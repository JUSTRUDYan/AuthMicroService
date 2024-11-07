//
// Created by Anton Demianov on 06.11.2024.
//

#ifndef ADDRESSENTITY_H
#define ADDRESSENTITY_H
#include <wfrest/Json.h>
#include <string>
#include <optional>


class AddressEntity {
public:
    int street_number;
    std::string street_number_suffix;
    std::string street_name;
    std::string street_type;
    std::string street_direction;
    std::string address_type;
    std::string address_type_identifier;
    std::string minor_municipality;
    std::string major_municipality;
    std::string governing_district;
    std::string postal_area;
    std::string country;
    std::optional<std::string> note;
    std::optional<wfrest::Json> additional_data;

    AddressEntity(int street_number, const std::string& street_number_suffix, const std::string& street_name,
            const std::string& street_type, const std::string& street_direction, const std::string& address_type,
            const std::string& address_type_identifier, const std::string& minor_municipality,
            const std::string& major_municipality, const std::string& governing_district, const std::string& postal_area,
            const std::string& country, const std::optional<std::string>& note = {},
            const std::optional<wfrest::Json>& additional_data = {})
        : street_number(street_number),
          street_number_suffix(street_number_suffix),
          street_name(street_name),
          street_type(street_type),
          street_direction(street_direction),
          address_type(address_type),
          address_type_identifier(address_type_identifier),
          minor_municipality(minor_municipality),
          major_municipality(major_municipality),
          governing_district(governing_district),
          postal_area(postal_area),
          country(country),
          note(note),
          additional_data(additional_data) {}
};



#endif //ADDRESSENTITY_H
