cmake_minimum_required(VERSION 3.29)
project(AuthMicroService)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ~/Documents/projects/Libraries/CPP/workflow/_include
        ~/Documents/projects/Libraries/CPP/wfrest/_include
        /usr/local/opt/openssl@3/include
        /usr/local/include
)

set(WORKFLOW_LIB_DIR ~/Documents/projects/Libraries/CPP/workflow/_lib)
set(WFREST_LIB_DIR ~/Documents/projects/Libraries/CPP/wfrest/_lib)
set(OPENSSL_LIB_DIR /usr/local/opt/openssl/lib)

find_package(jwt-cpp CONFIG REQUIRED)
find_package(libpqxx REQUIRED)

find_library(WORKFLOW_LIBRARY NAMES workflow HINTS ${WORKFLOW_LIB_DIR})
find_library(WFREST_LIBRARY NAMES wfrest HINTS ${WFREST_LIB_DIR})
find_library(ZLIB_LIBRARY NAMES z PATHS /usr/lib)
find_library(OPENSSL_LIBRARY NAMES ssl crypto PATHS ${OPENSSL_LIB_DIR})
link_directories("/usr/local/lib")

message(STATUS "Workflow Library: ${WORKFLOW_LIBRARY}")
message(STATUS "Wfrest Library: ${WFREST_LIBRARY}")
message(STATUS "Zlib Library: ${ZLIB_LIBRARY}")
message(STATUS "OpenSSL Library: ${OPENSSL_LIBRARY}")

add_executable(AuthMicroService main.cpp
        repositories/IAuthRepository.h
        models/UserEntity.h
        models/AddressEntity.h
        models/PhoneNumberEntity.h
        models/UserCredentialsEntity.h
        repositories/AuthRepositoryImpl.cpp
        repositories/DBConfigRepository.cpp
        repositories/DBConfigRepository.h
        models/AddressEntity.cpp
        models/PhoneNumber.cpp
        models/UserCredentialsEntity.cpp
)

target_link_libraries(AuthMicroService
        PRIVATE
        ${WORKFLOW_LIBRARY}
        ${WFREST_LIBRARY}
        ${ZLIB_LIBRARY}
        jwt-cpp::jwt-cpp
        ${OPENSSL_LIBRARY}
        pqxx
)