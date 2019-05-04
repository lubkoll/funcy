cmake_minimum_required(VERSION 3.8)

project(funcy VERSION 1.4.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

add_library(funcy INTERFACE)
target_include_directories(funcy INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

include(Headers)

target_compile_features(funcy INTERFACE cxx_std_14)
set_target_properties(funcy PROPERTIES
  EXPORT_NAME funcy
)
target_sources(funcy INTERFACE ${HEADER_FILES})
#This is required so that the exported target has the name funcy and not funcy
set_target_properties(funcy PROPERTIES EXPORT_NAME funcy)
add_library(funcy::funcy ALIAS funcy)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/funcy)

install(TARGETS funcy
    EXPORT funcy-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT funcy-targets
  FILE
    funcyTargets.cmake
  NAMESPACE
    funcy::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/funcy
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/funcyConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/funcyConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/funcyConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/cmake/Findfuncy.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/funcyConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/funcyConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/Findfuncy.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/Findfuncy.cmake
    COPYONLY)

export(EXPORT funcy-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/funcyTargets.cmake NAMESPACE funcy::)
#Register package in user's package registry
export(PACKAGE funcy)

option(BuildTest "BuildTest" OFF)
if(BuildTest)
    add_subdirectory(test)
endif()

