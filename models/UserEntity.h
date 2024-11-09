//
// Created by Anton Demianov on 06.11.2024.
//
#pragma once
#ifndef USERENTITY_H
#define USERENTITY_H
#include <optional>
#include <string>
#include <utility>
#include <wfrest/Json.h>

#include "AddressEntity.h"
#include "PhoneNumberEntity.h"

class UserEntity {
public:
    const unsigned int user_id;
    std::string first_name;
    std::string last_name;
    Gender gender = Gender::PreferNotToSay;
    std::string email;
    unsigned long date_of_birth;
    std::string created_at;
    PhoneNumberEntity phone_number;
    AddressEntity address;
    std::optional<wfrest::Json> additional_data;

    UserEntity
    (
        const unsigned int id,
        std::string&   first_name,
        std::string&   last_name,
        const Gender& gender,
        std::string&  email,
        const unsigned long dob,
        std::string&  created_at,
        PhoneNumberEntity   phone_number,
        AddressEntity&  address,
        const std::optional<std::string>& last_login = {},
        const std::optional<wfrest::Json>& additional_data = {}
        ):
    user_id(id),
    first_name(std::move(first_name)),
    last_name(std::move(last_name)),
    gender(gender),
    email(std::move(email)),
    date_of_birth(dob),
    created_at(std::move(created_at)),
    phone_number(std::move(phone_number)),
    address(std::move(address)),
    additional_data(additional_data) {}
};

#endif //USERENTITY_H
