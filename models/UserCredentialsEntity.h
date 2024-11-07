//
// Created by Anton Demianov on 07.11.2024.
//

#ifndef USERCREDENTIALSENTITY_H
#define USERCREDENTIALSENTITY_H

#include <string>
#include <optional>

class UserCredentialsEntity {
public:
    const int user_id;
    std::string login;
    std::string password;
    std::string email;
    std::optional<unsigned long> last_login;

    UserCredentialsEntity(const int user_id,
                          const std::string& login,
                          const std::string& password,
                          const std::string& email,
                          const std::optional<std::time_t>& last_login = {})
        : user_id(user_id),
          login(login),
          password(password),
          email(email),
          last_login(last_login) {}
};



#endif //USERCREDENTIALSENTITY_H
