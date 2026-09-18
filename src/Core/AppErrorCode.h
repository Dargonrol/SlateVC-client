#pragma once

namespace Core
{
    enum class AppErrorCode
    {
        SUCCESS = 0,
        GLFW_INIT_FAILED,
        WINDOW_CREATION_FAILED,
        GLAD_INIT_FAILED
    };
}