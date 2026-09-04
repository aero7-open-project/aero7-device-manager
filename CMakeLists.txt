cmake_minimum_required(VERSION 3.16)
project(Aero7DeviceManager VERSION 2.2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets DBus)

file(GLOB_RECURSE AERO7_PACK_ICON_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/icons/pack/*.png")

add_executable(aero7-device-manager
    resources/icons.qrc
    src/main.cpp
    src/model/DeviceCatalog.cpp
    src/model/DeviceModel.cpp
    src/model/DeviceOps.cpp
    src/scanner/SysfsScanner.cpp
    src/scanner/AirPodsScanner.cpp
    src/scanner/DeviceScanner.cpp
    src/monitor/UdevMonitor.cpp
    src/ui/MainWindow.cpp
    src/ui/DevicePropertiesDialog.cpp
    src/ui/DriverDetailsDialog.cpp
    src/ui/UpdateDriverDialog.cpp
)
qt_add_resources(aero7-device-manager "aero7-device-manager-pack-icons"
    PREFIX "/aero7/pack"
    BASE "${CMAKE_CURRENT_SOURCE_DIR}/assets/icons/pack"
    FILES ${AERO7_PACK_ICON_FILES})

target_include_directories(aero7-device-manager PRIVATE
    src/model
    src/scanner
    src/monitor
    src/ui
)

target_link_libraries(aero7-device-manager PRIVATE Qt6::Widgets Qt6::DBus)

install(TARGETS aero7-device-manager RUNTIME DESTINATION bin)
install(FILES aero7-device-manager.desktop DESTINATION share/applications)
foreach(size 16 24 32 48 64 256)
    install(FILES assets/icons/pack/${size}/computer.png
        DESTINATION share/icons/hicolor/${size}x${size}/apps
        RENAME aero7-device-manager.png)
endforeach()
install(FILES assets/icons/LICENSES.md assets/icons/pack/UPSTREAM-LICENSE
    assets/icons/pack/UPSTREAM-README.md
    DESTINATION share/doc/aero7-device-manager)

enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_test(NAME searchable-device-catalog COMMAND aero7-device-manager --list-settings-json)
set_tests_properties(searchable-device-catalog PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
add_test(NAME invalid-device-section COMMAND aero7-device-manager --open not-a-section)
set_tests_properties(invalid-device-section PROPERTIES
    WILL_FAIL TRUE ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
add_executable(device-manager-icon-independence
    tests/IconIndependenceTest.cpp resources/icons.qrc)
qt_add_resources(device-manager-icon-independence "aero7-device-manager-pack-icons-test"
    PREFIX "/aero7/pack"
    BASE "${CMAKE_CURRENT_SOURCE_DIR}/assets/icons/pack"
    FILES ${AERO7_PACK_ICON_FILES})
target_include_directories(device-manager-icon-independence PRIVATE src/ui)
target_link_libraries(device-manager-icon-independence PRIVATE Qt6::Widgets)
add_test(NAME device-manager-icon-independence COMMAND device-manager-icon-independence)
set_tests_properties(device-manager-icon-independence PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
add_test(NAME device-manager-icon-policy
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_icon_policy.py)
