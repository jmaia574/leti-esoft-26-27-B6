project(Core)

add_library(Core
        # Shared components
        headers/domain/shared/Result.h
        headers/domain/shared/StringUtils.h
        sources/domain/shared/Result.cpp
        sources/domain/shared/StringUtils.cpp

        # US11 - Register Parameter
        headers/domain/parameter/Parameter.h
        sources/domain/parameter/Parameter.cpp
        headers/domain/parameter/ParameterRepository.h
        sources/domain/parameter/ParameterRepository.cpp
        headers/domain/parameter/RegisterParameter.h
        sources/domain/parameter/RegisterParameter.cpp

        # US10 - Register Test Type
        headers/domain/testType/TestType.h
        sources/domain/testType/TestType.cpp
        headers/domain/testType/TestTypeContainer.h
        sources/domain/testType/TestTypeContainer.cpp
        headers/application/App.h
        sources/application/App.cpp
        headers/application/testType/RegisterTestTypeController.h
        sources/application/testType/RegisterTestTypeController.cpp
        headers/presentation/RegisterTestTypeView.h
        sources/presentation/RegisterTestTypeView.cpp

        # US13 - List Employees by Role
        headers/domain/employee/Employee.h
        sources/domain/employee/Employee.cpp
        headers/domain/employee/EmployeeRepository.h
        sources/domain/employee/EmployeeRepository.cpp
        headers/domain/employee/ListEmployeesByRole.h
        sources/domain/employee/ListEmployeesByRole.cpp
)

# Make Core headers available to this library and its consumers
target_include_directories(Core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)