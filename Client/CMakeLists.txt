set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
    Client
)

set(CUSTOM_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedHeader.h")

execute_process(
    COMMAND python ${CRESSIE_SCRIPT_DIR}/HelloWorld.py ${CUSTOM_HEADER}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

target_sources(
    Client 
    PRIVATE
        ApiCore.cpp
        ApiCore.h
        LoginDialog.cpp
        LoginDialog.h
        ContentView.cpp
        ContentView.h
        ContentList.h
        ContentList.cpp
        MainWindow.cpp
        Main.cpp
        MainWindow.ui
        ${CUSTOM_HEADER}
)

target_link_libraries(
    Client
    PUBLIC
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Network
)
    