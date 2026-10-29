//
// EmployeeRepository.cpp
// UK Labs Management System
// US13 - List Employees by Role
// LETI-ESOFT 2026/2027 - Team B6
//

#include "domain/employee/EmployeeRepository.h"

// Add an employee to the repository.
bool EmployeeRepository::add(const Employee& employee) {

    // Prevent duplicate employee codes.
    if (existsByCode(employee.getCode())) {
        return false;
    }

    employees.push_back(employee);
    return true;
}

// Find employees with the specified role.
std::vector<Employee> EmployeeRepository::findByRole(
        const std::wstring& role
) const {
    std::vector<Employee> result;

    for (const Employee& employee : employees) {
        if (employee.getRole() == role) {
            result.push_back(employee);
        }
    }

    return result;
}

// Check whether an employee code already exists.
bool EmployeeRepository::existsByCode(
        const std::wstring& code
) const {
    for (const Employee& employee : employees) {
        if (employee.getCode() == code) {
            return true;
        }
    }

    return false;
}

// Return the total number of employees.
std::size_t EmployeeRepository::count() const {
    return employees.size();
}