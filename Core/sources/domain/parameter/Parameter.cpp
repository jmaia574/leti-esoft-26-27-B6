//
// Parameter.cpp
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#include "domain/parameter/Parameter.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

// =====================================================
// Constructor with explicit metric classification
// =====================================================

Parameter::Parameter(
    const std::wstring& code,
    const std::wstring& name,
    const std::wstring& description,
    const std::wstring& metric,
    MetricType metricType,
    std::optional<double> minimumReferenceValue,
    std::optional<double> maximumReferenceValue
)
    : code(code),
      name(name),
      description(description),
      metric(metric),
      metricType(metricType),
      minimumReferenceValue(minimumReferenceValue),
      maximumReferenceValue(maximumReferenceValue)
{
    // AC11-1: Code must contain exactly five alphanumeric characters.
    if (!isValidCode(code)) {
        throw std::invalid_argument(
            "Parameter code must contain exactly five alphanumeric characters."
        );
    }

    // Validate mandatory fields.
    if (name.empty() || description.empty() || metric.empty()) {
        throw std::invalid_argument(
            "Parameter name, description and metric are required."
        );
    }

    // Validate reference range.
    if (!isValidReferenceRange(
            minimumReferenceValue,
            maximumReferenceValue)) {
        throw std::invalid_argument(
            "Invalid parameter reference range."
        );
    }

    // AC11-2: Reference values are only applicable to numeric metrics.
    if ((minimumReferenceValue.has_value() ||
         maximumReferenceValue.has_value()) &&
        metricType != MetricType::Numeric) {
        throw std::invalid_argument(
            "Reference values are only applicable to numeric metrics."
        );
    }
}

// =====================================================
// Legacy constructor - Compatibility with existing code
// =====================================================

Parameter::Parameter(
    const std::wstring& code,
    const std::wstring& name,
    const std::wstring& description,
    const std::wstring& metric,
    std::optional<double> minimumReferenceValue,
    std::optional<double> maximumReferenceValue
)
    : Parameter(
        code,
        name,
        description,
        metric,
        isNumericMetric(metric)
            ? MetricType::Numeric
            : MetricType::Qualitative,
        minimumReferenceValue,
        maximumReferenceValue
    )
{
}

// =====================================================
// Getters
// =====================================================

const std::wstring& Parameter::getCode() const {
    return code;
}

const std::wstring& Parameter::getName() const {
    return name;
}

const std::wstring& Parameter::getDescription() const {
    return description;
}

const std::wstring& Parameter::getMetric() const {
    return metric;
}

MetricType Parameter::getMetricType() const {
    return metricType;
}

std::optional<double> Parameter::getMinimumReferenceValue() const {
    return minimumReferenceValue;
}

std::optional<double> Parameter::getMaximumReferenceValue() const {
    return maximumReferenceValue;
}

// =====================================================
// AC11-1: Code validation
// =====================================================

bool Parameter::isValidCode(const std::wstring& code) {
    if (code.length() != 5) {
        return false;
    }

    return std::all_of(
        code.begin(),
        code.end(),
        [](wchar_t character) {
            return (character >= L'A' && character <= L'Z') ||
                   (character >= L'a' && character <= L'z') ||
                   (character >= L'0' && character <= L'9');
        }
    );
}

// =====================================================
// Legacy metric classification
// =====================================================

bool Parameter::isNumericMetric(const std::wstring& metric) {

    // Temporary compatibility with existing registrations.
    // New registrations should use explicit MetricType.

    static const std::wstring numericMetrics[] = {
        L"g/dL",
        L"mg/dL",
        L"U/L",
        L"10^12/L",
        L"10^9/L",
        L"mmol/L",
        L"mg/L",
        L"g/L",
        L"ng/mL",
        L"pg/mL",
        L"mEq/L",
        L"cells/uL"
    };

    return std::find(
        std::begin(numericMetrics),
        std::end(numericMetrics),
        metric
    ) != std::end(numericMetrics);
}

// =====================================================
// Reference range validation
// =====================================================

bool Parameter::isValidReferenceRange(
    std::optional<double> minimum,
    std::optional<double> maximum
) {
    if (minimum.has_value() && !std::isfinite(*minimum)) {
        return false;
    }

    if (maximum.has_value() && !std::isfinite(*maximum)) {
        return false;
    }

    if (minimum.has_value() && maximum.has_value()) {
        return *minimum <= *maximum;
    }

    return true;
}