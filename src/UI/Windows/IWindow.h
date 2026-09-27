#pragma once

#include "Model/Theme.h"
#include "Model/VirtualViewport.h"
#include "Core/Util.h"

namespace UI::Window
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        void Render(const Model::Theme& theme, const Model::VirtualViewport& viewport);

        void SetWindowPos(const ImVec2 pos)
        {
            pos_ = pos;
        }

        void SetWindowSize(const ImVec2 size)
        {
            size_ = size;
        }

        void SetCustomConstrains(const ImVec2 min, const ImVec2 max)
        {
            customMin_ = min;
            customMax_ = max;
        }

        void OnViewportResize(const ImVec2& oldSize, const ImVec2& newSize)
        {
            if (autoResizeHorizontal)
                fixedResizeSize_.x = newSize.x;
            if (autoResizeVertical)
                fixedResizeSize_.y = newSize.y;
        }

        [[nodiscard]] ImVec2 GetWindowSize() const { return size_; }
        [[nodiscard]] ImVec2 GetWindowPos() const { return pos_; }

    protected:
        virtual void RenderContent(const Model::Theme& theme, const Model::VirtualViewport& viewport) = 0;

    public:
        bool autoResizeHorizontal = false;
        bool autoResizeVertical = false;
        bool floating = false;

    protected:
        ImVec2 size_{0.0f, 0.0f};
        ImVec2 pos_{100.0f, 100.0f};
        ImVec2 resizeDeltaSize_{0.0f, 0.0f};
        ImVec2 resizeDeltaPos_{0.0f, 0.0f};

    private:
        ImVec2 fixedResizeSize_{0.0f, 0.0f};
        ImVec2 customMin_{0.0f, 0.0f};
        ImVec2 customMax_{0.0f, 0.0f};
    };

    inline void IWindow::Render(const Model::Theme& theme, const Model::VirtualViewport& viewport)
    {
        ImVec2 minSize{0.0f, 0.0f};
        ImVec2 maxSize{viewport.WorkSize.x - theme.globalContext.outerWindowPadding.x * 2.0f, viewport.WorkSize.y - theme.globalContext.outerWindowPadding.y * 2.0f};
        minSize.x = std::max(minSize.x, customMin_.x);
        minSize.y = std::max(minSize.y, customMin_.y);
        maxSize.x = std::min(maxSize.x, customMax_.x);
        maxSize.y = std::min(maxSize.y, customMax_.y);
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

        if (autoResizeHorizontal)
            size_.x = fixedResizeSize_.x;
        if (autoResizeVertical)
            size_.y = fixedResizeSize_.y;

        if (pos_.x + resizeDeltaPos_.x >= viewport.WorkPos.x + viewport.WorkSize.x)
            resizeDeltaPos_.x = 0.0f;
        if (pos_.x + resizeDeltaPos_.x <= viewport.WorkPos.x)
            resizeDeltaPos_.x = 0.0f;
        if (pos_.y + resizeDeltaPos_.y >= viewport.WorkPos.y + viewport.WorkSize.y)
            resizeDeltaPos_.y = 0.0f;
        if (pos_.y + resizeDeltaPos_.y <= viewport.WorkPos.y)
            resizeDeltaPos_.y = 0.0f;

        if (!floating)
        {
            resizeDeltaPos_.x = 0.0f;
            resizeDeltaPos_.y = 0.0f;
        }

        size_.x += resizeDeltaSize_.x;
        size_.y += resizeDeltaSize_.y;
        pos_.x += resizeDeltaPos_.x;
        pos_.y += resizeDeltaPos_.y;

        resizeDeltaSize_.x = 0.0f;
        resizeDeltaSize_.y = 0.0f;
        resizeDeltaPos_.x = 0.0f;
        resizeDeltaPos_.y = 0.0f;

        if (size_.x > maxSize.x)
            size_.x = maxSize.x;
        if (size_.y > maxSize.y)
            size_.y = maxSize.y;

        if (size_.x < minSize.x)
            size_.x = minSize.x;
        if (size_.y < minSize.y)
            size_.y = minSize.y;

        ImGui::SetNextWindowSize(size_, ImGuiCond_Always);
        ImGui::SetNextWindowPos(pos_, ImGuiCond_Always);
        RenderContent(theme, viewport);
    }
}
