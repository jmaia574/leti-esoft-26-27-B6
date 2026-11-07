//
// RegisterParameter.h
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#ifndef LETI_ESOFT_26_27_B6_REGISTERPARAMETER_H
#define LETI_ESOFT_26_27_B6_REGISTERPARAMETER_H

#include "domain/parameter/ParameterRepository.h"
#include "domain/parameter/Parameter.h"

#include <optional>
#include <string>

class RegisterParameter {
private:
    ParameterRepository& repository;

public:
    explicit RegisterParameter(ParameterRepository& repository);

    // Register a parameter with explicit metric classification.
    bool execute(
        const std::wstring& ID,
        const std::wstring& name,
        const std::wstring& description,
        const std::wstring& metric,
        MetricType metricType,
        std::optional<double> minimumReferenceValue = std::nullopt,
        std::optional<double> maximumReferenceValue = std::nullopt
    );

    // Legacy method - temporary compatibility with existing code.
    bool execute(
        const std::wstring& ID,
        const std::wstring& name,
        const std::wstring& description,
        const std::wstring& metric,
        std::optional<double> minimumReferenceValue = std::nullopt,
        std::optional<double> maximumReferenceValue = std::nullopt
    );
};

#endif // LETI_ESOFT_26_27_B6_REGISTERPARAMETER_H