cmake_minimum_required(VERSION 3.25)
project(AuthMicroService)

set(CMAKE_CXX_STANDARD 20)

# Specify include directories
include_directories(
        /mnt/d/projects/Libraries/CPP/workflow/_include
        /mnt/d/projects/Libraries/CPP/wfrest/_include
        /usr/local/opt/openssl@3/include
        /usr/local/include
)

set(WORKFLOW_LIB_DIR /mnt/d/projects/Libraries/CPP/workflow/_lib)
set(WFREST_LIB_DIR /mnt/d/projects/Libraries/CPP/wfrest/_lib)
set(OPENSSL_LIB_DIR /usr/local/opt/openssl/lib)

find_package(jwt-cpp CONFIG REQUIRED)
find_package(libpqxx REQUIRED)
find_package(OpenSSL REQUIRED)

find_library(WORKFLOW_LIBRARY NAMES workflow HINTS ${WORKFLOW_LIB_DIR})
find_library(WFREST_LIBRARY NAMES wfrest HINTS ${WFREST_LIB_DIR})
find_library(ZLIB_LIBRARY NAMES z PATHS /usr/lib)
find_library(OPENSSL_LIBRARY NAMES ssl crypto PATHS ${OPENSSL_LIB_DIR})

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
        models/Enums.h
)

target_link_libraries(AuthMicroService
        PRIVATE
        ${WORKFLOW_LIBRARY}
        ${WFREST_LIBRARY}
        ${ZLIB_LIBRARY}
        jwt-cpp::jwt-cpp
        OpenSSL::SSL
        OpenSSL::Crypto
        pqxx
)
