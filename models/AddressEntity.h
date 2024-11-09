//
// Created by Anton Demianov on 06.11.2024.
//
#pragma once
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

    AddressEntity(int street_number, std::string  street_number_suffix, std::string  street_name,
            std::string  street_type, std::string  street_direction, std::string  address_type,
            std::string  address_type_identifier, std::string  minor_municipality,
            std::string  major_municipality, std::string  governing_district, std::string  postal_area,
            std::string  country, const std::optional<std::string>& note = {},
            const std::optional<wfrest::Json>& additional_data = {})
        : street_number(street_number),
          street_number_suffix(std::move(street_number_suffix)),
          street_name(std::move(street_name)),
          street_type(std::move(street_type)),
          street_direction(std::move(street_direction)),
          address_type(std::move(address_type)),
          address_type_identifier(std::move(address_type_identifier)),
          minor_municipality(std::move(minor_municipality)),
          major_municipality(std::move(major_municipality)),
          governing_district(std::move(governing_district)),
          postal_area(std::move(postal_area)),
          country(std::move(country)),
          note(note),
          additional_data(additional_data) {}
};



#endif //ADDRESSENTITY_H
