//
// Created by Anton Demianov on 09.11.2024.
//
#pragma once

#include <wfrest/HttpServer.h>

#include "IAuthController.h"

class AuthControllerImpl final : public IAuthController
{
public:

    explicit AuthControllerImpl(wfrest::HttpServer& svr) {
        svr.register_blueprint(signUp(), "/auth");
    }

    private:

    BluePrint* signUp() override
    {
        auto* bp = new BluePrint();

        bp->POST("/sign-up", [](const HttpReq *req, HttpResp *resp)
        {
            if (req->content_type() != APPLICATION_JSON)
            {
                setErrorResponse(resp, 415, "Content-Type must be application/json.");
                return;
            }


        });

        return bp;
    }


    static void login(BluePrint& bp) override
    {

    }

    void logout(const BluePrint& bp) override
    {

    }

    void updatePassword(const BluePrint& bp) override
    {

    }

    void updateUser(const BluePrint& bp) override
    {

    }
};