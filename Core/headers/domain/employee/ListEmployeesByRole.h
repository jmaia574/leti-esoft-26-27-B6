//
// ListEmployeesByRole.h
// UK Labs Management System
// US13 - List Employees by Role
// LETI-ESOFT 2026/2027 - Team B6
//

#ifndef LETI_ESOFT_26_27_B6_LISTEMPLOYEESBYROLE_H
#define LETI_ESOFT_26_27_B6_LISTEMPLOYEESBYROLE_H

#include "domain/employee/EmployeeRepository.h"

#include <string>
#include <vector>

class ListEmployeesByRole {
private:
    const EmployeeRepository& repository;

public:
    // Constructor
    explicit ListEmployeesByRole(
            const EmployeeRepository& repository
    );

    // Return employees matching the selected role.
    std::vector<Employee> execute(
            const std::wstring& role
    ) const;
};

#endif // LETI_ESOFT_26_27_B6_LISTEMPLOYEESBYROLE_H