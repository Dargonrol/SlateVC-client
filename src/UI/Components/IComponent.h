#pragma once
#include "Model/Theme.h"

namespace UI::Component
{
    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual void Render(const Model::Theme& theme) = 0;
    };
}
