#pragma once
#include "IComponent.h"
#include "Model/Message.h"

namespace Components
{
    class MessageBubble : public IComponent
    {
        void Render() override;

        void Draw(const Model::Message& msg);
    };
}
