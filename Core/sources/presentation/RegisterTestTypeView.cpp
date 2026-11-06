#include "presentation/RegisterTestTypeView.h"

#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

RegisterTestTypeView::RegisterTestTypeView(
    RegisterTestTypeController& controller
)
    : controller(controller) {
}

void RegisterTestTypeView::show(
    std::wistream& input,
    std::wostream& output
) {
    std::wstring internalCode;
    std::wstring nhsCode;
    std::wstring collectionMethodDescription;

    output << L"\n===== US10 - REGISTER TEST TYPE =====\n";
    output << L"Internal Code: ";
    if (!std::getline(input, internalCode)) {
        return;
    }

    output << L"NHS Code: ";
    if (!std::getline(input, nhsCode)) {
        return;
    }

    output << L"Description identifying the sample collection method: ";
    if (!std::getline(input, collectionMethodDescription)) {
        return;
    }

    try {
        if (controller.registerTestType(
                internalCode,
                nhsCode,
                collectionMethodDescription
            )) {
            output << L"\nTest type registered successfully.\n";
        } else {
            output << L"\nRegistration failed: Internal Code or NHS Code "
                   << L"already exists.\n";
        }
    } catch (const std::invalid_argument& exception) {
        output << L"\nRegistration failed: ";
        const std::string message = exception.what();
        for (char character : message) {
            output << static_cast<wchar_t>(character);
        }
        output << L'\n';
    }
}
