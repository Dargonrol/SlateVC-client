#pragma once
#include "IView.h"
#include "Model/ViewType.h"
#include <functional>

namespace UI::View
{
    class LoginView : public IView
    {
    public:
        using NavCallback = std::function<void(Model::ViewType)>;

        explicit LoginView(NavCallback navCallback) : navCallback_(std::move(navCallback)) {};

        void Render() override
        {
            ImGui::Begin("login window");
            ImGui::Text("this is the login window");
            ImGui::Spacing();
            if (ImGui::Button("switch to main view"))
            {
                navCallback_(Model::ViewType::MAIN);
            }
            ImGui::End();
        };

        void OnEnter() override {};
        void OnExit() override {};

    private:
        NavCallback navCallback_;

    };
}
