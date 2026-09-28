#pragma once
#include "IWindow.h"

#include <imgui.h>

namespace UI::Window
{
    class ChatWindow : public IWindow
    {
    protected:
        void RenderContent(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            ImGui::Text("Chat Window");
        }
    };
}
