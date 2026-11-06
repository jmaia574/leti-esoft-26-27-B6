#include <gtest/gtest.h>

#include "domain/testType/TestType.h"
#include "domain/testType/TestTypeContainer.h"
#include "application/App.h"
#include "application/testType/RegisterTestTypeController.h"
#include "presentation/RegisterTestTypeView.h"

#include <sstream>
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

TEST(TestTypeContainerTests, CreatesAndSavesTestType) {
    TestTypeContainer container;
    const TestType testType(L"0123", L"A1b2C", L"Sample collection");

    EXPECT_TRUE(container.save(testType));
    ASSERT_NE(container.findByInternalCode(L"0123"), nullptr);
    EXPECT_EQ(container.count(), 1);
}

TEST(TestTypeContainerTests, RejectsDuplicateInternalCode) {
    TestTypeContainer container;
    const TestType first(L"0123", L"A1b2C", L"First collection method");
    const TestType duplicate(L"0123", L"Z9y8X", L"Second collection method");

    EXPECT_TRUE(container.save(first));
    EXPECT_FALSE(container.save(duplicate));
    EXPECT_EQ(container.count(), 1);
}

TEST(TestTypeContainerTests, RejectsDuplicateNhsCode) {
    TestTypeContainer container;
    const TestType first(L"0123", L"A1b2C", L"First collection method");
    const TestType duplicate(L"4567", L"A1b2C", L"Second collection method");

    EXPECT_TRUE(container.save(first));
    EXPECT_FALSE(container.save(duplicate));
    EXPECT_EQ(container.count(), 1);
}

TEST(TestTypeContainerTests, RejectsDuplicateNhsCodeIgnoringCase) {
    TestTypeContainer container;
    const TestType first(L"0123", L"AB123", L"First collection method");
    const TestType duplicate(L"4567", L"ab123", L"Second collection method");

    ASSERT_TRUE(container.save(first));
    EXPECT_TRUE(container.existsByNhsCode(L"aB123"));
    EXPECT_FALSE(container.save(duplicate));
    EXPECT_EQ(container.count(), 1);
}

TEST(TestTypeContainerTests, CreatesTestTypeWithValidatedAttributes) {
    TestTypeContainer container;

    const TestType testType = container.create(
        L"0123",
        L"A1b2C",
        L"Sample collection"
    );

    EXPECT_EQ(testType.getInternalCode(), L"0123");
}

TEST(AppTests, ReturnsTheSameApplicationInstance) {
    EXPECT_EQ(&App::getInstance(), &App::getInstance());
}

TEST(RegisterTestTypeControllerTests, UsesApplicationContainerByDefault) {
    RegisterTestTypeController controller;
    TestTypeContainer& container = App::getInstance().getTestTypeContainer();

    ASSERT_TRUE(controller.registerTestType(
        L"9876",
        L"Z9Y8X",
        L"Application container test"
    ));

    EXPECT_NE(container.findByInternalCode(L"9876"), nullptr);
}

TEST(RegisterTestTypeControllerTests, RegistersValidTestType) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);

    EXPECT_TRUE(controller.registerTestType(
        L"0123",
        L"A1b2C",
        L"Sample collection"
    ));
    EXPECT_EQ(container.count(), 1);
}

TEST(RegisterTestTypeControllerTests, RetainsSubmittedAttributes) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);

    ASSERT_TRUE(controller.registerTestType(
        L"0123",
        L"A1b2C",
        L"Sample collection"
    ));

    const TestType* registered = container.findByInternalCode(L"0123");
    ASSERT_NE(registered, nullptr);
    EXPECT_EQ(registered->getNhsCode(), L"A1b2C");
    EXPECT_EQ(
        registered->getCollectionMethodDescription(),
        L"Sample collection"
    );
}

TEST(RegisterTestTypeControllerTests, RejectsDuplicateNhsCodeIgnoringCase) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);

    EXPECT_TRUE(controller.registerTestType(
        L"0123",
        L"A1b2C",
        L"First method"
    ));
    EXPECT_FALSE(controller.registerTestType(
        L"4567",
        L"a1B2c",
        L"Second method"
    ));
    EXPECT_EQ(container.count(), 1);
}

TEST(RegisterTestTypeControllerTests, RejectsDuplicateInternalCode) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);

    ASSERT_TRUE(controller.registerTestType(
        L"0123",
        L"A1b2C",
        L"First method"
    ));
    EXPECT_FALSE(controller.registerTestType(
        L"0123",
        L"Z9y8X",
        L"Second method"
    ));
    EXPECT_EQ(container.count(), 1);
}

TEST(RegisterTestTypeControllerTests, DoesNotStoreInvalidTestType) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);

    EXPECT_THROW(
        controller.registerTestType(L"123", L"A1b2C", L"Sample collection"),
        std::invalid_argument
    );
    EXPECT_EQ(container.count(), 0);
}

TEST(RegisterTestTypeControllerTests, DoesNotStoreTestTypeWithInvalidNhsCode) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);

    EXPECT_THROW(
        controller.registerTestType(
            L"0123",
            L"AB@12",
            L"Sample collection"
        ),
        std::invalid_argument
    );
    EXPECT_EQ(container.count(), 0);
}

TEST(RegisterTestTypeViewTests, CollectsInputAndDisplaysSuccess) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);
    RegisterTestTypeView view(controller);
    std::wistringstream input(
        L"0123\nA1b2C\nSample collection\n"
    );
    std::wostringstream output;

    view.show(input, output);

    EXPECT_NE(
        output.str().find(L"Test type registered successfully"),
        std::wstring::npos
    );
    EXPECT_EQ(container.count(), 1);
}

TEST(RegisterTestTypeViewTests, DisplaysRejectionForDuplicateCode) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);
    RegisterTestTypeView view(controller);
    std::wistringstream firstInput(
        L"0123\nA1b2C\nFirst method\n"
    );
    std::wostringstream firstOutput;
    view.show(firstInput, firstOutput);

    std::wistringstream duplicateInput(
        L"4567\na1B2c\nSecond method\n"
    );
    std::wostringstream duplicateOutput;
    view.show(duplicateInput, duplicateOutput);

    EXPECT_NE(
        duplicateOutput.str().find(L"already exists"),
        std::wstring::npos
    );
    EXPECT_EQ(container.count(), 1);
}

TEST(RegisterTestTypeViewTests, DisplaysValidationFailure) {
    TestTypeContainer container;
    RegisterTestTypeController controller(container);
    RegisterTestTypeView view(controller);
    std::wistringstream input(
        L"12x3\nA1b2C\nSample collection\n"
    );
    std::wostringstream output;

    view.show(input, output);

    EXPECT_NE(
        output.str().find(L"Internal Code must contain exactly four digits"),
        std::wstring::npos
    );
    EXPECT_EQ(container.count(), 0);
}
