set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
    Client
)

target_sources(
    Client 
    PRIVATE
        LoginDialog.cpp
        ContentView.cpp
        ContentList.cpp
        MainWindow.cpp
        Main.cpp
        MainWindow.ui
)

target_link_libraries(
    Client
    PUBLIC
        ApiCore
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Network
)

target_include_directories(
    Client
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
    