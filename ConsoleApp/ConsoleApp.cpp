//
// ConsoleApp.cpp
// UK Labs Management System
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#include <iostream>
#include <string>
#include <optional>
#include <stdexcept>
#include <sstream>
#include <cmath>

#include "domain/parameter/RegisterParameter.h"

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

// US11 - Register Parameter
void registerParameter(RegisterParameter& service) {
    std::wstring code;
    std::wstring name;
    std::wstring description;
    std::wstring metric;
    std::wstring option;
    std::wstring answer;

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

    // Reference values
    std::wcout << L"\nAdd reference values? (Y/N): ";

    if (!std::getline(std::wcin, answer)) {
        return;
    }

    if (answer == L"Y" || answer == L"y") {

        // AC11-2: Qualitative metrics cannot have reference values.
        if (metricType == MetricType::Qualitative) {
            std::wcout
                << L"\nRegistration failed: Reference values are only "
                << L"applicable to numeric metrics.\n";
            return;
        }

        double minValue;
        double maxValue;

        if (!readDouble(
                L"Minimum reference value: ",
                minValue)) {
            std::wcout
                << L"Invalid minimum reference value.\n";
            return;
        }

        if (!readDouble(
                L"Maximum reference value: ",
                maxValue)) {
            std::wcout
                << L"Invalid maximum reference value.\n";
            return;
        }

        minimum = minValue;
        maximum = maxValue;

    } else if (answer != L"N" && answer != L"n") {
        std::wcout << L"Invalid option.\n";
        return;
    }

    // Register parameter
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

// Main application
int main() {
    ParameterRepository repository;
    RegisterParameter service(repository);

    std::wstring option;

    do {
        std::wcout << L"\n========== UKLABSMS ==========\n";
        std::wcout << L"1 - Register Parameter (US11)\n";
        std::wcout << L"0 - Exit\n";
        std::wcout << L"Choose an option: ";

        if (!std::getline(std::wcin, option)) {
            break;
        }

        if (option == L"1") {
            registerParameter(service);

        } else if (option == L"0") {
            std::wcout << L"Exiting application...\n";

        } else {
            std::wcout << L"Invalid option.\n";
        }

    } while (option != L"0");

    return 0;
}