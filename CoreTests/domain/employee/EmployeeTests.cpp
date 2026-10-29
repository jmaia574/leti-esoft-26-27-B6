//
// EmployeeTests.cpp
// US13 - List Employees by Role
// LETI-ESOFT 2026/2027 - Team B6
//

#include <gtest/gtest.h>

#include "domain/employee/Employee.h"
#include "domain/employee/EmployeeRepository.h"
#include "domain/employee/ListEmployeesByRole.h"

// =====================================================
// Employee entity tests
// =====================================================

TEST(EmployeeTests, StoresEmployeeInformation) {
Employee employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
);

EXPECT_EQ(employee.getCode(), L"EMP01");
EXPECT_EQ(employee.getName(), L"John Smith");
EXPECT_EQ(employee.getRole(), L"Receptionist");
}

// =====================================================
// EmployeeRepository tests
// =====================================================

TEST(EmployeeRepositoryTests, AddsEmployeeSuccessfully) {
EmployeeRepository repository;

Employee employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
);

EXPECT_TRUE(repository.add(employee));
EXPECT_EQ(repository.count(), 1);
}

TEST(EmployeeRepositoryTests, RejectsDuplicateEmployeeCode) {
EmployeeRepository repository;

Employee first(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
);

Employee second(
        L"EMP01",
        L"Mary Johnson",
        L"Lab Technician"
);

EXPECT_TRUE(repository.add(first));
EXPECT_FALSE(repository.add(second));
EXPECT_EQ(repository.count(), 1);
}

TEST(EmployeeRepositoryTests, FindsEmployeesByRole) {
EmployeeRepository repository;

repository.add(Employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
));

repository.add(Employee(
        L"EMP02",
        L"Mary Johnson",
        L"Lab Technician"
));

std::vector<Employee> result =
        repository.findByRole(L"Receptionist");

ASSERT_EQ(result.size(), 1);
EXPECT_EQ(result[0].getCode(), L"EMP01");
EXPECT_EQ(result[0].getName(), L"John Smith");
}

TEST(EmployeeRepositoryTests, ReturnsMultipleEmployeesWithSameRole) {
EmployeeRepository repository;

repository.add(Employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
));

repository.add(Employee(
        L"EMP02",
        L"Mary Johnson",
        L"Receptionist"
));

repository.add(Employee(
        L"EMP03",
        L"Peter Brown",
        L"Lab Technician"
));

std::vector<Employee> result =
        repository.findByRole(L"Receptionist");

ASSERT_EQ(result.size(), 2);

EXPECT_EQ(result[0].getCode(), L"EMP01");
EXPECT_EQ(result[1].getCode(), L"EMP02");
}

TEST(EmployeeRepositoryTests, ReturnsEmptyListForUnknownRole) {
EmployeeRepository repository;

repository.add(Employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
));

std::vector<Employee> result =
        repository.findByRole(L"Administrator");

EXPECT_TRUE(result.empty());
}

TEST(EmployeeRepositoryTests, ReturnsEmptyListWhenRepositoryIsEmpty) {
EmployeeRepository repository;

std::vector<Employee> result =
        repository.findByRole(L"Receptionist");

EXPECT_TRUE(result.empty());
EXPECT_EQ(repository.count(), 0);
}

TEST(EmployeeRepositoryTests, ChecksEmployeeCodeExistence) {
EmployeeRepository repository;

repository.add(Employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
));

EXPECT_TRUE(repository.existsByCode(L"EMP01"));
EXPECT_FALSE(repository.existsByCode(L"EMP99"));
}

// =====================================================
// US13 - ListEmployeesByRole service tests
// =====================================================

TEST(ListEmployeesByRoleTests, ListsEmployeesForSelectedRole) {
EmployeeRepository repository;

repository.add(Employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
));

repository.add(Employee(
        L"EMP02",
        L"Mary Johnson",
        L"Lab Technician"
));

ListEmployeesByRole service(repository);

std::vector<Employee> result =
        service.execute(L"Receptionist");

ASSERT_EQ(result.size(), 1);
EXPECT_EQ(result[0].getName(), L"John Smith");
}

TEST(ListEmployeesByRoleTests, DoesNotModifyRepository) {
EmployeeRepository repository;

repository.add(Employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
));

repository.add(Employee(
        L"EMP02",
        L"Mary Johnson",
        L"Receptionist"
));

ListEmployeesByRole service(repository);

const std::size_t originalCount = repository.count();

std::vector<Employee> result =
        service.execute(L"Receptionist");

EXPECT_EQ(result.size(), 2);
EXPECT_EQ(repository.count(), originalCount);
}

// =====================================================
// Additional edge-case tests
// =====================================================

TEST(ListEmployeesByRoleTests, ReturnsEmptyListForUnknownRole) {
EmployeeRepository repository;

repository.add(Employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
));

ListEmployeesByRole service(repository);

std::vector<Employee> result =
        service.execute(L"Pathologist");

EXPECT_TRUE(result.empty());
}

TEST(EmployeeRepositoryTests, RoleMatchingIsCaseSensitive) {
EmployeeRepository repository;

repository.add(Employee(
        L"EMP01",
        L"John Smith",
        L"Receptionist"
));

std::vector<Employee> result =
        repository.findByRole(L"receptionist");

EXPECT_TRUE(result.empty());
}