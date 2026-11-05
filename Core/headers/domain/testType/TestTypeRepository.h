#ifndef LETI_ESOFT_26_27_B6_TESTTYPEREPOSITORY_H
#define LETI_ESOFT_26_27_B6_TESTTYPEREPOSITORY_H

#include "domain/testType/TestType.h"

#include <cstddef>
#include <vector>

class TestTypeRepository {
private:
    std::vector<TestType> testTypes;

public:
    bool add(const TestType& testType);
    bool existsByInternalCode(const std::wstring& internalCode) const;
    bool existsByNhsCode(const std::wstring& nhsCode) const;
    const TestType* findByInternalCode(const std::wstring& internalCode) const;
    std::size_t count() const;
};

#endif // LETI_ESOFT_26_27_B6_TESTTYPEREPOSITORY_H
