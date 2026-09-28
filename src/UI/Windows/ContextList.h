#pragma once
#include "IWindow.h"

#include <imgui.h>

namespace UI::Window
{
    class ContextList :public IWindow
    {
    protected:
        void RenderContent(const Model::Theme& theme, const Model::VirtualViewport& viewport) override
        {
            ImGui::Text("Context");
        }
    };
}