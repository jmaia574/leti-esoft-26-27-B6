//
// EmployeeRepository.h
// UK Labs Management System
// US13 - List Employees by Role
// LETI-ESOFT 2026/2027 - Team B6
//

#ifndef LETI_ESOFT_26_27_B6_EMPLOYEEREPOSITORY_H
#define LETI_ESOFT_26_27_B6_EMPLOYEEREPOSITORY_H

#include "domain/employee/Employee.h"

#include <vector>
#include <string>
#include <cstddef>

class EmployeeRepository {
private:
    std::vector<Employee> employees;

public:
    // Add an employee to the repository.
    bool add(const Employee& employee);

    // Find employees with the specified role.
    std::vector<Employee> findByRole(const std::wstring& role) const;

    // Check whether an employee code already exists.
    bool existsByCode(const std::wstring& code) const;

    // Return the total number of employees.
    std::size_t count() const;
};

#endif // LETI_ESOFT_26_27_B6_EMPLOYEEREPOSITORY_H