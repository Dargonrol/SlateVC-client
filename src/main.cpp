#include <iostream>

#include "Core/Application.h"


int main ()
{
    Core::AppErrorCode errorCode;

    Core::Application app{&errorCode};
    if (errorCode != Core::AppErrorCode::SUCCESS)
        return -1;

    errorCode = app.Init(720, 400, "SlateVC");
    if (errorCode != Core::AppErrorCode::SUCCESS)
        return -1;

    app.Run();

    return 0;
}
