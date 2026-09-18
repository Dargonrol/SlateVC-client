#pragma once
#include "IView.h"
#include <functional>
#include "Model/ViewType.h"

namespace UI::View
{
    class MainView : public IView
    {
    public:
        using NavCallback = std::function<void(Model::ViewType)>;

        explicit MainView(NavCallback navCallback) : navCallback_(std::move(navCallback)) {};

        void Render() override
        {
            ImGui::Begin("Main window");
            ImGui::Text("this is the main window");
            ImGui::Spacing();
            if (ImGui::Button("switch to login view"))
            {
                navCallback_(Model::ViewType::LOGIN);
            }
            ImGui::End();
        };

        void OnEnter() override {};
        void OnExit() override {};

    private:
        NavCallback navCallback_;
    };
}