#pragma once

#include <iostream>

#include "Model/Theme.h"

namespace UI::Window
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;
        virtual void Render(const Model::Theme& theme, const ImGuiViewport& viewport) = 0;

        void SetWindowPos(const ImVec2 pos, ImGuiCond_ cond = ImGuiCond_FirstUseEver)
        {
            pos_ = pos;
            posCondition_ = cond;
        }

        void SetWindowSize(const ImVec2 size, ImGuiCond_ cond = ImGuiCond_FirstUseEver)
        {
            size_ = size;
            sizeCondition_ = cond;
        }
        void ClearPositionCondition()
        {
            posCondition_ = ImGuiCond_None;
        }

        void ClearSizeCondition()
        {
            sizeCondition_ = ImGuiCond_None;
        }

        [[nodiscard]] ImVec2 GetWindowSize() const { return size_; }

    protected:
        ImVec2 size_{};
        ImVec2 pos_{};

        ImGuiCond_ posCondition_ = ImGuiCond_None;
        ImGuiCond_ sizeCondition_ = ImGuiCond_None;
    };

    /**
     * Updates Window Size and Position
     */
    inline void IWindow::Render(const Model::Theme& theme, const ImGuiViewport& viewport)
    {
        if (posCondition_ != ImGuiCond_None)
            ImGui::SetNextWindowPos(pos_, posCondition_);
        if (sizeCondition_ != ImGuiCond_None)
            ImGui::SetNextWindowSize(size_, sizeCondition_);
    }
}
