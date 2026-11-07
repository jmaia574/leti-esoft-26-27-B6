#ifndef LETI_ESOFT_26_27_B6_REGISTERTESTTYPEVIEW_H
#define LETI_ESOFT_26_27_B6_REGISTERTESTTYPEVIEW_H

#include "application/testType/RegisterTestTypeController.h"

#include <iosfwd>

class RegisterTestTypeView {
private:
    RegisterTestTypeController& controller;

public:
    explicit RegisterTestTypeView(RegisterTestTypeController& controller);
    void show(std::wistream& input, std::wostream& output);
};

#endif // LETI_ESOFT_26_27_B6_REGISTERTESTTYPEVIEW_H
