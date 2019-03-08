# Findfuncy.cmake
#
# Finds the funcy library
#
# This will define the following variables
#
#    funcy_FOUND
#    funcy_INCLUDE_DIRS
#
# and the following imported targets
#
#     funcy::funcy

find_package(PkgConfig)
pkg_check_modules(PC_funcy QUIET funcy)

find_path(funcy_INCLUDE_DIR
    NAMES funcy/funcy.hh
    PATHS ${PC_funcy_INCLUDE_DIRS} ${funcy_DIR}
    PATH_SUFFIXES include
)

set(funcy_VERSION ${PC_funcy_VERSION})

mark_as_advanced(funcy_FOUND funcy_INCLUDE_DIR funcy_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(funcy
    REQUIRED_VARS funcy_INCLUDE_DIR
    VERSION_VAR funcy_VERSION
)

if(funcy_FOUND)
    set(funcy_INCLUDE_DIRS ${funcy_INCLUDE_DIR})
endif()

if(funcy_FOUND AND NOT TARGET funcy::funcy)
    add_library(funcy::funcy INTERFACE IMPORTED)
    set_target_properties(funcy::funcy PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${funcy_INCLUDE_DIRS}"
    )
endif()
