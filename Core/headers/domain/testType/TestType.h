#ifndef LETI_ESOFT_26_27_B6_TESTTYPE_H
#define LETI_ESOFT_26_27_B6_TESTTYPE_H

#include <string>

class TestType {
private:
    std::wstring internalCode;
    std::wstring nhsCode;
    std::wstring collectionMethodDescription;

public:
    TestType(
        const std::wstring& internalCode,
        const std::wstring& nhsCode,
        const std::wstring& collectionMethodDescription
    );

    const std::wstring& getInternalCode() const;
    const std::wstring& getNhsCode() const;
    const std::wstring& getCollectionMethodDescription() const;

    static bool isValidInternalCode(const std::wstring& internalCode);
    static bool isValidNhsCode(const std::wstring& nhsCode);
};

#endif // LETI_ESOFT_26_27_B6_TESTTYPE_H
