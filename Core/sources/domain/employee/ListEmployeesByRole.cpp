//
// ListEmployeesByRole.cpp
// UK Labs Management System
// US13 - List Employees by Role
// LETI-ESOFT 2026/2027 - Team B6
//

#include "domain/employee/ListEmployeesByRole.h"

// Constructor
ListEmployeesByRole::ListEmployeesByRole(
        const EmployeeRepository& repository
)
        : repository(repository)
{
}

// Return employees matching the selected role.
std::vector<Employee> ListEmployeesByRole::execute(
        const std::wstring& role
) const {
    return repository.findByRole(role);
}