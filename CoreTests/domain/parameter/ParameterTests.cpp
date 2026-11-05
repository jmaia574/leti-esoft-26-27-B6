//
// US11 - Register Parameter
// Unit Tests - LETI-ESOFT 2026/2027 - Team B6
//

#include <gtest/gtest.h>

#include "domain/parameter/Parameter.h"
#include "domain/parameter/ParameterRepository.h"
#include "domain/parameter/RegisterParameter.h"

#include <optional>
#include <stdexcept>

// =====================================================
// AC11-1: Parameter code validation
// =====================================================

TEST(ParameterTests, AcceptsValidAlphanumericCode) {
    EXPECT_TRUE(Parameter::isValidCode(L"RBC01"));
    EXPECT_TRUE(Parameter::isValidCode(L"12345"));
    EXPECT_TRUE(Parameter::isValidCode(L"ABCDE"));
}

TEST(ParameterTests, RejectsCodeWithLessThanFiveCharacters) {
    EXPECT_FALSE(Parameter::isValidCode(L"ABC1"));
}

TEST(ParameterTests, RejectsCodeWithMoreThanFiveCharacters) {
    EXPECT_FALSE(Parameter::isValidCode(L"ABC123"));
}

TEST(ParameterTests, RejectsNonAlphanumericCharacters) {
    EXPECT_FALSE(Parameter::isValidCode(L"AB@12"));
    EXPECT_FALSE(Parameter::isValidCode(L"AB 12"));
    EXPECT_FALSE(Parameter::isValidCode(L"AB-12"));
}

TEST(ParameterTests, RejectsEmptyCode) {
    EXPECT_FALSE(Parameter::isValidCode(L""));
}

// =====================================================
// AC11-2: Reference values and numeric metrics
// =====================================================

TEST(ParameterTests, AcceptsNumericMetricWithReferenceValues) {
    EXPECT_NO_THROW({
        Parameter parameter(
            L"RBC01",
            L"Red Blood Cells",
            L"Red blood cell count",
            L"10^12/L",
            4.2,
            5.9
        );
    });
}

TEST(ParameterTests, AcceptsNonNumericMetricWithoutReferenceValues) {
    EXPECT_NO_THROW({
        Parameter parameter(
            L"COV01",
            L"COVID-19",
            L"COVID-19 test result",
            L"Positive/Negative"
        );
    });
}

TEST(ParameterTests, RejectsNonNumericMetricWithReferenceValues) {
    EXPECT_THROW({
        Parameter parameter(
            L"COV01",
            L"COVID-19",
            L"COVID-19 test result",
            L"Positive/Negative",
            0.0,
            1.0
        );
    }, std::invalid_argument);
}

TEST(ParameterTests, RejectsInvalidReferenceRange) {
    EXPECT_FALSE(
        Parameter::isValidReferenceRange(10.0, 5.0)
    );
}

TEST(ParameterTests, AcceptsValidReferenceRange) {
    EXPECT_TRUE(
        Parameter::isValidReferenceRange(4.2, 5.9)
    );
}

// =====================================================
// Additional acceptance criteria: Mandatory fields
// =====================================================

TEST(ParameterTests, RejectsEmptyName) {
    EXPECT_THROW({
        Parameter parameter(
            L"RBC01",
            L"",
            L"Red blood cell count",
            L"10^12/L",
            4.2,
            5.9
        );
    }, std::invalid_argument);
}

TEST(ParameterTests, RejectsEmptyDescription) {
    EXPECT_THROW({
        Parameter parameter(
            L"RBC01",
            L"Red Blood Cells",
            L"",
            L"10^12/L",
            4.2,
            5.9
        );
    }, std::invalid_argument);
}

TEST(ParameterTests, RejectsEmptyMetric) {
    EXPECT_THROW({
        Parameter parameter(
            L"RBC01",
            L"Red Blood Cells",
            L"Red blood cell count",
            L"",
            MetricType::Numeric,
            4.2,
            5.9
        );
    }, std::invalid_argument);
}

// =====================================================
// Repository tests: Code uniqueness
// =====================================================

TEST(ParameterRepositoryTests, AddsValidParameter) {
    ParameterRepository repository;

    Parameter parameter(
        L"RBC01",
        L"Red Blood Cells",
        L"Red blood cell count",
        L"10^12/L",
        4.2,
        5.9
    );

    EXPECT_TRUE(repository.add(parameter));
    EXPECT_EQ(repository.count(), 1);
}

TEST(ParameterRepositoryTests, RejectsDuplicateCode) {
    ParameterRepository repository;

    Parameter first(
        L"RBC01",
        L"Red Blood Cells",
        L"Red blood cell count",
        L"10^12/L",
        4.2,
        5.9
    );

    Parameter second(
        L"RBC01",
        L"Another Parameter",
        L"Different description",
        L"mg/dL",
        70.0,
        100.0
    );

    EXPECT_TRUE(repository.add(first));
    EXPECT_FALSE(repository.add(second));

    EXPECT_EQ(repository.count(), 1);
}

TEST(ParameterRepositoryTests, FindsExistingParameter) {
    ParameterRepository repository;

    Parameter parameter(
        L"RBC01",
        L"Red Blood Cells",
        L"Red blood cell count",
        L"10^12/L",
        4.2,
        5.9
    );

    repository.add(parameter);

    const Parameter* found = repository.findByCode(L"RBC01");

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), L"Red Blood Cells");
}

TEST(ParameterRepositoryTests, ReturnsNullForUnknownCode) {
    ParameterRepository repository;

    EXPECT_EQ(repository.findByCode(L"XXXXX"), nullptr);
}

// =====================================================
// US11: Register Parameter
// =====================================================

TEST(RegisterParameterTests, RegistersValidParameter) {
    ParameterRepository repository;
    RegisterParameter service(repository);

    bool result = service.execute(
        L"RBC01",
        L"Red Blood Cells",
        L"Red blood cell count",
        L"10^12/L",
        4.2,
        5.9
    );

    EXPECT_TRUE(result);
    EXPECT_EQ(repository.count(), 1);
}

TEST(RegisterParameterTests, RejectsDuplicateRegistration) {
    ParameterRepository repository;
    RegisterParameter service(repository);

    EXPECT_TRUE(service.execute(
        L"RBC01",
        L"Red Blood Cells",
        L"Red blood cell count",
        L"10^12/L",
        4.2,
        5.9
    ));

    EXPECT_FALSE(service.execute(
        L"RBC01",
        L"Another Parameter",
        L"Different description",
        L"mg/dL",
        70.0,
        100.0
    ));

    EXPECT_EQ(repository.count(), 1);
}

TEST(RegisterParameterTests, DoesNotStoreInvalidParameter) {
    ParameterRepository repository;
    RegisterParameter service(repository);

    EXPECT_THROW({
        service.execute(
            L"AB12",
            L"Invalid Parameter",
            L"Invalid code length",
            L"mg/dL",
            70.0,
            100.0
        );
    }, std::invalid_argument);

    EXPECT_EQ(repository.count(), 0);
}

// =====================================================
// AC11-2: Explicit MetricType classification
// =====================================================

TEST(ParameterTests, AcceptsNewNumericUnitWithExplicitClassification) {
    EXPECT_NO_THROW({
        Parameter parameter(
            L"GLU01",
            L"Glucose",
            L"Blood glucose concentration",
            L"mg/100mL",
            MetricType::Numeric,
            70.0,
            100.0
        );
    });
}

TEST(ParameterTests, ReturnsNumericMetricType) {
    Parameter parameter(
        L"GLU01",
        L"Glucose",
        L"Blood glucose concentration",
        L"mg/100mL",
        MetricType::Numeric,
        70.0,
        100.0
    );

    EXPECT_EQ(parameter.getMetricType(), MetricType::Numeric);
}

TEST(ParameterTests, ReturnsQualitativeMetricType) {
    Parameter parameter(
        L"COV01",
        L"COVID-19 Result",
        L"COVID-19 test result",
        L"Positive/Negative",
        MetricType::Qualitative
    );

    EXPECT_EQ(parameter.getMetricType(), MetricType::Qualitative);
    EXPECT_FALSE(parameter.getMinimumReferenceValue().has_value());
    EXPECT_FALSE(parameter.getMaximumReferenceValue().has_value());
}

TEST(ParameterTests, RejectsQualitativeMetricWithReferenceValues) {
    EXPECT_THROW({
        Parameter parameter(
            L"COV02",
            L"COVID-19 Result",
            L"COVID-19 test result",
            L"Positive/Negative",
            MetricType::Qualitative,
            0.0,
            1.0
        );
    }, std::invalid_argument);
}

TEST(RegisterParameterTests, RegistersExplicitNumericMetricWithNewUnit) {
    ParameterRepository repository;
    RegisterParameter service(repository);

    EXPECT_TRUE(service.execute(
        L"GLU01",
        L"Glucose",
        L"Blood glucose concentration",
        L"mg/100mL",
        MetricType::Numeric,
        70.0,
        100.0
    ));

    EXPECT_EQ(repository.count(), 1);

    const Parameter* parameter = repository.findByCode(L"GLU01");

    ASSERT_NE(parameter, nullptr);
    EXPECT_EQ(parameter->getMetricType(), MetricType::Numeric);
}

TEST(RegisterParameterTests, RegistersExplicitQualitativeMetric) {
    ParameterRepository repository;
    RegisterParameter service(repository);

    EXPECT_TRUE(service.execute(
        L"COV01",
        L"COVID-19 Result",
        L"COVID-19 test result",
        L"Positive/Negative",
        MetricType::Qualitative
    ));

    EXPECT_EQ(repository.count(), 1);

    const Parameter* parameter = repository.findByCode(L"COV01");

    ASSERT_NE(parameter, nullptr);
    EXPECT_EQ(parameter->getMetricType(), MetricType::Qualitative);
}

TEST(RegisterParameterTests, DoesNotStoreQualitativeMetricWithReferenceValues) {
    ParameterRepository repository;
    RegisterParameter service(repository);

    EXPECT_THROW({
        service.execute(
            L"COV02",
            L"COVID-19 Result",
            L"COVID-19 test result",
            L"Positive/Negative",
            MetricType::Qualitative,
            0.0,
            1.0
        );
    }, std::invalid_argument);

    EXPECT_EQ(repository.count(), 0);
}

// =====================================================
// NEW: Mandatory reference values for Numeric metrics
// Rule confirmed with the professor
// =====================================================

// Numeric parameter without minimum must be rejected.
TEST(ParameterTests, RejectsNumericMetricWithoutMinimum) {
    EXPECT_THROW({
        Parameter parameter(
            L"GLU02",
            L"Glucose",
            L"Blood glucose concentration",
            L"mg/dL",
            MetricType::Numeric,
            std::nullopt,
            100.0
        );
    }, std::invalid_argument);
}

// Numeric parameter without maximum must be rejected.
TEST(ParameterTests, RejectsNumericMetricWithoutMaximum) {
    EXPECT_THROW({
        Parameter parameter(
            L"GLU03",
            L"Glucose",
            L"Blood glucose concentration",
            L"mg/dL",
            MetricType::Numeric,
            70.0,
            std::nullopt
        );
    }, std::invalid_argument);
}

// Numeric parameter without either reference value must be rejected.
TEST(ParameterTests, RejectsNumericMetricWithoutBothReferenceValues) {
    EXPECT_THROW({
        Parameter parameter(
            L"GLU04",
            L"Glucose",
            L"Blood glucose concentration",
            L"mg/dL",
            MetricType::Numeric,
            std::nullopt,
            std::nullopt
        );
    }, std::invalid_argument);
}

// The service must not store numeric parameters
// when mandatory reference values are missing.
TEST(RegisterParameterTests, DoesNotStoreNumericMetricWithoutReferenceValues) {
    ParameterRepository repository;
    RegisterParameter service(repository);

    EXPECT_THROW({
        service.execute(
            L"GLU05",
            L"Glucose",
            L"Blood glucose concentration",
            L"mg/dL",
            MetricType::Numeric,
            std::nullopt,
            std::nullopt
        );
    }, std::invalid_argument);

    EXPECT_EQ(repository.count(), 0);
}