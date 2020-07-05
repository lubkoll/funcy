list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
)
include(FuncyHeaders)

add_library(funcy INTERFACE)
target_include_directories(funcy INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_features(funcy INTERFACE cxx_std_20)
set_target_properties(funcy PROPERTIES
    EXPORT_NAME Funcy
)
target_sources(funcy INTERFACE ${HEADER_FILES})
add_library(Funcy::Funcy ALIAS funcy)

##############################################
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/funcy)

install(TARGETS funcy
    EXPORT funcy-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY . DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/funcy)
install(EXPORT funcy-targets
  FILE
    FuncyTargets.cmake
  NAMESPACE
    Funcy::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/funcy
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/FuncyConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/FuncyConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FuncyConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FuncyConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/FuncyConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
export(EXPORT funcy-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/FuncyTargets.cmake NAMESPACE Funcy::)
#Register package in user's package registry
export(PACKAGE funcy)

