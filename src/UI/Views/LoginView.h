#pragma once
#include "IView.h"
#include "Model/ViewType.h"

namespace UI::View
{
    class LoginView : public IView
    {
    public:
        using NavCallback = std::function<void(Model::ViewType)>;

        explicit LoginView(NavCallback navCallback) : navCallback_(std::move(navCallback)) {};

        void Render() override;

        void OnEnter() override;
        void OnExit() override;

    private:
        NavCallback navCallback_;

    };
}
