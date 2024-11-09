//
// Created by Anton Demianov on 07.11.2024.
//
#pragma once
#ifndef USERCREDENTIALSENTITY_H
#define USERCREDENTIALSENTITY_H

#include <string>
#include <optional>

class UserCredentialsEntity {
public:
    std::string login;
    std::string password;
    std::string email;
    std::optional<unsigned long> last_login;

    UserCredentialsEntity(std::string  login,
                          std::string  password,
                          std::string  email,
                          const std::optional<unsigned long>& last_login = {})
         :login(std::move(login)),
          password(std::move(password)),
          email(std::move(email)),
          last_login(last_login) {}
};



#endif //USERCREDENTIALSENTITY_H
