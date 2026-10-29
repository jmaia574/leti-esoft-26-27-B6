project(CoreTests)

add_subdirectory(lib)

include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)

add_executable(CoreTests
        # Existing tests
        domain/shared/StringUtilsTests.cpp

        # US11 - Register Parameter
        domain/parameter/ParameterTests.cpp

        # US13 - List Employees by Role
        domain/employee/EmployeeTests.cpp
)

target_link_libraries(CoreTests Core)
target_link_libraries(CoreTests gtest gtest_main)