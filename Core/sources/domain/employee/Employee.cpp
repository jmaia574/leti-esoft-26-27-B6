//
// Employee.cpp
// UK Labs Management System
// US13 - List Employees by Role
// LETI-ESOFT 2026/2027 - Team B6
//

#include "domain/employee/Employee.h"

#include <utility>

// Constructor
Employee::Employee(
        const std::wstring& code,
        const std::wstring& name,
        const std::wstring& role
)
        : code(code),
          name(name),
          role(role)
{
}

// Getters
const std::wstring& Employee::getCode() const {
    return code;
}

const std::wstring& Employee::getName() const {
    return name;
}

const std::wstring& Employee::getRole() const {
    return role;
}