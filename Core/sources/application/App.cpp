#include "application/App.h"

App& App::getInstance() {
    static App app;
    return app;
}

TestTypeContainer& App::getTestTypeContainer() {
    return testTypeContainer;
}
