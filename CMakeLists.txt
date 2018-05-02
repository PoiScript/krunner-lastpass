cmake_minimum_required(VERSION 2.8.12)
project(KRunnerLastPass)

# build library
include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

file(GLOB PROJECT_HEADERS
        lastpass-cli/cmd.h
        lastpass-cli/util.h
        lastpass-cli/agent.h
        lastpass-cli/endpoints.h
        )

file(GLOB PROJECT_SOURCES
        lastpass-cli/cmd.c
        lastpass-cli/util.c
        lastpass-cli/agent.c
        lastpass-cli/endpoints.c
        )

add_library(lastpass SHARED lastpass.c ${PROJECT_HEADERS} ${PROJECT_SOURCES})

set(PROJECT_DEFINITIONS "_GNU_SOURCE")

set(PROJECT_FLAGS "-std=gnu99 -pedantic -Wall -Wextra -Wno-language-extension-token")

set_target_properties(lastpass PROPERTIES
        C_STANDARD 99
        COMPILE_FLAGS ${PROJECT_FLAGS}
        COMPILE_DEFINITIONS ${PROJECT_DEFINITIONS}
        )

target_link_libraries(lastpass ${LIBXML2_LIBRARIES} ${OPENSSL_LIBRARIES} ${CURL_LIBRARIES})

# build plugin
find_package(ECM 5.12.0 REQUIRED NO_MODULE)
set(
        CMAKE_MODULE_PATH
        ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH}
)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED CONFIG COMPONENTS Widgets Core)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS Runner)

include(KDEInstallDirs)
include(KDECMakeSettings)

set(
        krunner_lastpass_srcs
        main.cpp
)

add_library(krunner_lastpass MODULE ${krunner_lastpass_srcs})

target_link_libraries(
        krunner_lastpass
        lastpass
        Qt5::Widgets
        KF5::Runner
)

install(TARGETS krunner_lastpass DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES krunner-lastpass.desktop DESTINATION ${SERVICES_INSTALL_DIR})
