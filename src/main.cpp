#include <iostream>

#include "Core/Application.h"


int main ()
{
    Core::Application::Get().Init(720, 400, "SlateVC");

    Core::Application::Get().Run();

    return 0;
}

// when fullscreen message transparent pop up type shit