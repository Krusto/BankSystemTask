project(BankSystem)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE BANKSYSTEMLIB_SOURCE_FILES ${CMAKE_SOURCE_DIR}/BankSystemLib/*.cpp)
file(GLOB_RECURSE BANKSYSTEMLIB_HEADER_FILES ${CMAKE_SOURCE_DIR}/BankSystemLib/*.hpp)

set(BANKSYSTEMLIB_INCLUDE ${CMAKE_SOURCE_DIR}/BankSystemLib)

add_library(BankSystemLib STATIC ${BANKSYSTEMLIB_SOURCE_FILES} ${BANKSYSTEMLIB_HEADER_FILES})

add_executable(Sandbox ${CMAKE_SOURCE_DIR}/Sandbox/main.cpp)
target_include_directories(Sandbox PRIVATE ${BANKSYSTEMLIB_INCLUDE})
target_link_libraries(Sandbox BankSystemLib)

enable_testing()

option(ENABLE_COVERAGE "Enable LLVM code coverage" OFF)

if(ENABLE_COVERAGE)
    message(STATUS "Code coverage enabled")
    set(COVERAGE_COMPILE_FLAGS -fprofile-instr-generate -fcoverage-mapping)
    set(COVERAGE_LINK_FLAGS -fprofile-instr-generate)
endif()

add_executable(main_test tests/main_test.cpp)
target_link_libraries(main_test PRIVATE BankSystemLib GTest::gtest_main)
target_include_directories(main_test PRIVATE ${BANKSYSTEMLIB_INCLUDE})
if(ENABLE_COVERAGE)

    target_compile_options(BankSystemLib PRIVATE ${COVERAGE_COMPILE_FLAGS})
    target_link_options(BankSystemLib PRIVATE ${COVERAGE_LINK_FLAGS})

    target_compile_options(main_test PRIVATE ${COVERAGE_COMPILE_FLAGS})
    target_link_options(main_test PRIVATE ${COVERAGE_LINK_FLAGS})

    set(PROFRAW_MAIN "default.profraw")
    set(PROFRAW_TESTS "tests.profraw")
    set(PROFDATA_FILE "coverage.profdata")

    add_custom_target(run_main_program
        COMMAND LLVM_PROFILE_FILE=${CMAKE_BINARY_DIR}/${PROFRAW_MAIN} ./BankSystem
        COMMENT "Running main program to generate ${PROFRAW_MAIN}"
    )

    add_custom_target(run_tests
        COMMAND LLVM_PROFILE_FILE=${CMAKE_BINARY_DIR}/${PROFRAW_TESTS} ./main_test
        COMMENT "Running tests to generate ${PROFRAW_TESTS}"
    )

    add_custom_target(merge_coverage_data
        COMMAND llvm-profdata-19 merge -sparse -output=${CMAKE_BINARY_DIR}/${PROFDATA_FILE} ${CMAKE_BINARY_DIR}/${PROFRAW_MAIN} ${CMAKE_BINARY_DIR}/${PROFRAW_TESTS}
        DEPENDS run_main_program run_tests
        COMMENT "Merging coverage data into ${PROFDATA_FILE}"
    )

    add_custom_target(generate_coverage_report
        COMMAND llvm-cov-19 show ./Sandbox -instr-profile=${CMAKE_BINARY_DIR}/${PROFDATA_FILE} -format=html -output-dir=${CMAKE_BINARY_DIR}/coverage_report --show-branches=count --show-expansions
        DEPENDS merge_coverage_data
        COMMENT "Generating HTML coverage report in ${CMAKE_BINARY_DIR}/coverage_report"
    )

    add_dependencies(run_main_program Sandbox)
    add_dependencies(run_tests main_test)
    add_dependencies(generate_coverage_report merge_coverage_data)
endif()

include(GoogleTest)
gtest_discover_tests(main_test)
