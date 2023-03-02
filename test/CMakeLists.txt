set(library_project_name threadator)

get_target_property(library_include_dirs "${library_project_name}" INTERFACE_INCLUDE_DIRECTORIES)

set(test_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/method.cpp"
)

if(BUILD_COVERAGE)
    set(FIXTURES_COVERAGE_LIST)
endif()

foreach(file ${test_source_files})
    get_filename_component(filenamewe "${file}" NAME_WE)
    add_executable("${filenamewe}.gtest" "${file}")
    set_target_properties("${filenamewe}.gtest" PROPERTIES
        CXX_STANDARD "${CMAKE_CXX_STANDARD}"
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
        COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
        INCLUDE_DIRECTORIES "${library_include_dirs};${CMAKE_CURRENT_SOURCE_DIR}/include"
        LINK_LIBRARIES "gmock_main;gmock;pthread"
    )
    add_test(NAME "${filenamewe}.gtest" COMMAND "$<TARGET_FILE:${filenamewe}.gtest>")
endforeach()

find_program(VALGRIND "valgrind")
if (VALGRIND)
    set(DART_CONFIG DartConfiguration.tcl)
    add_custom_target(${DART_CONFIG}
        COMMAND echo "MemoryCheckCommand: ${VALGRIND}" >> ${DART_CONFIG}
        COMMENT "Generating ${DART_CONFIG}"
    )
    set(VALGRIND_ARGS
        --leak-check=full
        --error-exitcode=255
    )
    set(LOGFILE memcheck.log)
    add_custom_target(valgrind
        COMMAND ${CMAKE_CTEST_COMMAND} -O ${LOGFILE} -D ExperimentalMemCheck --overwrite MemoryCheckCommandOptions="${VALGRIND_ARGS}" -j 16 -T memcheck -LE "^noMemcheck$"
        COMMAND tail -n1 ${LOGFILE} | grep 'Memory checking results:' > /dev/null
        COMMAND rm -f ${LOGFILE}
        DEPENDS ${DART_CONFIG}
    )
endif()