add_subdirectory(ApiCore)

install(
    EXPORT Objects-config
    NAMESPACE objects::
    DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake
)
