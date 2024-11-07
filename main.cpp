#include "workflow/WFFacilities.h"
#include <csignal>
#include "wfrest/HttpServer.h"
#include <jwt-cpp/jwt.h>
#include <pqxx/pqxx>
#include "./repositories/DBConfigRepository.h"
#include "repositories/IAuthRepository.h"

using namespace wfrest;

static WFFacilities::WaitGroup wait_group(1);

int mai1n() {
    const std::string secret = "my_secret_key";

    auto token = jwt::create()
        .set_issuer("auth0")
        .set_type("JWT")
        .set_subject("user123")
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{1})
        .sign(jwt::algorithm::hs256{secret});

    std::cout << "JWT Token: " << token << std::endl;

    return 0;
}

void sigHandler(int signo)
{
    wait_group.done();
}

void setErrorResponse(HttpResp *resp, int statusCode, const std::string& message) {
    resp->set_status(statusCode);
    Json errorJson;
    errorJson["error"] = message;
    resp->Json(errorJson);
}

int main(const int argc, char* argv[])
{
    signal(SIGINT, sigHandler);
    const std::string configFilePath = argv[1];
    DBConfigRepository configRepo(configFilePath);
    if (!configRepo.connection.has_value())
    {
        return EXIT_FAILURE;
    }

    pqxx::work tx{configRepo.connection.value()};
    IAuthRepository authRepo = AuthRepositoryImpl();

/*
    HttpServer svr;
    svr.POST("~/auth/sign-up", [](const HttpReq *req, HttpResp *resp)
    {
        // Перевірка на тип контенту
        if (req->content_type() != APPLICATION_JSON)
        {
            setErrorResponse(resp, 415, "Content-Type must be application/json.");
            return;
        }

        // Отримання JSON з запиту
        const Json& registerData = req->json();

        // Перевірка обов'язкових полів
        if (!registerData.has("login"))
        {
            setErrorResponse(resp, 400, "Login is required.");
            return;
        }
        if (!registerData.has("password"))
        {
            setErrorResponse(resp, 400, "Password is required.");
            return;
        }

        std::string login = registerData["login"].dump();
        std::string password = registerData["password"].dump();

        // Валідація логіна (наприклад, перевірка на мінімальну довжину)
        if (login.length() < 5)
        {
            setErrorResponse(resp, 400, "Login must be at least 5 characters long.");
            return;
        }

        // Валідація пароля
        if (password.length() < 8)
        {
            setErrorResponse(resp, 400, "Password must be at least 8 characters long.");
            return;
        }
        // Хешування пароля
        std::string passwordHash = BCrypt::generateHash(password);

        // Збереження користувача в базу даних (псевдокод)
        // Якщо база даних вже містить такий логін
        if (userExists(login))
        {
            setErrorResponse(resp, 409, "User with this login already exists.");
            return;
        }

        // Приклад збереження нового користувача
        if (!saveUserToDatabase(login, passwordHash)) // Функція для збереження користувача в БД
        {
            setErrorResponse(resp, 500, "Failed to register user.");
            return;
        }

        // Успішна відповідь
        Json response;
        response["message"] = "User registered successfully.";
        resp->Json(response, 201); // 201 Created
    });


    svr.GET("/accounts", [](const HttpReq *req, HttpResp *resp)
    {
        if (jsons.empty())
        {
            setErrorResponse(resp, 404, "No tuples found.");
            return;
        }

        Json response;
        for (size_t i = 0; i < jsons.size(); i++) {
            Json iJson = jsons[i];
            iJson["id"] = i;
            response.push_back(iJson);
        }

        resp->Json(response);
    });

    svr.POST("/accounts", [](const HttpReq *req, HttpResp *resp)
    {
        if (req->content_type() != APPLICATION_JSON)
        {
            setErrorResponse(resp, 415, "Content-Type is not application/json.");
            return;
        }

        const Json jsonStr = req->json();
        if (!jsonStr.has("login") || !jsonStr.has("password")) {
            setErrorResponse(resp, 400, "Invalid request: 'login' and 'password' fields are required.");
            return;
        }

        jsons.push_back(jsonStr);
        std::cerr << "Json" << (jsons.size() - 1) << " : " << jsonStr.dump() << "\n";

        Json jsonResponse = jsonStr;
        jsonResponse["id"] = jsons.size() - 1;
        resp->Json(jsonResponse);
    });

    svr.DELETE("/accounts", [](const HttpReq *req, HttpResp *resp)
    {
        if (req->content_type() != APPLICATION_JSON)
        {
            setErrorResponse(resp, 415, "Content-Type is not application/json.");
            return;
        }

        const Json& json = req->json();
        if (!json["id"].is_number()) {
            setErrorResponse(resp, 400, "Invalid request: 'id' should be a number.");
            return;
        }

        const unsigned int id = json["id"].get<unsigned int>();
        if (id >= jsons.size())
        {
            setErrorResponse(resp, 404, "Tuple with id " + std::to_string(id) + " does not exist.");
            return;
        }

        jsons.erase(jsons.begin() + id);
        Json response;
        response["message"] = "Tuple with id " + std::to_string(id) + " has been deleted.";
        resp->Json(response);
    });

    if (svr.start(8888) == 0)
    {
        wait_group.wait();
        svr.stop();
    } else
    {
        fprintf(stderr, "Cannot start server\n");
        exit(1);
    }
    return 0;
    */
}
