//
// Created by Anton Demianov on 07.11.2024.
//
#pragma once
#include "IAuthRepository.h"
#include "../models/UserEntity.h"
#include "../models/UserCredentialsEntity.h"
class AuthRepositoryImpl final : public IAuthRepository
{
    pqxx::connection c;

public:
    explicit AuthRepositoryImpl(pqxx::connection& connection) : c(std::move(connection)) {}
    bool isLoginExists(const std::string& login) override
    {
        try
        {
            pqxx::work transaction{c};
            const pqxx::result res = transaction.exec_params("SELECT 1 FROM users.credentials WHERE login = ' $1 ';", login);
            transaction.commit();
            return !res.empty();
        } catch (const std::exception& e)
        {
            std::cout << "Error checking if login exists: " << e.what() << std::endl;
            return false;
        }
    }

    bool isEmailExists(const std::string& email) override
    {
        try
        {
            pqxx::work transaction{c};
            const pqxx::result res = transaction.exec_params("SELECT 1 FROM users.credentials WHERE email = $1;", email);
            transaction.commit();
            return !res.empty();
        } catch (const std::exception& e)
        {
            std::cout << "Error checking if email exists: " << e.what() << std::endl;
            return false;
        }
    }

    bool isPhoneExists(const PhoneNumberEntity& phone) override
    {
        try
        {
            pqxx::work transaction{c};
            const pqxx::result res = transaction.exec_params(
                "SELECT 1 FROM users.phone_numbers "
                "WHERE country_code = $1 AND area_code = $2 AND local_number = $3",
                phone.country_code, phone.area_code, phone.local_number);

            transaction.commit();
            return !res.empty();
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error checking if phone exists: " << e.what() << std::endl;
            return false;
        }
    }


    bool updatePassword(const unsigned int user_id, const std::string& newPassword) override
    {
        try
        {
            pqxx::work transaction{c};
            transaction.exec_params("UPDATE users.credentials SET password = '$1';", newPassword);
            transaction.commit();
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error updating password: " << e.what() << std::endl;
            return false;
        }
    }

    bool updateLastLogin(const unsigned int user_id) override
    {
        try
        {
            pqxx::work transaction{c};
            transaction.exec_params("UPDATE user.credentials SET last_login = NOW() WHERE user_id = $1", user_id);
            transaction.commit();
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error updating last login: " << e.what() << std::endl;
            return false;
        }
    }


    std::optional<unsigned int> getUserIdByLogin(const std::string& login) override
    {
        try
        {
            pqxx::work transaction{c};
            const pqxx::row res = transaction.exec_params1(
                "SELECT user_id FROM user.credentials WHERE login = $1;", login);
            transaction.commit();
            return res["user_id"].as<unsigned int>();
        }
        catch ([[maybe_unused]] const pqxx::unexpected_rows& e)
        {
            return std::nullopt;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error retrieving user_id by login: " << e.what() << std::endl;
            return std::nullopt;
        }
    }


    std::optional<unsigned int> getUserIdByEmail(const std::string& email) override
    {
        try
        {
            pqxx::work transaction{c};
            const pqxx::row res = transaction.exec_params1(
                "SELECT user_id FROM user.credentials WHERE email = $1;", email);
            transaction.commit();
            return res["user_id"].as<unsigned int>();
        }
        catch ([[maybe_unused]] const pqxx::unexpected_rows& e)
        {
            return std::nullopt;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error retrieving user_id by login: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    int addUser(const UserEntity &user, const UserCredentialsEntity &credentials) override
    {
        try {
            const AddressEntity& userAddress = user.address;
            const PhoneNumberEntity& userPhoneNumber = user.phone_number;

            pqxx::work transaction{c};

            pqxx::row user_row = transaction.exec_params1(
                    "INSERT INTO users.users (first_name, last_name, gender, date_of_birth, additional_data) "
                    "VALUES ($1, $2, $3, to_date($4, 'YYYYMMDD'), $5::jsonb) RETURNING user_id;",
                    user.first_name,
                    user.last_name,
                    genderToString(user.gender),
                    user.date_of_birth,
                    user.additional_data ? user.additional_data->dump() : ""
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
                    userPhoneNumber.country_code,
                    userPhoneNumber.area_code,
                    userPhoneNumber.local_number,
                    phoneTypeToString(userPhoneNumber.phone_type),
                    userPhoneNumber.note.value_or("")
            );

            transaction.exec_params(
                    "INSERT INTO users.addresses (user_id, street_number, street_number_suffix, street_name, street_type, "
                    "street_direction, address_type, address_type_identifier, minor_municipality, major_municipality, "
                    "governing_district, postal_area, country, note, additional_data) "
                    "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15::jsonb);",
                    user_id,
                    userAddress.street_number,
                    userAddress.street_number_suffix,
                    userAddress.street_name,
                    userAddress.street_type,
                    userAddress.street_direction,
                    userAddress.address_type,
                    userAddress.address_type_identifier,
                    userAddress.minor_municipality,
                    userAddress.major_municipality,
                    userAddress.governing_district,
                    userAddress.postal_area,
                    userAddress.country,
                    userAddress.note.value_or(""),
                    userAddress.additional_data.value_or("").dump()
            );

            transaction.commit();

            return true;
        }   catch (const std::exception &e) {
            std::cerr << "Error adding user: " << e.what() << std::endl;
            return false;
        }
    }

    std::optional<UserCredentialsEntity> getUserCredentials(const unsigned int& id) override
    {
        pqxx::work transaction{c};
        auto result = transaction.exec("SELECT login, password, salt, user_id FROM users.credentials WHERE user_id = " + std::to_string(id) + ";");

        if (result.empty())
            return std::nullopt;

        const pqxx::row res = result[0];

        return UserCredentialsEntity(
            res["login"].is_null() ? "" : res["login"].as<std::string>(),
            res["password"].is_null() ? "" : res["password"].as<std::string>(),
            res["salt"].is_null() ? "" : res["salt"].as<std::string>(),
            res["user_id"].is_null() ? 0 : res["user_id"].as<unsigned long>()
        );
    }
};