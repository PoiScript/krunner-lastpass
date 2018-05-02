cmake_minimum_required(VERSION 2.8.12)
project(RunnerLpass)

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
        lastpass-cli/process.h
        lastpass-cli/xml.h
        lastpass-cli/endpoints-login.h
        lastpass-cli/notes.h
        lastpass-cli/config.h
        lastpass-cli/blob.h
        lastpass-cli/edit.h
        lastpass-cli/log.h
        lastpass-cli/format.h
        lastpass-cli/pbkdf2.h
        lastpass-cli/session.h
        lastpass-cli/upload-queue.h
        lastpass-cli/terminal.h
        lastpass-cli/http.h
        lastpass-cli/agent.h
        lastpass-cli/util.h
        lastpass-cli/cmd.h
        lastpass-cli/cipher.h
        lastpass-cli/kdf.h
        lastpass-cli/endpoints.h
        lastpass-cli/endpoints-share.h
        lastpass-cli/password.h
        )
file(GLOB PROJECT_SOURCES
        lastpass-cli/process.c
        lastpass-cli/xml.c
        lastpass-cli/endpoints-login.c
        lastpass-cli/notes.c
        lastpass-cli/config.c
        lastpass-cli/blob.c
        lastpass-cli/clipboard.c
        lastpass-cli/edit.c
        lastpass-cli/log.c
        lastpass-cli/format.c
        lastpass-cli/pbkdf2.c
        lastpass-cli/session.c
        lastpass-cli/upload-queue.c
        lastpass-cli/terminal.c
        lastpass-cli/http.c
        lastpass-cli/agent.c
        lastpass-cli/util.c
        lastpass-cli/cmd.c
        lastpass-cli/cipher.c
        lastpass-cli/kdf.c
        lastpass-cli/endpoints.c
        lastpass-cli/json-format.c
        lastpass-cli/endpoints-share.c
        lastpass-cli/password.c
        )

add_library(lastpass SHARED ${PROJECT_HEADERS} ${PROJECT_SOURCES})

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


find_package(Qt5 ${QT_MIN_VERSION} REQUIRED CONFIG COMPONENTS Widgets Core Network Quick QuickWidgets)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS I18n Service Runner TextWidgets ConfigWidgets PlasmaQuick)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

set(
        krunner_lpass_srcs
        main.cpp
)

add_library(krunner_lpass MODULE ${krunner_lpass_srcs})

target_link_libraries(
        krunner_lpass
        lastpass
        Qt5::Widgets
        Qt5::Network
        KF5::Runner
        KF5::I18n
        KF5::Service
        KF5::ConfigWidgets
        KF5::Plasma
)

install(TARGETS krunner_lpass DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-lpass.desktop DESTINATION ${SERVICES_INSTALL_DIR})
