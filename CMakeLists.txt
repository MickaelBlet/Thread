cmake_minimum_required(VERSION 3.5)

project(blet_thread VERSION 1.2.1 LANGUAGES CXX)

# options
option(BUILD_EXAMPLE "Build example binaries" OFF)
option(BUILD_TESTING "Build test binaries" OFF)
option(BUILD_COVERAGE "Check coverage at end of test" OFF)
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 98 CACHE STRING "C++ standard to be used")
endif()
if(NOT CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib CACHE STRING "Install destination library directory")
endif()
if(NOT CMAKE_INSTALL_BINDIR)
    set(CMAKE_INSTALL_BINDIR bin CACHE STRING "Install destination binary directory")
endif()
if(NOT CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR include CACHE STRING "Install destination include directory")
endif()

add_library("${PROJECT_NAME}" INTERFACE)

set_target_properties("${PROJECT_NAME}"
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>;$<INSTALL_INTERFACE:include>"
)

# install
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake\")"
)

install(TARGETS "${PROJECT_NAME}" EXPORT "${PROJECT_NAME}Targets"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
install(EXPORT "${PROJECT_NAME}Targets"
        FILE "${PROJECT_NAME}Targets.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)

if(BUILD_TESTING)
    enable_testing()
endif()

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

# test
get_target_property(library_type "${PROJECT_NAME}" TYPE)
if(library_type STREQUAL "INTERFACE_LIBRARY" AND
   CMAKE_BUILD_TYPE STREQUAL "Debug" AND
   BUILD_TESTING)
    add_subdirectory(test)
endif()
