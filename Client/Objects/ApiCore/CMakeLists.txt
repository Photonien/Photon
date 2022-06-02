add_library(
    ApiCore
)

target_link_libraries(
    ApiCore
    PRIVATE
        Qt5::Core
        Qt5::Widgets
        Qt5::Network
)

target_sources(
    ApiCore
    PRIVATE
        ApiCore.cpp
        ApiCore/ApiCore.h
)

target_include_directories(
    ApiCore 
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
    TARGETS ApiCore
    EXPORT Objects-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/ApiCore/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ApiCore
)