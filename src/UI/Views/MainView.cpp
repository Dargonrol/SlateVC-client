#include "MainView.h"

#include <imgui.h>
#include <algorithm>

#include "Model/Theme.h"

namespace UI::View
{
    void MainView::Update()
    {
        viewport_ = ImGui::GetMainViewport();
    }

    MainView::MainView(NavCallback navCallback, const Service::ThemeController& themeController) : navCallback_(std::move(navCallback)), themeController_(themeController)
    {
        viewport_ = ImGui::GetMainViewport();

        ImVec2 initialWindowSize{60.0f, viewport_->WorkSize.y};
        navBar_.SetWindowSize(initialWindowSize);

        initialWindowSize = {200.0f, viewport_->WorkSize.y};
        serverAndStatus_.SetWindowSize(initialWindowSize);

        initialWindowSize = {240.0f, viewport_->WorkSize.y};
        contextList_.SetWindowSize(initialWindowSize);
    }

    void MainView::Render()
    {
        const Model::Theme& theme = themeController_.GetCurrentTeme();

        std::cout << "Navbar: " << navBar_.GetWindowSize().x << std::endl;
        std::cout << "Server: " << serverAndStatus_.GetWindowSize().x << std::endl;
        std::cout << "Chat: " << chatWindow_.GetWindowSize().x << std::endl;
        std::cout << "Context: " << contextList_.GetWindowSize().x << std::endl;


        DrawNavBar(theme);
        DrawServerAndStatusBar(theme);
        DrawContextList(theme);
        DrawChatWindow(theme);
    }

    void MainView::DrawNavBar(const Model::Theme& theme)
    {
        const ImVec2 windowPosition{viewport_->WorkPos.x + theme.globalContext.outerWindowPadding.x, viewport_->WorkPos.y + theme.globalContext.outerWindowPadding.y};
        navBar_.SetWindowPos(windowPosition);

        navBar_.Render(theme, *viewport_);
    }

    void MainView::DrawServerAndStatusBar(const Model::Theme& theme)
    {
        const ImVec2 windowPosition{viewport_->WorkPos.x + navBar_.GetWindowSize().x + theme.globalContext.outerWindowPadding.x * 2.0f, viewport_->WorkPos.y + theme.globalContext.outerWindowPadding.y};
        serverAndStatus_.SetWindowPos(windowPosition);

        serverAndStatus_.Render(theme, *viewport_);
    }

    void MainView::DrawContextList(const Model::Theme& theme)
    {
        const ImVec2 windowPosition{viewport_->WorkPos.x + viewport_->WorkSize.x - contextList_.GetWindowSize().x - theme.globalContext.outerWindowPadding.x, viewport_->WorkPos.y + theme.globalContext.outerWindowPadding.y};
        contextList_.SetWindowPos(windowPosition);

        contextList_.Render(theme, *viewport_);
    }

    void MainView::DrawChatWindow(const Model::Theme& theme)
    {
        const float calculatedWidth = viewport_->WorkSize.x
                                    - navBar_.GetWindowSize().x
                                    - serverAndStatus_.GetWindowSize().x
                                    - contextList_.GetWindowSize().x
                                    - theme.globalContext.outerWindowPadding.x * 5.0f;

        const float finalChatWidth = std::max(calculatedWidth, 10.0f);

        const ImVec2 windowSize{finalChatWidth, viewport_->WorkSize.y - theme.globalContext.outerWindowPadding.y * 2.0f};
        const ImVec2 windowPosition{viewport_->WorkPos.x + navBar_.GetWindowSize().x + serverAndStatus_.GetWindowSize().x + theme.globalContext.outerWindowPadding.x * 3.0f, viewport_->WorkPos.y + theme.globalContext.outerWindowPadding.y};

        chatWindow_.SetWindowSize(windowSize);
        chatWindow_.SetWindowPos(windowPosition);

        chatWindow_.Render(theme, *viewport_);
    }
}