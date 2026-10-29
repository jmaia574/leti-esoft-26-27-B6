//
// Created by Tomas Campinho on 29/10/2026.
//

#ifndef LETI_ESOFT_26_27_B6_PARAMETER_H
#define LETI_ESOFT_26_27_B6_PARAMETER_H

#include <string>
#include <optional>

class Parameter {
private:
    std::wstring code;
    std::wstring name;
    std::wstring description;
    std::wstring metric;

    std::optional<double> minimumReferenceValue;
    std::optional<double> maximumReferenceValue;

public:
    // Constructor
    Parameter(
        const std::wstring& code,
        const std::wstring& name,
        const std::wstring& description,
        const std::wstring& metric,
        std::optional<double> minimumReferenceValue = std::nullopt,
        std::optional<double> maximumReferenceValue = std::nullopt
    );

    // Getters
    const std::wstring& getCode() const;
    const std::wstring& getName() const;
    const std::wstring& getDescription() const;
    const std::wstring& getMetric() const;

    std::optional<double> getMinimumReferenceValue() const;
    std::optional<double> getMaximumReferenceValue() const;

    // Validation
    static bool isValidCode(const std::wstring& code);

    static bool isNumericMetric(const std::wstring& metric);

    static bool isValidReferenceRange(
        std::optional<double> minimum,
        std::optional<double> maximum
    );
};

#endif // LETI_ESOFT_26_27_B6_PARAMETER_H