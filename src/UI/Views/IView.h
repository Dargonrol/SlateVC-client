#pragma once

namespace UI::View
{
    class IView
    {
    public:
        virtual ~IView() = default;
        virtual void Render() = 0;

        virtual void OnEnter() {};
        virtual void OnExit() {};
    };
}

