

#include <string>
#include <fstream>
#include <iostream>
#include <pqxx/pqxx>  // pqxx connection class
#include <optional>
#include <wfrest/Json.h>

#include "DBConfigRepository.h"
void DBConfigRepository::loadFromFile(const std::string& filePath) {
    if (filePath.empty()) {
        std::cerr << "Config path is empty :(" << std::endl;
        return;
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Config file \"" << filePath << "\" is not exist!" << std::endl;
        return;
    }

    std::string rawConfig;
    std::string line;
    while (getline(file, line)) {
        rawConfig += line + "\n";
    }
    file.close();

    try {
        wfrest::Json jsonConfig = wfrest::Json::parse(rawConfig);

        if (jsonConfig.has("postgresHost")) {
            postgresHost = jsonConfig["postgresHost"].get<std::string>();
        }
        if (jsonConfig.has("postgresPort")) {
            postgresPort = jsonConfig["postgresPort"].get<std::string>();
        }
        if (jsonConfig.has("postgresUser")) {
            postgresUser = jsonConfig["postgresUser"].get<std::string>();
        }
        if (jsonConfig.has("postgresPassword")) {
            postgresPassword = jsonConfig["postgresPassword"].get<std::string>();
        }
        if (jsonConfig.has("postgresDatabase")) {
            postgresDatabase = jsonConfig["postgresDatabase"].get<std::string>();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error during config parsing -> " << e.what() << std::endl;
    }
}

void DBConfigRepository::connect(const std::string& connectionString) {
    try {
        if (pqxx::connection connection(connectionString); connection.is_open()) {
            std::cout << "Connected to database: " << connection.dbname() << std::endl;
            this->connection = std::move(connection);
            return;
        }
        std::cerr << "Can't open database" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error during establishing connection to database -> " << e.what() << std::endl;
    }
}

DBConfigRepository::DBConfigRepository(const std::string& filePath)
    : postgresHost("localhost"), postgresPort("5432"), postgresUser("postgres"),
      postgresPassword("password"), postgresDatabase("postgres")
{
    loadFromFile(filePath);
    const std::string connectionString = "dbname=" + postgresDatabase + " user=" + postgresUser + " password=" +
        postgresPassword + " host=" + postgresHost + " port=" + postgresPort;
    connect(connectionString);
}

DBConfigRepository::DBConfigRepository(const std::string& host, const std::string& port, const std::string& user,
                                       const std::string& password, const std::string& database)
    : postgresHost(host), postgresPort(port), postgresUser(user), postgresPassword(password),
      postgresDatabase(database)
{
    std::string connectionString = "dbname=" + postgresDatabase + " user=" + postgresUser + " password=" +
        postgresPassword + " host=" + postgresHost + " port=" + postgresPort;
    connect(connectionString);
}
