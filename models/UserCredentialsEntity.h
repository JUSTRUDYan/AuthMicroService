//
// Created by Anton Demianov on 07.11.2024.
//

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

    UserCredentialsEntity(const std::string& login,
                          const std::string& password,
                          const std::string& email,
                          const std::optional<unsigned long>& last_login = {})
         :login(login),
          password(password),
          email(email),
          last_login(last_login) {}
};



#endif //USERCREDENTIALSENTITY_H
