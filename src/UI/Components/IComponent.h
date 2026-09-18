#pragma once

namespace UI::Component
{
    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual void Render() = 0;
    };
}
