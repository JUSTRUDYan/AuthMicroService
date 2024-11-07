//
// Created by Anton Demianov on 07.11.2024.
//
#include "IAuthRepository.h"
#include "../models/UserEntity.h"
#include "../models/UserCredentialsEntity.h"

int AuthRepository::addUser(const UserEntity &user, const UserCredentialsEntity &credentials) {
    try {
        pqxx::work transaction{c};

        pqxx::row user_row = transaction.exec_params1(
                "INSERT INTO users.users (first_name, last_name, gender, date_of_birth, additional_data) "
                "VALUES ($1, $2, $3, to_date($4, 'YYYYMMDD'), $5::jsonb) RETURNING user_id;",
                user.first_name,
                user.last_name,
                genderToString(user.gender),
                user.date_of_birth,
                user.additional_data ? user.additional_data->dump() : nullptr
        );

        int user_id = user_row["user_id"].as<int>();

        transaction.exec_params(
                "INSERT INTO users.credentials (user_id, login, password, email, last_login) "
                "VALUES ($1, $2, $3, $4, $5);",
                user_id,
                user.email,
                "hashed_password",
                user.email,
                nullptr
        );

        transaction.exec_params(
                "INSERT INTO users.phone_numbers (user_id, country_code, area_code, local_number, phone_type, note) "
                "VALUES ($1, $2, $3, $4, $5, $6);",
                user_id,
                user.phone_number.country_code,
                user.phone_number.area_code,
                user.phone_number.local_number,
                phoneTypeToString(user.phone_number.phone_type),
                user.phone_number.note.value_or("")
        );

        transaction.exec_params(
                "INSERT INTO users.addresses (user_id, street_number, street_number_suffix, street_name, street_type, "
                "street_direction, address_type, address_type_identifier, minor_municipality, major_municipality, "
                "governing_district, postal_area, country, note, additional_data) "
                "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15::jsonb);",
                user_id,
                user.address.street_number,
                user.address.street_number_suffix,
                user.address.street_name,
                user.address.street_type,
                user.address.street_direction,
                user.address.address_type,
                user.address.address_type_identifier,
                user.address.minor_municipality,
                user.address.major_municipality,
                user.address.governing_district,
                user.address.postal_area,
                user.address.country,
                user.address.note.value_or(""),
                user.address.additional_data ? user.address.additional_data->dump() : nullptr
        );

        transaction.commit();

        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error adding user: " << e.what() << std::endl;
        return false;
    }
}

std::optional<UserCredentialsEntity> AuthRepository::getUserCredentials(const unsigned int& id)
{
    pqxx::work transaction{c};
    auto result = transaction.exec("SELECT login, password, salt, user_id FROM users.credentials WHERE user_id = " + std::to_string(id) + ";");

    if (result.empty())
        return std::nullopt;

    pqxx::row res = result[0];

    return UserCredentialsEntity(
            res["login"].is_null() ? "" : res["login"].as<std::string>(),
            res["password"].is_null() ? "" : res["password"].as<std::string>(),
            res["salt"].is_null() ? "" : res["salt"].as<std::string>(),
            res["user_id"].is_null() ? 0 : res["user_id"].as<unsigned long>()
    );
}


AuthRepository::AuthRepository(const pqxx::connection& connection) {}
