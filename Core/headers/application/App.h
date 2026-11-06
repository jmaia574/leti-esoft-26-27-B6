#ifndef LETI_ESOFT_26_27_B6_APP_H
#define LETI_ESOFT_26_27_B6_APP_H

#include "domain/testType/TestTypeContainer.h"

class App {
private:
    App() = default;
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    TestTypeContainer testTypeContainer;

public:
    static App& getInstance();
    TestTypeContainer& getTestTypeContainer();
};

#endif // LETI_ESOFT_26_27_B6_APP_H
