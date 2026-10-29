//
// Created by Tomas Campinho on 29/10/2026.
//

#ifndef LETI_ESOFT_26_27_B6_PARAMETERREPOSITORY_H
#define LETI_ESOFT_26_27_B6_PARAMETERREPOSITORY_H

#include "domain/parameter/Parameter.h"

#include <string>
#include <vector>
#include <cstddef>

class ParameterRepository {
private:
    std::vector<Parameter> parameters;

public:
    // Checks whether a parameter with the given code exists.
    bool existsByCode(const std::wstring& code) const;

    // Stores a parameter if its code is not already registered.
    // Returns false if the code already exists.
    bool add(const Parameter& parameter);

    // Returns the parameter with the specified code.
    // Returns nullptr if the parameter does not exist.
    const Parameter* findByCode(const std::wstring& code) const;

    // Returns the total number of registered parameters.
    std::size_t count() const;
};

#endif // LETI_ESOFT_26_27_B6_PARAMETERREPOSITORY_H