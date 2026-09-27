#pragma once
#include "IWindow.h"

#include "Core/Util.h"

#include <imgui.h>

namespace UI::Window
{
    class TitleBar :public IWindow
    {
    protected:
        void RenderContent(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            InvisibleResizeGrip _;

            constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

            ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.0f, 0.0f));
            ImGui::Begin("Title Bar", nullptr, windowFlags);
            {
                size_ = ImGui::GetWindowSize();
            }
            ImGui::End();
            ImGui::PopStyleVar(1);
        }
    };
}