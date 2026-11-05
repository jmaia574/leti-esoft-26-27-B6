#ifndef LETI_ESOFT_26_27_B6_REGISTERTESTTYPE_H
#define LETI_ESOFT_26_27_B6_REGISTERTESTTYPE_H

#include "domain/testType/TestTypeRepository.h"

#include <string>

class RegisterTestType {
private:
    TestTypeRepository& repository;

public:
    explicit RegisterTestType(TestTypeRepository& repository);

    bool execute(
        const std::wstring& internalCode,
        const std::wstring& nhsCode,
        const std::wstring& collectionMethodDescription
    );
};

#endif // LETI_ESOFT_26_27_B6_REGISTERTESTTYPE_H
