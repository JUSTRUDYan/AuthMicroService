//
// Created by Anton Demianov on 07.11.2024.
//

#ifndef DBCONFIGREPOSITORY_H
#define DBCONFIGREPOSITORY_H
#include <string>

#endif //DBCONFIGREPOSITORY_H

class DBConfigRepository {
    std::string postgresHost;
    std::string postgresPort;
    std::string postgresUser;
    std::string postgresPassword;
    std::string postgresDatabase;

    void loadFromFile(const std::string& filePath);

    void connect(const std::string& connectionString);

public:
    std::optional<pqxx::connection> connection;
    explicit DBConfigRepository(const std::string& filePath);

    DBConfigRepository(const std::string& host, const std::string& port, const std::string& user,
                       const std::string& password, const std::string& database);
};