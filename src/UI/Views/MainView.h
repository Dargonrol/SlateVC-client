#pragma once
#include "IView.h"
#include <functional>
#include <imgui.h>
#include "Model/ViewType.h"
#include "Service/ThemeController.h"
#include "UI/Windows/ChatWindow.h"
#include "UI/Windows/ContextList.h"
#include "UI/Windows/NavigationBar.h"
#include "UI/Windows/ServerAndStatus.h"

namespace UI::View
{
    class MainView : public IView
    {
    public:
        using NavCallback = std::function<void(Model::ViewType)>;

        explicit MainView(NavCallback navCallback, const Service::ThemeController& themeController);

        void Render() override;
        void Update() override;

        void OnEnter() override {};
        void OnExit() override {};

    private:
        void DrawChatWindow(const Model::Theme& theme);
        void DrawServerAndStatusBar(const Model::Theme& theme);
        void DrawContextList(const Model::Theme& theme); // Memberlist and other tabs like quick channel options
        void DrawNavBar(const Model::Theme& theme);

    private:
        NavCallback navCallback_;

        const Service::ThemeController& themeController_;
        ImGuiViewport* viewport_{};

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
