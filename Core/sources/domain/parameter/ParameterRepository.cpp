//
// ParameterRepository.cpp
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#include "domain/parameter/ParameterRepository.h"

#include <algorithm>

bool ParameterRepository::existsByCode(const std::wstring& code) const {
    return findByCode(code) != nullptr;
}

bool ParameterRepository::add(const Parameter& parameter) {
    if (existsByCode(parameter.getCode())) {
        return false;
    }

    parameters.push_back(parameter);
    return true;
}

const Parameter* ParameterRepository::findByCode(
    const std::wstring& code
) const {
    auto it = std::find_if(
        parameters.begin(),
        parameters.end(),
        [&code](const Parameter& parameter) {
            return parameter.getCode() == code;
        }
    );

    if (it == parameters.end()) {
        return nullptr;
    }

    return &(*it);
}

std::size_t ParameterRepository::count() const {
    return parameters.size();
}