#pragma once
#include "IWindow.h"

#include "Core/Util.h"

#include <imgui.h>

namespace UI::Window
{
    class ContextList :public IWindow
    {
    protected:
        void RenderContent(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            InvisibleResizeGrip _;

            constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

            ImGui::Begin("Context List", nullptr, windowFlags);
            {
                ImGui::SetCursorPos(theme.globalContext.innerWindowPadding);
                ImGui::BeginChild("child", ImVec2{
                    size_.x - ImGui::GetStyle().ScrollbarSize + Resizable::buttonWidth - theme.globalContext.innerWindowPadding.x,
                    size_.y - ImGui::GetStyle().ScrollbarSize + Resizable::buttonHeight - 2 - theme.globalContext.innerWindowPadding.y
                });
                {
                    ImGui::Text("Context");
                }
                ImGui::EndChild();
                Resizable::MakeWindowResizable_Left(resizeDeltaSize_, resizeDeltaPos_);
            }
            ImGui::End();
        }
    };
}