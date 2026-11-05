//
// Employee.h
// UK Labs Management System
// US13 - List Employees by Role
// LETI-ESOFT 2026/2027 - Team B6
//

#ifndef LETI_ESOFT_26_27_B6_EMPLOYEE_H
#define LETI_ESOFT_26_27_B6_EMPLOYEE_H

#include <string>

class Employee {
private:
    std::wstring ID;
    std::wstring name;
    std::wstring role;

public:
    // Constructor
    Employee(
            const std::wstring& ID,
            const std::wstring& name,
            const std::wstring& role
    );

    // Getters
    const std::wstring& getID() const;
    const std::wstring& getName() const;
    const std::wstring& getRole() const;
};

#endif // LETI_ESOFT_26_27_B6_EMPLOYEE_H