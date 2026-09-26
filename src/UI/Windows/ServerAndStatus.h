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

            // TODO: MAKE THIS PRETTY, SCALABLE AND MODULAR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            ImGui::SameLine();

            float contentWidth = ImGui::GetContentRegionAvail().x;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + contentWidth - 4.0f + ImGui::GetStyle().WindowPadding.x);

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

            ImGui::Button("##ResizeRight", ImVec2(4.0f, ImGui::GetContentRegionAvail().y));

            if (ImGui::IsItemActive())
            {
                float mouseDeltaX = ImGui::GetIO().MouseDelta.x;
                size_.x += mouseDeltaX;
                size_.x = std::clamp(size_.x, minSize.x, maxSize.x);
                ImGui::SetWindowSize(size_);
            }

            if (ImGui::IsItemHovered() || ImGui::IsItemActive())
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

            ImGui::PopStyleColor(4);

            ImGui::End();
        }
    };
}