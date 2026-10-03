#include "Singleton/Application.h"

int main()
{
    Application* TonYogourt = Application::getInstance();

    if (TonYogourt) {
        TonYogourt->run();
    }

    return 0;
};