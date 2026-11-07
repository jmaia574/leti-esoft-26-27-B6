//
// ParameterRepository.cpp
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
//

#include "domain/parameter/ParameterRepository.h"

#include <algorithm>

// =====================================================
// Check if a parameter ID already exists
// =====================================================

bool ParameterRepository::existsByID(const std::wstring& ID) const {
    return findByID(ID) != nullptr;
}

// =====================================================
// Add a new parameter
// =====================================================

bool ParameterRepository::add(const Parameter& parameter) {

    // Prevent duplicate parameter IDs.
    if (existsByID(parameter.getID())) {
        return false;
    }

    parameters.push_back(parameter);
    return true;
}

// =====================================================
// Find a parameter by ID
// =====================================================

const Parameter* ParameterRepository::findByID(
    const std::wstring& ID
) const {
    auto it = std::find_if(
        parameters.begin(),
        parameters.end(),
        [&ID](const Parameter& parameter) {
            return parameter.getID() == ID;
        }
    );

    if (it == parameters.end()) {
        return nullptr;
    }

    return &(*it);
}

// =====================================================
// Count registered parameters
// =====================================================

std::size_t ParameterRepository::count() const {
    return parameters.size();
}