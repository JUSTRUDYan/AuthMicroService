//
// Created by Anton Demianov on 09.11.2024.
//

#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

using namespace wfrest;

class IAuthController {
public:
    virtual ~IAuthController() = default;

    virtual BluePrint& signUp() = 0;
    virtual BluePrint& login() = 0;
    virtual BluePrint& logout() = 0;
    virtual BluePrint& updatePassword() = 0;
    virtual BluePrint& updateUser() = 0;

};
#endif //AUTHCONTROLLER_H
