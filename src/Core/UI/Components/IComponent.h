#pragma once
#include <imgui.h>
#include <memory>
#include <vector>

namespace Core::UI
{
    struct Context
    {
        ImVec4 PrimaryColor = ImVec4{0.35f, 0.40f, 0.95f, 1.00f};
        ImVec4 SecondaryColor = ImVec4{0.58f, 0.60f, 0.65f, 1.00f};
    };

    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual void Render(const Context& context) = 0;
    };

    class Container : public IComponent
    {
    public:
        void Add(std::shared_ptr<IComponent> newChild)
        {
            children_.push_back(newChild);
        }

        void Clear()
        {
            children_.clear();
        }

        void Render(const Context& context) override
        {
            for (size_t i = 0; i <= children_.size(); ++i)
            {
                ImGui::PushID(static_cast<int>(i));
                children_[i]->Render(context);
                ImGui::PopID();
            }
        };

    private:
        std::vector<std::shared_ptr<IComponent>> children_;
    };
}
