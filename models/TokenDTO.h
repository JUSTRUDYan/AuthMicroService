//
// Created by Anton Demianov on 08.11.2024.
//
#pragma once
#ifndef TOKENDTO_H
#define TOKENDTO_H
#include <string>
#include <jwt-cpp/jwt.h>
#include <wfrest/Json.h>

#endif //TOKENDTO_H

class TokenDTO
{
    const std::string accessToken;
    const std::string refreshToken;
    const unsigned long expires;

    public:

    TokenDTO(
    std::string& token, std::string& refresh, const unsigned long expires
    ): accessToken(std::move(token)), refreshToken(std::move(refresh)), expires(expires)
    {};

    [[nodiscard]] wfrest::Json GetJson() const
    {
        wfrest::Json jsonToken;
        jsonToken["access_token"] = accessToken;
        jsonToken["access_refresh"] = refreshToken;
        jsonToken["expires"] = expires;
        return jsonToken;
    }
};