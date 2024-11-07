#include <pqxx/pqxx>
#include <string>
#include <optional>
#include "../models/UserEntity.h"
#include "../models/UserCredentialsEntity.h"

class AuthRepository
{
protected:
    pqxx::work tx; // Не посилання, а власний об'єкт транзакції

public:
    explicit AuthRepository(pqxx::connection& connection);

    virtual ~AuthRepository() = default;

    virtual bool isLoginExists(const std::string& login) = 0;
    virtual bool isEmailExists(const std::string& email) = 0;
    virtual bool isPhoneExists(const std::string& phone) = 0;
    AuthRepository(const pqxx::connection& c);
    virtual int addUser(const UserEntity& user, const UserCredentialsEntity& credentials) = 0;
    virtual int updatePassword(const std::string& login, const std::string& newPassword) = 0;
    virtual int updateLastLogin(const std::string& login) = 0;
    virtual std::optional<unsigned int> getUserIdByLogin(const std::string& login) = 0;
    virtual std::optional<unsigned int> getUserIdByEmail(const std::string& email) = 0;
    virtual std::optional<UserCredentialsEntity> getUserCredentials(const unsigned int& id) = 0;
};
