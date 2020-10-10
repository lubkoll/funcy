cmake_minimum_required(VERSION 3.8)

project(funcy VERSION 1.6.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

option(Funcy_BuildTest "build test" OFF)
option(Funcy_DisableAssert "disable assert" OFF)
option(Funcy_Funcy "enable funcy" ON)
option(Funcy_Texy "enable texy" OFF)

if(Funcy_DisableAssert)
    add_definitions(-DFUNCY_DISABLE_ASSERT)
endif()

add_subdirectory(include)

if(Funcy_BuildTest)
    add_subdirectory(test)
endif()

