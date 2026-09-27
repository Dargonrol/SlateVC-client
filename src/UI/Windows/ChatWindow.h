#pragma once
#include "IWindow.h"

#include "Core/Util.h"

#include <imgui.h>

namespace UI::Window
{
    class ChatWindow : public IWindow
    {
    public:
        void RenderContent(const Model::Theme& theme, const ImGuiViewport& viewport) override
        {
            InvisibleResizeGrip _;

            constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

            const ImVec2 minSize{10.0f, viewport.WorkSize.y - theme.globalContext.outerWindowPadding.y * 2};
            const ImVec2 maxSize{FLT_MAX, viewport.WorkSize.y - theme.globalContext.outerWindowPadding.y * 2};
            ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

            ImGui::Begin("Chat Window", nullptr, windowFlags);
            {
                ImGui::SetCursorPos(theme.globalContext.innerWindowPadding);
                ImGui::BeginChild("child", ImVec2{
                   size_.x - ImGui::GetStyle().ScrollbarSize + Resizable::buttonWidth - theme.globalContext.innerWindowPadding.x,
                   size_.y - ImGui::GetStyle().ScrollbarSize + Resizable::buttonHeight - 2 - theme.globalContext.innerWindowPadding.y
               });

                ImGui::Text("Chat Window");

                ImGui::EndChild();
            }
            ImGui::End();
        }
    };
}
