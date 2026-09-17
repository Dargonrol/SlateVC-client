#pragma once
#include <cstdint>
#include <chrono>
#include <functional>

#include "IComponent.h"
#include "Core/Actions.h"

namespace Core::UI
{
    class MessageItem : public IComponent
    {
        struct Data
        {
            uint64_t messageID;
            uint64_t senderID;
            std::chrono::system_clock::time_point timestamp;
            std::string text;
            // reactions?
        };

        using ActionCallback = std::function<void(const Action, const uint64_t messageID)>;

    public:
        explicit MessageItem(const Data& data, const ActionCallback& onAction = nullptr) : data_(data), onAction_(onAction) {}

        void Render(const Context& context) override
        {
            
        }


    private:
        Data data_;
        ActionCallback onAction_;
    };

}

