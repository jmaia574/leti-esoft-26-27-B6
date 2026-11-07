//
// Parameter.h
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#ifndef LETI_ESOFT_26_27_B6_PARAMETER_H
#define LETI_ESOFT_26_27_B6_PARAMETER_H

#include <string>
#include <optional>

// =====================================================
// Metric classification
// =====================================================

enum class MetricType {
    Numeric,
    Qualitative
};

class Parameter {
private:
    std::wstring ID;
    std::wstring name;
    std::wstring description;
    std::wstring metric;

    MetricType metricType;

    std::optional<double> minimumReferenceValue;
    std::optional<double> maximumReferenceValue;

public:
    // =====================================================
    // Constructor with explicit metric classification
    // =====================================================

    Parameter(
        const std::wstring& ID,
        const std::wstring& name,
        const std::wstring& description,
        const std::wstring& metric,
        MetricType metricType,
        std::optional<double> minimumReferenceValue = std::nullopt,
        std::optional<double> maximumReferenceValue = std::nullopt
    );

    // =====================================================
    // Legacy constructor for compatibility
    // =====================================================

    Parameter(
        const std::wstring& ID,
        const std::wstring& name,
        const std::wstring& description,
        const std::wstring& metric,
        std::optional<double> minimumReferenceValue = std::nullopt,
        std::optional<double> maximumReferenceValue = std::nullopt
    );

    // =====================================================
    // Getters
    // =====================================================

    const std::wstring& getID() const;
    const std::wstring& getName() const;
    const std::wstring& getDescription() const;
    const std::wstring& getMetric() const;

    MetricType getMetricType() const;

    std::optional<double> getMinimumReferenceValue() const;
    std::optional<double> getMaximumReferenceValue() const;

    // =====================================================
    // Validation
    // =====================================================

    static bool isValidID(const std::wstring& ID);

    static bool isNumericMetric(const std::wstring& metric);

    static bool isValidReferenceRange(
        std::optional<double> minimum,
        std::optional<double> maximum
    );
};

#endif // LETI_ESOFT_26_27_B6_PARAMETER_H