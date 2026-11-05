//
// ConsoleApp.cpp
// UK Labs Management System
// US10 - Register Test Type
// US11 - Register Parameter
// US13 - List Employees by Role
// LETI-ESOFT 2026/2027 - Team B6
//

#include <iostream>
#include <string>
#include <optional>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <vector>

#include "domain/parameter/RegisterParameter.h"
#include "domain/testType/RegisterTestType.h"
#include "domain/employee/EmployeeRepository.h"
#include "domain/employee/ListEmployeesByRole.h"

// =====================================================
// Shared console utilities
// =====================================================

// Read a numeric value from the console.
bool readDouble(const std::wstring& prompt, double& value) {
    std::wcout << prompt;

    std::wstring input;
    if (!std::getline(std::wcin, input)) {
        return false;
    }

    std::wistringstream stream(input);
    stream >> value;

    if (stream.fail()) {
        return false;
    }

    // Reject additional characters after the number.
    stream >> std::ws;

    if (!stream.eof()) {
        return false;
    }

    return std::isfinite(value);
}

// =====================================================
// US11 - Register Parameter
// =====================================================

void registerParameter(RegisterParameter& service) {
    std::wstring code;
    std::wstring name;
    std::wstring description;
    std::wstring metric;
    std::wstring option;

    std::wcout << L"\n===== US11 - REGISTER PARAMETER =====\n";

    // Parameter code
    std::wcout << L"Code: ";
    if (!std::getline(std::wcin, code)) {
        return;
    }

    // Parameter name
    std::wcout << L"Name: ";
    if (!std::getline(std::wcin, name)) {
        return;
    }

    // Parameter description
    std::wcout << L"Description: ";
    if (!std::getline(std::wcin, description)) {
        return;
    }

    // Metric
    std::wcout << L"Metric: ";
    if (!std::getline(std::wcin, metric)) {
        return;
    }

    // Explicit metric classification
    std::wcout << L"\nMetric type:\n";
    std::wcout << L"1 - Numeric\n";
    std::wcout << L"2 - Qualitative\n";
    std::wcout << L"Choose an option: ";

    if (!std::getline(std::wcin, option)) {
        return;
    }

    MetricType metricType;

    if (option == L"1") {
        metricType = MetricType::Numeric;

    } else if (option == L"2") {
        metricType = MetricType::Qualitative;

    } else {
        std::wcout << L"Invalid metric type.\n";
        return;
    }

    std::optional<double> minimum;
    std::optional<double> maximum;

    // =====================================================
    // Mandatory reference values for Numeric metrics
    // =====================================================

    if (metricType == MetricType::Numeric) {

        std::wcout
            << L"\nNumeric parameters require both "
            << L"minimum and maximum reference values.\n";

        double minValue;
        double maxValue;

        // Minimum reference value
        if (!readDouble(
                L"Minimum reference value: ",
                minValue)) {

            std::wcout
                << L"\nRegistration failed: "
                << L"Invalid minimum reference value.\n";

            return;
        }

        // Maximum reference value
        if (!readDouble(
                L"Maximum reference value: ",
                maxValue)) {

            std::wcout
                << L"\nRegistration failed: "
                << L"Invalid maximum reference value.\n";

            return;
        }

        // Validate reference interval
        if (minValue > maxValue) {

            std::wcout
                << L"\nRegistration failed: "
                << L"Minimum reference value cannot "
                << L"exceed maximum reference value.\n";

            return;
        }

        minimum = minValue;
        maximum = maxValue;

    } else {

        // Qualitative metrics cannot have numeric reference values.
        std::wcout
            << L"\nQualitative metric selected. "
            << L"No numeric reference values required.\n";
    }

    // =====================================================
    // Register parameter
    // =====================================================

    try {
        bool success = service.execute(
            code,
            name,
            description,
            metric,
            metricType,
            minimum,
            maximum
        );

        if (success) {

            std::wcout
                << L"\nParameter registered successfully!\n";

        } else {

            std::wcout
                << L"\nError: Parameter code already exists.\n";
        }

    } catch (const std::invalid_argument& exception) {

        std::wcout
            << L"\nRegistration failed: ";

        // Exception messages are ASCII in our domain validation.
        const std::string message = exception.what();

        for (char character : message) {
            std::wcout << static_cast<wchar_t>(character);
        }

        std::wcout << L'\n';
    }
}

// =====================================================
// US10 - Register Test Type
// =====================================================

void registerTestType(RegisterTestType& service) {
    std::wstring internalCode;
    std::wstring nhsCode;
    std::wstring collectionMethodDescription;

    std::wcout << L"\n===== US10 - REGISTER TEST TYPE =====\n";

    std::wcout << L"Internal Code: ";
    if (!std::getline(std::wcin, internalCode)) {
        return;
    }

    std::wcout << L"NHS Code: ";
    if (!std::getline(std::wcin, nhsCode)) {
        return;
    }

    std::wcout << L"Description identifying the sample collection method: ";
    if (!std::getline(std::wcin, collectionMethodDescription)) {
        return;
    }

    try {
        if (service.execute(
                internalCode,
                nhsCode,
                collectionMethodDescription)) {

            std::wcout
                << L"\nTest type registered successfully.\n";

        } else {

            std::wcout
                << L"\nRegistration failed: Internal Code or NHS Code "
                << L"already exists.\n";
        }

    } catch (const std::invalid_argument& exception) {

        std::wcout << L"\nRegistration failed: ";

        const std::string message = exception.what();

        for (char character : message) {
            std::wcout << static_cast<wchar_t>(character);
        }

        std::wcout << L'\n';
    }
}

// =====================================================
// US13 - List Employees by Role
// =====================================================

void listEmployeesByRole(const ListEmployeesByRole& service) {
    std::wstring role;

    std::wcout << L"\n===== US13 - LIST EMPLOYEES BY ROLE =====\n";

    std::wcout << L"Enter employee role: ";

    if (!std::getline(std::wcin, role)) {
        return;
    }

    if (role.empty()) {
        std::wcout
            << L"\nError: Employee role cannot be empty.\n";
        return;
    }

    // Retrieve employees matching the selected role.
    std::vector<Employee> employees = service.execute(role);

    if (employees.empty()) {

        std::wcout
            << L"\nNo employees found for the selected role.\n";

        return;
    }

    std::wcout << L"\n===== EMPLOYEES =====\n";
    std::wcout << L"Role: " << role << L"\n";
    std::wcout << L"Total employees: "
               << employees.size() << L"\n";

    for (const Employee& employee : employees) {

        std::wcout << L"\n-----------------------------\n";
        std::wcout << L"Code: " << employee.getCode() << L"\n";
        std::wcout << L"Name: " << employee.getName() << L"\n";
        std::wcout << L"Role: " << employee.getRole() << L"\n";
    }

    std::wcout << L"-----------------------------\n";
}

// =====================================================
// Main application
// =====================================================

int main() {

    // US10 - Test-type registration
    TestTypeRepository testTypeRepository;
    RegisterTestType registerTestTypeService(testTypeRepository);

    // US11 - Parameter registration
    ParameterRepository parameterRepository;
    RegisterParameter registerParameterService(parameterRepository);

    // US13 - Employee consultation
    EmployeeRepository employeeRepository;
    ListEmployeesByRole listEmployeesService(employeeRepository);

    std::wstring option;

    do {

        std::wcout << L"\n========== UKLABSMS ==========\n";
        std::wcout << L"1 - Register Test Type (US10)\n";
        std::wcout << L"2 - Register Parameter (US11)\n";
        std::wcout << L"3 - List Employees by Role (US13)\n";
        std::wcout << L"0 - Exit\n";
        std::wcout << L"Choose an option: ";

        if (!std::getline(std::wcin, option)) {
            break;
        }

        if (option == L"1") {

            registerTestType(registerTestTypeService);

        } else if (option == L"2") {

            registerParameter(registerParameterService);

        } else if (option == L"3") {

            listEmployeesByRole(listEmployeesService);

        } else if (option == L"0") {

            std::wcout << L"Exiting application...\n";

        } else {

            std::wcout << L"Invalid option.\n";
        }

    } while (option != L"0");

    return 0;
}