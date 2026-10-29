//
// RegisterParameter.h
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#ifndef LETI_ESOFT_26_27_B6_REGISTERPARAMETER_H
#define LETI_ESOFT_26_27_B6_REGISTERPARAMETER_H

#include "domain/parameter/ParameterRepository.h"

#include <optional>
#include <string>

class RegisterParameter {
private:
    ParameterRepository& repository;

public:
    explicit RegisterParameter(ParameterRepository& repository);

    bool execute(
        const std::wstring& code,
        const std::wstring& name,
        const std::wstring& description,
        const std::wstring& metric,
        std::optional<double> minimumReferenceValue = std::nullopt,
        std::optional<double> maximumReferenceValue = std::nullopt
    );
};

#endif // LETI_ESOFT_26_27_B6_REGISTERPARAMETER_H