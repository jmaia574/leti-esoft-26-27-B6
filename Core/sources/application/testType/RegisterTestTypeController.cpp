#include "application/testType/RegisterTestTypeController.h"
#include "application/App.h"

RegisterTestTypeController::RegisterTestTypeController(
    TestTypeContainer& container
)
    : container(&container) {
}

bool RegisterTestTypeController::registerTestType(
    const std::wstring& internalCode,
    const std::wstring& nhsCode,
    const std::wstring& collectionMethodDescription
) {
    TestTypeContainer& activeContainer = container != nullptr
        ? *container
        : App::getInstance().getTestTypeContainer();

    const TestType testType = activeContainer.create(
        internalCode,
        nhsCode,
        collectionMethodDescription
    );

    return activeContainer.save(testType);
}
