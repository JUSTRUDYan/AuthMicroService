//
// Created by Anton Demianov on 06.11.2024.
//

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

    PhoneNumberEntity(const std::string& country_code,
                const std::string& area_code,
                const std::string& local_number,
                PhoneType phone_type = PhoneType::Mobile,
                const std::optional<std::string>& note = {})
        : country_code(country_code),
          area_code(area_code),
          local_number(local_number),
          phone_type(phone_type),
          note(note) {}
};



#endif //PHONENUMBERENTITY_H
