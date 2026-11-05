#include "domain/testType/TestTypeRepository.h"

#include <algorithm>

bool TestTypeRepository::add(const TestType& testType) {
    if (existsByInternalCode(testType.getInternalCode()) ||
        existsByNhsCode(testType.getNhsCode())) {
        return false;
    }

    testTypes.push_back(testType);
    return true;
}

bool TestTypeRepository::existsByInternalCode(
    const std::wstring& internalCode
) const {
    return findByInternalCode(internalCode) != nullptr;
}

bool TestTypeRepository::existsByNhsCode(
    const std::wstring& nhsCode
) const {
    return std::any_of(
        testTypes.begin(),
        testTypes.end(),
        [&nhsCode](const TestType& testType) {
            return testType.getNhsCode() == nhsCode;
        }
    );
}

const TestType* TestTypeRepository::findByInternalCode(
    const std::wstring& internalCode
) const {
    const auto found = std::find_if(
        testTypes.begin(),
        testTypes.end(),
        [&internalCode](const TestType& testType) {
            return testType.getInternalCode() == internalCode;
        }
    );

    return found == testTypes.end() ? nullptr : &*found;
}

std::size_t TestTypeRepository::count() const {
    return testTypes.size();
}
