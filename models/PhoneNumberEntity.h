//
// Created by Anton Demianov on 06.11.2024.
//
#pragma once
#ifndef PHONENUMBERENTITY_H
#define PHONENUMBERENTITY_H
#include <optional>
#include <string>
#include "Enums.h"

class PhoneNumberEntity {
public:
    std::string country_code;
    std::string area_code;
    std::string local_number;
    PhoneType phone_type;
    std::optional<std::string> note;

    PhoneNumberEntity(std::string&  country_code,
                std::string&  area_code,
                std::string&  local_number,
                const PhoneType& phone_type = PhoneType::Mobile,
                const std::optional<std::string>& note = {})
        : country_code(std::move(country_code)),
          area_code(std::move(area_code)),
          local_number(std::move(local_number)),
          phone_type(phone_type),
          note(note) {}
};



#endif //PHONENUMBERENTITY_H
