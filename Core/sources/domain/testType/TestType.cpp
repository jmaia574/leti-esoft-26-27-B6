#include "domain/testType/TestType.h"

#include <algorithm>
#include <stdexcept>

TestType::TestType(
    const std::wstring& internalCode,
    const std::wstring& nhsCode,
    const std::wstring& collectionMethodDescription
)
    : internalCode(internalCode),
      nhsCode(nhsCode),
      collectionMethodDescription(collectionMethodDescription)
{
    if (!isValidInternalCode(internalCode)) {
        throw std::invalid_argument(
            "Internal Code must contain exactly four digits."
        );
    }

    if (!isValidNhsCode(nhsCode)) {
        throw std::invalid_argument(
            "NHS Code must contain exactly five alphanumeric characters."
        );
    }
}

const std::wstring& TestType::getInternalCode() const {
    return internalCode;
}

const std::wstring& TestType::getNhsCode() const {
    return nhsCode;
}

const std::wstring& TestType::getCollectionMethodDescription() const {
    return collectionMethodDescription;
}

bool TestType::isValidInternalCode(const std::wstring& internalCode) {
    return internalCode.size() == 4 &&
           std::all_of(
               internalCode.begin(),
               internalCode.end(),
               [](wchar_t character) {
                   return character >= L'0' && character <= L'9';
               }
           );
}

bool TestType::isValidNhsCode(const std::wstring& nhsCode) {
    return nhsCode.size() == 5 &&
           std::all_of(
               nhsCode.begin(),
               nhsCode.end(),
               [](wchar_t character) {
                   return (character >= L'A' && character <= L'Z') ||
                          (character >= L'a' && character <= L'z') ||
                          (character >= L'0' && character <= L'9');
               }
           );
}
