//
// RegisterParameter.cpp
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#include "domain/parameter/RegisterParameter.h"

// =====================================================
// Constructor
// =====================================================

RegisterParameter::RegisterParameter(ParameterRepository& repository)
    : repository(repository) {
}

// =====================================================
// Register parameter with explicit metric classification
// =====================================================

bool RegisterParameter::execute(
    const std::wstring& ID,
    const std::wstring& name,
    const std::wstring& description,
    const std::wstring& metric,
    MetricType metricType,
    std::optional<double> minimumReferenceValue,
    std::optional<double> maximumReferenceValue
) {
    // Create and validate the parameter.
    Parameter parameter(
        ID,
        name,
        description,
        metric,
        metricType,
        minimumReferenceValue,
        maximumReferenceValue
    );

    // AC11-1: Parameter ID must be unique.
    if (repository.existsByID(parameter.getID())) {
        return false;
    }

    // Store the parameter.
    return repository.add(parameter);
}

// =====================================================
// Legacy method - Temporary compatibility
// =====================================================

bool RegisterParameter::execute(
    const std::wstring& ID,
    const std::wstring& name,
    const std::wstring& description,
    const std::wstring& metric,
    std::optional<double> minimumReferenceValue,
    std::optional<double> maximumReferenceValue
) {
    // Preserve compatibility with existing callers.
    // The Parameter constructor enforces mandatory
    // reference values for numeric metrics.

    return execute(
        ID,
        name,
        description,
        metric,
        Parameter::isNumericMetric(metric)
            ? MetricType::Numeric
            : MetricType::Qualitative,
        minimumReferenceValue,
        maximumReferenceValue
    );
}