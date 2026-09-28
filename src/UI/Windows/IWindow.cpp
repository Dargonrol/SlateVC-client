#include "IWindow.h"

#include "Core/Util.h"

namespace UI::Window
{
    IWindow::IWindow()
    {
        std::ostringstream ss;
        ss << "##" << this;
        windowTitle_ = ss.str();
    }

    void IWindow::OnViewportResize(const ImVec2& oldSize, const ImVec2& newSize)
    {
        if (autoResizeHorizontal)
            fixedResizeSize_.x = newSize.x;
        if (autoResizeVertical)
            fixedResizeSize_.y = newSize.y;
    }

    void IWindow::Render(const Model::Theme& theme, const Model::VirtualViewport& viewport)
    {
        WorkOutWindowSizeAndPosition(theme, viewport);

        ImGui::SetNextWindowSize(size_, ImGuiCond_Always);
        ImGui::SetNextWindowPos(pos_, ImGuiCond_Always);

        PreRender(theme, viewport);

        ImGui::Begin(windowTitle_.c_str(), nullptr, windowFlags);
        {
            isWindowHovered_ = ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_RootAndChildWindows | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
            if (!customRenderImplementation)
            {
                ImGui::SetCursorPos(theme.globalContext.innerWindowPadding);

                if (showDebugChildArea)
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.2f, 0.6f, 0.2f, 0.5f});

                constexpr float MagicPaddingNumber = 11.001f;
                const float contentSizeYPadding = theme.globalContext.innerWindowPadding.y < MagicPaddingNumber ? MagicPaddingNumber + theme.globalContext.innerWindowPadding.y : theme.globalContext.innerWindowPadding.y * 2.0f;
                const ImVec2 contentSize{
                    size_.x - theme.globalContext.innerWindowPadding.x * 2.0f,
                    size_.y - contentSizeYPadding
                };

                PreContentRender(theme, viewport);
                ImGui::BeginChild("child", contentSize, false, childFlags);

                RenderContent(theme, viewport);

                ImGui::EndChild();
                PostContentRender(theme, viewport);

                if (showDebugChildArea)
                    ImGui::PopStyleColor(1);
            } else
            {
                RenderContent(theme, viewport);
            }

            ApplyResizable();
        }
        ImGui::End();

        PostRender(theme, viewport);
    }

    void IWindow::WorkOutWindowSizeAndPosition(const Model::Theme& theme, const Model::VirtualViewport& viewport)
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
    }

    void IWindow::ApplyResizable()
    {
        if (resizableFlags == Resizable::Flags::ResizableNone)
            return;
        if (resizableFlags & Resizable::Flags::ResizableRight)
            Resizable::MakeWindowResizable_Right(resizeDeltaSize_, showDebugResizeArea);
        if (resizableFlags & Resizable::Flags::ResizableBottom)
            Resizable::MakeWindowResizable_Bottom(resizeDeltaSize_, showDebugResizeArea);
        if (resizableFlags & Resizable::Flags::ResizableLeft)
            Resizable::MakeWindowResizable_Left(resizeDeltaSize_, resizeDeltaPos_, showDebugResizeArea);
        if (resizableFlags & Resizable::Flags::ResizableTop)
            Resizable::MakeWindowResizable_Top(resizeDeltaSize_, resizeDeltaPos_, showDebugResizeArea);
        if (resizableFlags & Resizable::Flags::ResizableTopRight)
            Resizable::MakeWindowResizable_TopRight(resizeDeltaSize_, resizeDeltaPos_, showDebugResizeArea);
        if (resizableFlags & Resizable::Flags::ResizableBottomRight)
            Resizable::MakeWindowResizable_BottomRight(resizeDeltaSize_, showDebugResizeArea);
        if (resizableFlags & Resizable::Flags::ResizableBottomLeft)
            Resizable::MakeWindowResizable_BottomLeft(resizeDeltaSize_, resizeDeltaPos_, showDebugResizeArea);
        if (resizableFlags & Resizable::Flags::ResizableTopLeft)
            Resizable::MakeWindowResizable_TopLeft(resizeDeltaSize_, resizeDeltaPos_, showDebugResizeArea);
    }
}
