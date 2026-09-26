#pragma once
#include "IWindow.h"

#include "Core/Util.h"

#include <imgui.h>

namespace UI::Window
{
    class NavigationBar : public IWindow
    {
    public:
        void Render(const Model::Theme& theme, const ImGuiViewport& viewport) override
        {
            IWindow::Render(theme, viewport);
            InvisibleResizeGrip _;

            //const ImVec2 minSize{60.0f, viewport.WorkSize.y};
            //const ImVec2 maxSize{120.0f, viewport.WorkSize.y};
            //ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

            constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;

            ImGui::Begin("NavBar", nullptr, windowFlags);
            size_ = ImGui::GetWindowSize();
            ImGui::Text("NAV");
            ImGui::End();
        }
    };
}