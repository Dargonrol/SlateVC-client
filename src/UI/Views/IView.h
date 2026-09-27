#pragma once

#include <imgui.h>

namespace UI::View
{
    class IView
    {
    public:
        virtual ~IView() = default;
        virtual void Init() {};
        virtual void Render() = 0;
        virtual void Update() {};

        virtual void OnViewportResize(const ImVec2& oldSize, const ImVec2& newSize) {};

        virtual void OnEnter() {};
        virtual void OnExit() {};

    public:
        bool initialized = false;
    };
}

