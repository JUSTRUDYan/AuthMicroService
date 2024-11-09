//
// Created by Anton Demianov on 08.11.2024.
//

#ifndef AUTHAPISERVICE_H
#define AUTHAPISERVICE_H



#ifndef IAUTH_API_SERVICE_IMPL_H
#define IAUTH_API_SERVICE_IMPL_H

#include <string>
#include <optional>
#include "User.h"
#include "Token.h"

class IAuthAPIServiceImpl {
public:
    virtual ~IAuthAPIServiceImpl() = default;

    virtual AuthResponse login(const AuthRequest& request) = 0;

    virtual AuthResponse registerUser(const AuthRequest& request) = 0;

    virtual AuthResponse logout(const std::string& token) = 0;

    virtual bool validateToken(const std::string& token) = 0;

    virtual std::optional<Token> refreshToken(const std::string& refreshToken) = 0;

    virtual AuthResponse changePassword(const std::string& userId, const std::string& oldPassword, const std::string& newPassword) = 0;

    virtual AuthResponse resetPassword(const std::string& email) = 0;
};

#endif // IAUTH_API_SERVICE_IMPL_H



#endif //AUTHAPISERVICE_H
