#ifndef LETI_ESOFT_26_27_B6_REGISTERTESTTYPECONTROLLER_H
#define LETI_ESOFT_26_27_B6_REGISTERTESTTYPECONTROLLER_H

#include "domain/testType/TestTypeContainer.h"

#include <string>

class RegisterTestTypeController {
private:
    TestTypeContainer* container = nullptr;

public:
    RegisterTestTypeController() = default;
    explicit RegisterTestTypeController(TestTypeContainer& container);

    bool registerTestType(
        const std::wstring& internalCode,
        const std::wstring& nhsCode,
        const std::wstring& collectionMethodDescription
    );
};

#endif // LETI_ESOFT_26_27_B6_REGISTERTESTTYPECONTROLLER_H
