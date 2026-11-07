//
// ParameterRepository.h
// US11 - Register Parameter
// LETI-ESOFT 2026/2027 - Team B6
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
    // Checks whether a parameter with the given ID exists.
    bool existsByID(const std::wstring& ID) const;

    // Stores a parameter if its ID is not already registered.
    // Returns false if the ID already exists.
    bool add(const Parameter& parameter);

    // Returns the parameter with the specified ID.
    // Returns nullptr if the parameter does not exist.
    const Parameter* findByID(const std::wstring& ID) const;

    // Returns the total number of registered parameters.
    std::size_t count() const;
};

#endif // LETI_ESOFT_26_27_B6_PARAMETERREPOSITORY_H