#[[---------------------------------------------------------------------------
                                  Base settings
   ---------------------------------------------------------------------------]]

#[[ Set CMake minimum required version ]]
cmake_minimum_required(VERSION 3.0)

#[[ Set project version and description ]]
project(InstanceGuard VERSION 1.0.0 LANGUAGES CXX)

#[[ Set C++ standard version ]]
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#[[ Set default build type if none was specified ]]
set(DEFAULT_BUILD_TYPE "Debug")

#[[ Set build type if none was specified ]]
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(
        CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
        STRING "Choose the type of build." FORCE
    )
    set_property(
        CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug"
        "Release"
        "MinSizeRel"
        "RelWithDebInfo"
    )
endif()

#[[ Define GNU standard installation directories ]]
include(GNUInstallDirs)


#[[---------------------------------------------------------------------------
                               Project files settings
   ---------------------------------------------------------------------------]]

#[[ Set header files ]]
set(
    HEADER_FILES
    config.h
    InstanceGuard.hpp
)

#[[ Set source files ]]
set(
    SOURCE_FILES
    InstanceGuard.cpp
)

#[[ Set public header files ]]
set(
    PUBLIC_HEADER_FILES
    InstanceGuard.hpp
)

#[[ Set pkg-config input file ]]
set(
    PKG_CONFIG_INPUT_FILE
    InstanceGuard.pc.in
)

#[[ Set pkg-config output file ]]
string(
    REGEX REPLACE "\\.[^.]*$" ""
    PKG_CONFIG_OUTPUT_FILE
    ${PKG_CONFIG_INPUT_FILE}
)


#[[---------------------------------------------------------------------------
                                Targets settings
   ---------------------------------------------------------------------------]]

#[[ Add library target ]]
add_library(
    InstanceGuard
    STATIC
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

#[[ Set target properties ]]
set_target_properties(
    InstanceGuard PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER ${PUBLIC_HEADER_FILES}
)

#[[ Configure pkg-config files ]]
configure_file(
    ${PKG_CONFIG_INPUT_FILE}
    ${PKG_CONFIG_OUTPUT_FILE}
    @ONLY
)

#[[ Install library files ]]
install(
    TARGETS InstanceGuard
    LIBRARY ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

#[[ Install pkg-config files ]]
install(
    FILES ${CMAKE_BINARY_DIR}/${PKG_CONFIG_OUTPUT_FILE}
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
