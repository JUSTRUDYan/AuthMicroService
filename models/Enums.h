//
// Created by steam on 08.11.2024.
//

#ifndef AUTHMICROSERVICE_GENDERENUM_H
#define AUTHMICROSERVICE_GENDERENUM_H

#endif //AUTHMICROSERVICE_GENDERENUM_H

#include <string>

enum class Gender {
    PreferNotToSay,
    Male,
    Female,
    Other
};

enum class PhoneType {
    Mobile,
    Home,
    Work,
    Fax,
    Other
};

std::string genderToString(Gender gender) {
    switch (gender) {
        case Gender::Male:
            return "male";
        case Gender::Female:
            return "female";
        case Gender::Other:
            return "other";
        default:
            return "prefer-not-to-say";
    }
}


std::string phoneTypeToString(PhoneType phoneType) {
    switch (phoneType) {
        case PhoneType::Mobile:
            return "mobile";
        case PhoneType::Home:
            return "home";
        case PhoneType::Work:
            return "work";
        case PhoneType::Fax:
            return "fax";
        default:
            return "other";
    }
}
