#include "domain/testType/RegisterTestType.h"

RegisterTestType::RegisterTestType(TestTypeRepository& repository)
    : repository(repository) {
}

bool RegisterTestType::execute(
    const std::wstring& internalCode,
    const std::wstring& nhsCode,
    const std::wstring& collectionMethodDescription
) {
    const TestType testType(
        internalCode,
        nhsCode,
        collectionMethodDescription
    );

    return repository.add(testType);
}
