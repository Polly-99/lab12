cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/Polly-99/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "76f92ff7b49ec643196e60690f2123c3b986cdb7"
)
project(lab12)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

set(SOURCE_FILES cget.cpp)
add_executable(lab12 ${SOURCE_FILES})

target_link_libraries(lab12 CURL::libcurl)
install(TARGETS lab12 RUNTIME DESTINATION bin)
