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
        navBar_.SetWindowSize(initialWindowSize, ImGuiCond_FirstUseEver);

        initialWindowSize = {200.0f, viewport_->WorkSize.y};
        serverAndStatus_.SetWindowSize(initialWindowSize, ImGuiCond_FirstUseEver);

        initialWindowSize = {240.0f, viewport_->WorkSize.y};
        contextList_.SetWindowSize(initialWindowSize, ImGuiCond_FirstUseEver);
    }

    void MainView::Render()
    {
        const Model::Theme& theme = themeController_.GetCurrentTeme();

        DrawNavBar(theme);
        DrawServerAndStatusBar(theme);
        DrawContextList(theme);
        DrawChatWindow(theme);
    }

    void MainView::DrawNavBar(const Model::Theme& theme)
    {
        const ImVec2 windowPosition{viewport_->WorkPos.x, viewport_->WorkPos.y};
        navBar_.SetWindowPos(windowPosition, ImGuiCond_Always);

        navBar_.Render(theme, *viewport_);
    }

    void MainView::DrawServerAndStatusBar(const Model::Theme& theme)
    {
        const ImVec2 windowPosition{viewport_->WorkPos.x + navBar_.GetWindowSize().x, viewport_->WorkPos.y};
        serverAndStatus_.SetWindowPos(windowPosition, ImGuiCond_Always);

        serverAndStatus_.Render(theme, *viewport_);
    }

    void MainView::DrawContextList(const Model::Theme& theme)
    {
        const ImVec2 windowPosition{viewport_->WorkPos.x + viewport_->WorkSize.x - contextList_.GetWindowSize().x, viewport_->WorkPos.y};
        contextList_.SetWindowPos(windowPosition, ImGuiCond_Always);

        contextList_.Render(theme, *viewport_);
    }

    void MainView::DrawChatWindow(const Model::Theme& theme)
    {
        const ImVec2 windowSize{viewport_->WorkSize.x - navBar_.GetWindowSize().x - serverAndStatus_.GetWindowSize().x - contextList_.GetWindowSize().x, viewport_->WorkSize.y};
        const ImVec2 windowPosition{viewport_->WorkPos.x + navBar_.GetWindowSize().x + serverAndStatus_.GetWindowSize().x, viewport_->WorkPos.y};

        chatWindow_.SetWindowSize(windowSize, ImGuiCond_Always);
        chatWindow_.SetWindowPos(windowPosition, ImGuiCond_Always);

        chatWindow_.Render(theme, *viewport_);
    }
}