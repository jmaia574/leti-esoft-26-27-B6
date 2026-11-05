#include <gtest/gtest.h>

#include "domain/testType/RegisterTestType.h"
#include "domain/testType/TestType.h"
#include "domain/testType/TestTypeRepository.h"

#include <stdexcept>

TEST(TestTypeTests, StoresAllAssignmentDefinedAttributes) {
    const TestType testType(L"0123", L"A1b2C", L"Blood sample collection");

    EXPECT_EQ(testType.getInternalCode(), L"0123");
    EXPECT_EQ(testType.getNhsCode(), L"A1b2C");
    EXPECT_EQ(
        testType.getCollectionMethodDescription(),
        L"Blood sample collection"
    );
}

TEST(TestTypeTests, AcceptsInternalCodeWithExactlyFourDigits) {
    EXPECT_TRUE(TestType::isValidInternalCode(L"0123"));
}

TEST(TestTypeTests, RejectsInvalidInternalCodeValues) {
    EXPECT_FALSE(TestType::isValidInternalCode(L""));
    EXPECT_FALSE(TestType::isValidInternalCode(L"123"));
    EXPECT_FALSE(TestType::isValidInternalCode(L"12345"));
    EXPECT_FALSE(TestType::isValidInternalCode(L"12A3"));
    EXPECT_FALSE(TestType::isValidInternalCode(L"12 3"));
}

TEST(TestTypeTests, AcceptsNhsCodeWithFiveAlphanumericCharacters) {
    EXPECT_TRUE(TestType::isValidNhsCode(L"A1b2C"));
    EXPECT_TRUE(TestType::isValidNhsCode(L"12345"));
}

TEST(TestTypeTests, RejectsInvalidNhsCodeValues) {
    EXPECT_FALSE(TestType::isValidNhsCode(L""));
    EXPECT_FALSE(TestType::isValidNhsCode(L"AB12"));
    EXPECT_FALSE(TestType::isValidNhsCode(L"ABC123"));
    EXPECT_FALSE(TestType::isValidNhsCode(L"AB@12"));
    EXPECT_FALSE(TestType::isValidNhsCode(L"AB 12"));
}

TEST(TestTypeTests, ConstructorRejectsInvalidInternalCode) {
    EXPECT_THROW(
        TestType(L"12A3", L"A1b2C", L"Sample collection"),
        std::invalid_argument
    );
}

TEST(TestTypeTests, ConstructorRejectsInvalidNhsCode) {
    EXPECT_THROW(
        TestType(L"0123", L"AB@12", L"Sample collection"),
        std::invalid_argument
    );
}

TEST(TestTypeRepositoryTests, AddsTestTypeAndFindsByInternalCode) {
    TestTypeRepository repository;
    const TestType testType(L"0123", L"A1b2C", L"Sample collection");

    EXPECT_TRUE(repository.add(testType));
    ASSERT_NE(repository.findByInternalCode(L"0123"), nullptr);
    EXPECT_EQ(repository.count(), 1);
}

TEST(TestTypeRepositoryTests, RejectsDuplicateInternalCode) {
    TestTypeRepository repository;
    const TestType first(L"0123", L"A1b2C", L"First collection method");
    const TestType duplicate(L"0123", L"Z9y8X", L"Second collection method");

    EXPECT_TRUE(repository.add(first));
    EXPECT_FALSE(repository.add(duplicate));
    EXPECT_EQ(repository.count(), 1);
}

TEST(TestTypeRepositoryTests, RejectsDuplicateNhsCode) {
    TestTypeRepository repository;
    const TestType first(L"0123", L"A1b2C", L"First collection method");
    const TestType duplicate(L"4567", L"A1b2C", L"Second collection method");

    EXPECT_TRUE(repository.add(first));
    EXPECT_FALSE(repository.add(duplicate));
    EXPECT_EQ(repository.count(), 1);
}

TEST(RegisterTestTypeTests, RegistersValidTestType) {
    TestTypeRepository repository;
    RegisterTestType service(repository);

    EXPECT_TRUE(service.execute(L"0123", L"A1b2C", L"Sample collection"));
    EXPECT_EQ(repository.count(), 1);
}

TEST(RegisterTestTypeTests, RetainsSubmittedAttributesAfterRegistration) {
    TestTypeRepository repository;
    RegisterTestType service(repository);

    ASSERT_TRUE(service.execute(L"0123", L"A1b2C", L"Sample collection"));

    const TestType* registered = repository.findByInternalCode(L"0123");
    ASSERT_NE(registered, nullptr);
    EXPECT_EQ(registered->getNhsCode(), L"A1b2C");
    EXPECT_EQ(
        registered->getCollectionMethodDescription(),
        L"Sample collection"
    );
}

TEST(RegisterTestTypeTests, RejectsDuplicateCodeWithoutChangingRepository) {
    TestTypeRepository repository;
    RegisterTestType service(repository);

    EXPECT_TRUE(service.execute(L"0123", L"A1b2C", L"First method"));
    EXPECT_FALSE(service.execute(L"4567", L"A1b2C", L"Second method"));
    EXPECT_EQ(repository.count(), 1);
}

TEST(RegisterTestTypeTests, RejectsDuplicateInternalCodeWithoutStorage) {
    TestTypeRepository repository;
    RegisterTestType service(repository);

    ASSERT_TRUE(service.execute(L"0123", L"A1b2C", L"First method"));
    EXPECT_FALSE(service.execute(L"0123", L"Z9y8X", L"Second method"));
    EXPECT_EQ(repository.count(), 1);
}

TEST(RegisterTestTypeTests, DoesNotStoreInvalidTestType) {
    TestTypeRepository repository;
    RegisterTestType service(repository);

    EXPECT_THROW(
        service.execute(L"123", L"A1b2C", L"Sample collection"),
        std::invalid_argument
    );
    EXPECT_EQ(repository.count(), 0);
}

TEST(RegisterTestTypeTests, DoesNotStoreTestTypeWithInvalidNhsCode) {
    TestTypeRepository repository;
    RegisterTestType service(repository);

    EXPECT_THROW(
        service.execute(L"0123", L"AB@12", L"Sample collection"),
        std::invalid_argument
    );
    EXPECT_EQ(repository.count(), 0);
}
