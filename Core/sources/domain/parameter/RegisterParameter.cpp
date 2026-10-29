//
// RegisterParameter.cpp
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#include "domain/parameter/RegisterParameter.h"

#include <stdexcept>

RegisterParameter::RegisterParameter(ParameterRepository& repository)
    : repository(repository) {
}

bool RegisterParameter::execute(
    const std::wstring& code,
    const std::wstring& name,
    const std::wstring& description,
    const std::wstring& metric,
    std::optional<double> minimumReferenceValue,
    std::optional<double> maximumReferenceValue
) {
    // Create the parameter and validate its attributes.
    Parameter parameter(
        code,
        name,
        description,
        metric,
        minimumReferenceValue,
        maximumReferenceValue
    );

    // Check whether the parameter code is already registered.
    if (repository.existsByCode(parameter.getCode())) {
        return false;
    }

    // Store the parameter in the repository.
    return repository.add(parameter);
}