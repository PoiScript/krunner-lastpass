cmake_minimum_required(VERSION 2.8.12)
project(RunnerLpass)

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
        krunner_lpass KF5::Runner Qt5::Widgets Qt5::Network
        KF5::I18n
        KF5::Service
        KF5::ConfigWidgets
        KF5::Plasma
)

install(TARGETS krunner_lpass DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-lpass.desktop DESTINATION ${SERVICES_INSTALL_DIR})
