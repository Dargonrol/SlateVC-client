#pragma once

#include "Core/Util.h"
#include "Model/Theme.h"
#include "Model/VirtualViewport.h"

namespace UI::Window
{
    class IWindow
    {
    public:
        IWindow();
        virtual ~IWindow() = default;

        void Render(const Model::Theme& theme, const Model::VirtualViewport& viewport);

        void SetWindowPos(const ImVec2 pos) { pos_ = pos; }
        void SetWindowSize(const ImVec2 size){ size_ = size; }
        void SetCustomConstrains(const ImVec2 min, const ImVec2 max) { customMin_ = min; customMax_ = max; }
        void SetWindowName(const std::string_view name) { windowTitle_ = name; }

        void OnViewportResize(const ImVec2& oldSize, const ImVec2& newSize);

        [[nodiscard]] std::string& GetWindowTitle() { return windowTitle_; }
        [[nodiscard]] ImVec2 GetWindowSize() const { return size_; }
        [[nodiscard]] ImVec2 GetWindowPos() const { return pos_; }

    protected:
        virtual void PreRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) {}
        virtual void PreContentRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) {}
        virtual void RenderContent(const Model::Theme& theme, const Model::VirtualViewport& viewport) = 0;
        virtual void PostContentRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) {}
        virtual void PostRender(const Model::Theme& theme, const Model::VirtualViewport& viewport) {}

    private:
        void WorkOutWindowSizeAndPosition(const Model::Theme& theme, const Model::VirtualViewport& viewport);
        void ApplyResizable();


    public:
        bool customRenderImplementation = false; // prevents putting DrawContent inside a child window.
        bool autoResizeHorizontal = false;
        bool autoResizeVertical = false;
        bool floating = false;
        bool showDebugChildArea = false;
        bool showDebugResizeArea = false;
        Resizable::Flags resizableFlags = Resizable::Flags::ResizableNone;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
        ImGuiWindowFlags childFlags = 0;

    protected:
        ImVec2 size_{0.0f, 0.0f};
        ImVec2 pos_{100.0f, 100.0f};
        std::string windowTitle_;
        bool isWindowHovered_ = false;

    private:
        ImVec2 resizeDeltaSize_{0.0f, 0.0f};
        ImVec2 resizeDeltaPos_{0.0f, 0.0f};
        ImVec2 fixedResizeSize_{0.0f, 0.0f};
        ImVec2 customMin_{0.0f, 0.0f};
        ImVec2 customMax_{0.0f, 0.0f};
    };
}
