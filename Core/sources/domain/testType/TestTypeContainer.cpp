#include "domain/testType/TestTypeContainer.h"

#include <algorithm>

namespace {
std::wstring normalizeNhsCode(const std::wstring& nhsCode) {
    std::wstring normalized = nhsCode;
    std::transform(
        normalized.begin(),
        normalized.end(),
        normalized.begin(),
        [](wchar_t character) {
            if (character >= L'a' && character <= L'z') {
                return static_cast<wchar_t>(character - L'a' + L'A');
            }
            return character;
        }
    );
    return normalized;
}
}

TestType TestTypeContainer::create(
    const std::wstring& internalCode,
    const std::wstring& nhsCode,
    const std::wstring& collectionMethodDescription
) const {
    return TestType(internalCode, nhsCode, collectionMethodDescription);
}

bool TestTypeContainer::save(const TestType& testType) {
    if (existsByInternalCode(testType.getInternalCode()) ||
        existsByNhsCode(testType.getNhsCode())) {
        return false;
    }

    testTypes.push_back(testType);
    return true;
}

bool TestTypeContainer::existsByInternalCode(
    const std::wstring& internalCode
) const {
    return findByInternalCode(internalCode) != nullptr;
}

bool TestTypeContainer::existsByNhsCode(
    const std::wstring& nhsCode
) const {
    const std::wstring normalizedNhsCode = normalizeNhsCode(nhsCode);
    return std::any_of(
        testTypes.begin(),
        testTypes.end(),
        [&normalizedNhsCode](const TestType& testType) {
            return normalizeNhsCode(testType.getNhsCode()) == normalizedNhsCode;
        }
    );
}

const TestType* TestTypeContainer::findByInternalCode(
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

std::size_t TestTypeContainer::count() const {
    return testTypes.size();
}
