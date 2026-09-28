#pragma once
#include "IWindow.h"

#include <imgui.h>

namespace UI::Window
{
    class ServerAndStatus :public IWindow
    {
    protected:
        void PreContentRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 8.0f);

            const float alpha = isWindowHovered_ ? 1.0f : 0.0f;

            ImGui::PushStyleColor(ImGuiCol_ScrollbarBg,       ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab,      ImVec4(0.6f, 0.6f, 0.6f, alpha));
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, ImVec4(0.8f, 0.8f, 0.8f, alpha));
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive,  ImVec4(1.0f, 1.0f, 1.0f, alpha));
        }

        void RenderContent(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");
            ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");
            ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");
            ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");
            ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");
            ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");
            ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");ImGui::Text("Server and Status Text box");
        }

        void PostContentRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            ImGui::PopStyleColor(4); // Pop the 4 colors we pushed
            ImGui::PopStyleVar(1);   // Pop the style var
        }
    };
}