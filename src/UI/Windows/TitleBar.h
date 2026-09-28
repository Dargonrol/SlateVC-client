#pragma once
#include "IWindow.h"

#include "Core/Util.h"

#include <imgui.h>

namespace UI::Window
{
    class TitleBar :public IWindow
    {
    public:
        TitleBar()
        {
            customRenderImplementation = true;
            windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
            windowTitle_ = "Title Bar";
            autoResizeHorizontal = true;
            floating = false;
        }

    protected:
        void PreRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.0f, 0.0f));
        }

        void RenderContent(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            size_ = ImGui::GetWindowSize();
        }

        void PostRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            ImGui::PopStyleVar(1);
        }
    };
}