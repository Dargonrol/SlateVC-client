#pragma once

#include "Model/Theme.h"
#include "Core/Util.h"

namespace UI::Window
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        void Render(const Model::Theme& theme, const ImGuiViewport& viewport);
        virtual void RenderContent(const Model::Theme& theme, const ImGuiViewport& viewport) = 0;

        void SetWindowPos(const ImVec2 pos)
        {
            pos_ = pos;
        }

        void SetWindowSize(const ImVec2 size)
        {
            size_ = size;
        }

        [[nodiscard]] ImVec2 GetWindowSize() const { return size_; }
        [[nodiscard]] ImVec2 GetWindowPos() const { return pos_; }

    protected:
        ImVec2 size_{400.0f, 400.0f};
        ImVec2 pos_{100.0f, 100.0f};
    };

    inline void IWindow::Render(const Model::Theme& theme, const ImGuiViewport& viewport)
    {
        ImGui::SetNextWindowSize(size_);
        ImGui::SetNextWindowPos(pos_);
        RenderContent(theme, viewport);
    }
}
