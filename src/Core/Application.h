#pragma once
#include <string_view>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "AppErrorCode.h"
#include "UI/ViewManager.h"

namespace Core
{
    class Application
    {
    public:
        explicit Application(AppErrorCode* error = nullptr);
        ~Application();

        AppErrorCode Init(int width, int height, std::string_view title);
        void Run();

    private:
        void Update();
        void Render();

        void PreRender() const;
        void PostRender() const;

    private:
        GLFWwindow* window_;
        std::unique_ptr<UI::ViewManager> viewManager_;
    };

}
