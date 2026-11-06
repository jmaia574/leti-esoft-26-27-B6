#ifndef LETI_ESOFT_26_27_B6_TESTTYPECONTAINER_H
#define LETI_ESOFT_26_27_B6_TESTTYPECONTAINER_H

#include "domain/testType/TestType.h"

#include <cstddef>
#include <vector>

class TestTypeContainer {
private:
    std::vector<TestType> testTypes;

public:
    TestType create(
        const std::wstring& internalCode,
        const std::wstring& nhsCode,
        const std::wstring& collectionMethodDescription
    ) const;
    bool save(const TestType& testType);
    bool existsByInternalCode(const std::wstring& internalCode) const;
    bool existsByNhsCode(const std::wstring& nhsCode) const;
    const TestType* findByInternalCode(const std::wstring& internalCode) const;
    std::size_t count() const;
};

#endif // LETI_ESOFT_26_27_B6_TESTTYPECONTAINER_H
