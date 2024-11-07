//
// Created by Anton Demianov on 07.11.2024.
//
#include "IAuthRepository.h"
#include "../models/UserEntity.h"
#include "../models/UserCredentialsEntity.h"

AuthRepository::AuthRepository(const pqxx::connection& c): tx()
{
    pqxx::work tx{c};
    pqxx::result res = tx.exec("SELECT * FROM employee");
}

int AuthRepository::addUser(const UserEntity& user, const UserCredentialsEntity& credentials)
{

}

std::optional<UserCredentialsEntity> AuthRepository::getUserCredentials(const unsigned int& id)
{

}