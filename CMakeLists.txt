cmake_minimum_required(VERSION 3.25)
project(AuthMicroService)

set(CMAKE_CXX_STANDARD 20)

set(LIBRARIES_DIR "$ENV{HOME}/Documents/projects/Libraries/CPP")

include_directories(
        ${LIBRARIES_DIR}/workflow/_include
        ${LIBRARIES_DIR}/wfrest/_include
        /usr/local/opt/openssl@3/include
        /usr/local/include
)

set(WORKFLOW_LIB_DIR "${LIBRARIES_DIR}/workflow/_lib")
set(WFREST_LIB_DIR "${LIBRARIES_DIR}/wfrest/_lib")
set(OPENSSL_LIB_DIR "/usr/local/opt/openssl/lib")

find_package(jwt-cpp CONFIG REQUIRED)
find_package(libpqxx REQUIRED)
find_package(OpenSSL REQUIRED)

find_library(WORKFLOW_LIBRARY NAMES workflow HINTS "${WORKFLOW_LIB_DIR}")
find_library(WFREST_LIBRARY NAMES wfrest HINTS "${WFREST_LIB_DIR}")
find_library(ZLIB_LIBRARY NAMES z PATHS /usr/lib)
find_library(OPENSSL_LIBRARY NAMES ssl crypto PATHS "${OPENSSL_LIB_DIR}")

message(STATUS "Workflow Library: ${WORKFLOW_LIBRARY}")
message(STATUS "Wfrest Library: ${WFREST_LIBRARY}")
message(STATUS "Zlib Library: ${ZLIB_LIBRARY}")
message(STATUS "OpenSSL Library: ${OPENSSL_LIBRARY}")

# Check if the libraries were found
if(NOT WORKFLOW_LIBRARY)
    message(FATAL_ERROR "Workflow library not found.")
endif()
if(NOT WFREST_LIBRARY)
    message(FATAL_ERROR "Wfrest library not found.")
endif()
if(NOT ZLIB_LIBRARY)
    message(FATAL_ERROR "Zlib library not found.")
endif()
if(NOT OPENSSL_LIBRARY)
    message(FATAL_ERROR "OpenSSL library not found.")
endif()

add_executable(AuthMicroService main.cpp
        repositories/IAuthRepository.h
        models/UserEntity.h
        models/AddressEntity.h
        models/PhoneNumberEntity.h
        models/UserCredentialsEntity.h
        repositories/AuthRepositoryImpl.h
        repositories/DBConfigRepository.cpp
        repositories/DBConfigRepository.h
        models/Enums.h
        services/AuthAPIServiceImpl.cpp
        services/IAuthAPIService.h
        models/TokenDTO.h
        api/AuthControllerImpl.h
        api/IAuthController.h
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
