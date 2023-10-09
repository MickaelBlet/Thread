cmake_minimum_required(VERSION 3.5)

project(blet_thread VERSION 1.2.0 LANGUAGES CXX)

# OPTIONS
option(BUILD_EXAMPLE "Build example binaries" OFF)
option(BUILD_TESTING "Build test binaries" OFF)
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 98 CACHE STRING "C++ standard to be used")
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
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION include
)
install(EXPORT "${PROJECT_NAME}Targets"
        NAMESPACE mblet::
        FILE "${PROJECT_NAME}Targets.cmake"
        DESTINATION "lib/cmake"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "lib/cmake"
)

if(BUILD_TESTING)
    enable_testing()
endif()

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

# test
if(BUILD_TESTING)
    add_subdirectory(test)
endif()