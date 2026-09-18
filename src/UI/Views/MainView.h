#pragma once
#include "IView.h"

namespace UI::View
{
    class MainView : public IView
    {
    public:
        using NavCallback = std::function<void(Model::ViewType)>;

        explicit MainView(NavCallback navCallback) : navCallback_(std::move(navCallback)) {};

        void Render() override;

        void OnEnter() override;
        void OnExit() override;

    private:
        NavCallback navCallback_;
    };
}