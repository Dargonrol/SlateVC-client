#pragma once
#include "IWindow.h"

#include "Core/Application.h"

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
            ImGui::PushStyleColor(ImGuiCol_Button,          ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   ImVec4(0.85f, 0.2f, 0.2f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    ImVec4(0.95f, 0.1f, 0.1f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text,            ImVec4(0.9f, 0.9f, 0.9f, 1.0f));

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,    ImVec2(0.0f, 0.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign,  ImVec2{0.5f, 0.5f});

            const float buttonWidth = size_.y;
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() - buttonWidth);
            if (ImGui::Button("X##CloseBtn", ImVec2(buttonWidth, buttonWidth)))
            {
                glfwSetWindowShouldClose(Core::Application::Get().GetWindow(), GLFW_TRUE);
            }

            ImGui::PopStyleColor(4);
            ImGui::PopStyleVar(2);
        }

        void PostRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            ImGui::PopStyleVar(1);
        }
    };
}