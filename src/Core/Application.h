#pragma once
#include <string_view>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "AppErrorCode.h"
#include "Service/ThemeController.h"
#include "UI/ViewManager.h"

#include <imgui.h>

namespace Core
{
    class Application
    {
    public:
        explicit Application(AppErrorCode* error = nullptr);
        ~Application();

        AppErrorCode Init(int width, int height, std::string_view title);
        void Run();
        void Render();

        void SetLastWindowSize(const ImVec2 size) {lastSize = size; }
        [[nodiscard]] ImVec2& GetLastWindowSize() { return lastSize; }
        [[nodiscard]] UI::ViewManager* GetViewManager() const { return viewManager_.get(); }

    private:

        void Update();
        void PreRender() const;
        void PostRender() const;

    private:
        GLFWwindow* window_;
        std::unique_ptr<UI::ViewManager> viewManager_;
        std::unique_ptr<Service::ThemeController> themeController_;

        ImVec2 lastSize;
    };

}
