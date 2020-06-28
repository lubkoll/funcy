cmake_minimum_required(VERSION 3.8)

project(funcy VERSION 1.5.3 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

option(Funcy_BuildTest "build test" OFF)
option(Funcy_Funcy "enable funcy" ON)
option(Funcy_Texy "enable texy" OFF)
#option(Funcy_Stringy "enable stringy" OFF)

add_subdirectory(include)

if(Funcy_BuildTest)
    add_subdirectory(test)
endif()

