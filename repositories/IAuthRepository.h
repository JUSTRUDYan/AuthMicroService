#pragma once
#include <pqxx/pqxx>
#include <string>
#include <optional>
#include "../models/UserEntity.h"
#include "../models/UserCredentialsEntity.h"

class IAuthRepository
{
public:
    virtual ~IAuthRepository() = default;
    virtual bool isLoginExists(const std::string& login) = 0;
    virtual bool isEmailExists(const std::string& email) = 0;
    virtual bool isPhoneExists(const PhoneNumberEntity& phone) = 0;
    virtual int addUser(const UserEntity& user, const UserCredentialsEntity& credentials) = 0;
    virtual bool updatePassword(unsigned int user_id, const std::string& newPassword) = 0;
    virtual bool updateLastLogin(unsigned int user_id) = 0;
    virtual std::optional<unsigned int> getUserIdByLogin(const std::string& login) = 0;
    virtual std::optional<unsigned int> getUserIdByEmail(const std::string& email) = 0;
    virtual std::optional<UserCredentialsEntity> getUserCredentials(const unsigned int& id) = 0;
    IAuthRepository() = default;
};
