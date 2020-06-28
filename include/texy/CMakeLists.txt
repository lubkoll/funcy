list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
)
include(TexyHeaders)

add_library(texy INTERFACE)
target_include_directories(texy INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_features(texy INTERFACE cxx_std_17)
set_target_properties(texy PROPERTIES
    EXPORT_NAME Funcy
)
target_sources(texy INTERFACE ${HEADER_FILES})
add_library(Funcy::Texy ALIAS texy)

#include(GNUInstallDirs)
#set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/texy)

#install(TARGETS texy
#    EXPORT texy-targets
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)
#install(DIRECTORY . DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/texy)
#install(EXPORT texy-targets
#  FILE
#    TexyTargets.cmake
#  NAMESPACE
#    Texy::
#  DESTINATION
#    ${CMAKE_INSTALL_LIBDIR}/cmake/texy
#)

#include(CMakePackageConfigHelpers)
#write_basic_package_version_file(
#    ${CMAKE_CURRENT_BINARY_DIR}/TexyConfigVersion.cmake
#    VERSION ${PROJECT_VERSION}
#    COMPATIBILITY AnyNewerVersion
#)

#configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/TexyConfig.cmake.in
#    ${CMAKE_CURRENT_BINARY_DIR}/TexyConfig.cmake
#    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
#)

#install(FILES
#    ${CMAKE_CURRENT_BINARY_DIR}/TexyConfig.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/TexyConfigVersion.cmake
#    DESTINATION ${INSTALL_CONFIGDIR}
#)

##############################################
#export(EXPORT texy-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/TexyTargets.cmake NAMESPACE Texy::)
#Register package in user's package registry
#export(PACKAGE texy)

