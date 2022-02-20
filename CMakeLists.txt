cmake_minimum_required(VERSION 3.6)

project(
    Photon
    VERSION 0.1
    LANGUAGES CXX
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Core Test Network REQUIRED)

set(CRESSIE_SCRIPT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Scripts")
add_definitions( ${QT_DEFINITIONS} )

include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_subdirectory(Libraries)
add_subdirectory(Objects)
add_subdirectory(Client)

enable_testing()

# add_subdirectory(Tests/TestClient)
