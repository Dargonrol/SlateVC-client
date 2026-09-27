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

            constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
            const ImVec2 minSize{200.0f, viewport.WorkSize.y};
            const ImVec2 maxSize{340.0f, viewport.WorkSize.y};
            ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

            ImGui::Begin("Server And Status", nullptr, windowFlags);
            {
                size_ = ImGui::GetWindowSize();
                ImGui::SetCursorPos(theme.globalContext.innerWindowPadding);
                ImGui::BeginChild("child", ImVec2{
                    size_.x - ImGui::GetStyle().ScrollbarSize + Resizable::buttonWidth - theme.globalContext.innerWindowPadding.x,
                    size_.y - ImGui::GetStyle().ScrollbarSize + Resizable::buttonHeight - 2 - theme.globalContext.innerWindowPadding.y
                });
                {
                    ImGui::Text("Server and Status");
                }
                ImGui::EndChild();
            }
            Resizable::MakeWindowResizable_Right(size_, minSize, maxSize);
            ImGui::End();
        }
    };
}