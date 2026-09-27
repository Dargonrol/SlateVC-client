#pragma once
#include "IView.h"
#include <functional>
#include <imgui.h>
#include "Model/ViewType.h"
#include "Model/VirtualViewport.h"
#include "Service/ThemeController.h"
#include "UI/Windows/ChatWindow.h"
#include "UI/Windows/ContextList.h"
#include "UI/Windows/NavigationBar.h"
#include "UI/Windows/ServerAndStatus.h"
#include "UI/Windows/TitleBar.h"

namespace UI::View
{
    class MainView : public IView
    {
    public:
        using NavCallback = std::function<void(Model::ViewType)>;

        explicit MainView(NavCallback navCallback, const Service::ThemeController& themeController);

        void Init() override;

        void Render() override;
        void Update() override;

        void OnEnter() override {};
        void OnExit() override {};

        void OnViewportResize(const ImVec2& oldSize, const ImVec2& newSize) override;

    private:
        void DrawTitleBar(const Model::Theme& theme);
        void DrawChatWindow(const Model::Theme& theme);
        void DrawServerAndStatusBar(const Model::Theme& theme);
        void DrawContextList(const Model::Theme& theme); // Memberlist and other tabs like quick channel options
        void DrawNavBar(const Model::Theme& theme);

        void RecalculateWorkspace(ImVec2 size = {0.0f, 0.0f});

    private:
        NavCallback navCallback_;

        const Service::ThemeController& themeController_;
        ImGuiViewport* viewport_{};
        Model::VirtualViewport contentArea_{};

        Window::TitleBar titleBar_{};
        Window::NavigationBar navBar_{};
        Window::ServerAndStatus serverAndStatus_{};
        Window::ContextList contextList_{};
        Window::ChatWindow chatWindow_{};

        enum class Layout
        {
            DEFAULT,
            ONE
        };
    };
}
