//
// Created by Anton Demianov on 06.11.2024.
//

#ifndef USERENTITY_H
#define USERENTITY_H
#include <optional>
#include <string>
#include <wfrest/Json.h>

#include "AddressEntity.h"
#include "PhoneNumberEntity.h"


enum class Gender {
    PreferNotToSay,
    Male,
    Female,
    Other
};

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
        const std::string& first_name,
        const std::string& last_name,
        const Gender gender,
        const std::string& email,
        const unsigned long dob,
        const std::string& created_at,
        const PhoneNumberEntity& phone_number,
        const AddressEntity& address,
        const std::optional<std::string>& last_login = {},
        const std::optional<wfrest::Json>& additional_data = {}
        ):
    user_id(id),
    first_name(first_name),
    last_name(last_name),
    gender(gender),
    email(email),
    date_of_birth(dob),
    created_at(created_at),
    phone_number(phone_number),
    address(address),
    additional_data(additional_data) {}
};

#endif //USERENTITY_H
