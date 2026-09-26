#pragma once
#include "IWindow.h"

#include "Core/Util.h"

#include <imgui.h>

namespace UI::Window
{
    class ServerAndStatus :public IWindow
    {
    public:
        void Render(const Model::Theme& theme, const ImGuiViewport& viewport) override
        {
            IWindow::Render(theme, viewport);
            InvisibleResizeGrip _;

            const ImVec2 minSize{200.0f, viewport.WorkSize.y};
            const ImVec2 maxSize{500.0f, viewport.WorkSize.y};
            ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

            constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;

            ImGui::Begin("ServerAndStatus", nullptr, windowFlags);
            size_ = ImGui::GetWindowSize();

            ImGui::Text("Server & Status");
            ImGui::Text("Server & Status");
            ImGui::Text("Server & Status");ImGui::Text("Server & Status");ImGui::Text("Server & Status");

            Resizable::MakeWindowResizable_Right(size_, minSize, maxSize);
            ImGui::End();
        }
    };
}