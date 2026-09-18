#pragma once

namespace UI::Window
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;
        virtual void Render() = 0;
    };
}