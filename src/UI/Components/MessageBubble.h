#pragma once
#include "IComponent.h"
#include "Model/Message.h"

namespace UI::Component
{
    class MessageBubble : public IComponent
    {
        void Render(Theme& theme) override;

        void Draw(const Model::Message& msg);
    };
}
