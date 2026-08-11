cmake_minimum_required(VERSION 3.16)
project(DeviceManager VERSION 2.2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets DBus)

add_executable(devmgmt
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

target_include_directories(devmgmt PRIVATE
    src/model
    src/scanner
    src/monitor
    src/ui
)

target_link_libraries(devmgmt PRIVATE Qt6::Widgets Qt6::DBus)

install(TARGETS devmgmt RUNTIME DESTINATION bin)
install(FILES linux-devmgmt.desktop DESTINATION share/applications)

enable_testing()
add_test(NAME searchable-device-catalog COMMAND devmgmt --list-settings-json)
set_tests_properties(searchable-device-catalog PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
add_test(NAME invalid-device-section COMMAND devmgmt --open not-a-section)
set_tests_properties(invalid-device-section PROPERTIES
    WILL_FAIL TRUE ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
