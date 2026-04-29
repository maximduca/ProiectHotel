cmake_minimum_required(VERSION 3.20)
project(ProiectHotel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Camera.cpp
    src/CameraStandard.cpp
    src/Apartament.cpp
    src/Penthouse.cpp
    src/Hotel.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE headers)