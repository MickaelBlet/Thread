set(library_project_name "${PROJECT_NAME}")

get_target_property(library_include_dirs "${library_project_name}" INTERFACE_INCLUDE_DIRECTORIES)

set(example_files
    "${CMAKE_CURRENT_SOURCE_DIR}/allType.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/memberMethod.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/quickstart.cpp"
)

foreach(file ${example_files})
    get_filename_component(filenamewe "${file}" NAME_WE)
    add_executable("${filenamewe}.example" "${file}")
    set_target_properties("${filenamewe}.example"
        PROPERTIES
            CXX_STANDARD "${CMAKE_CXX_STANDARD}"
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            NO_SYSTEM_FROM_IMPORTED ON
            COMPILE_FLAGS "-std=c++98 -pedantic -Wall -Wextra -Werror"
            INCLUDE_DIRECTORIES "${library_include_dirs}"
            LINK_LIBRARIES "pthread"
    )
endforeach()