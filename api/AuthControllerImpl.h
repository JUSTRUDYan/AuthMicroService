//
// Created by Anton Demianov on 09.11.2024.
//
#pragma once

#include <wfrest/HttpServer.h>
#include "../utilies/setErrorResponse.h"

class AuthControllerImpl
{
public:

    explicit AuthControllerImpl(wfrest::HttpServer& svr) {
        svr.register_blueprint(signUp(), "/auth");
    }
};