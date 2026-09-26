#pragma once
#include <memory>
#include <vector>

#include "IComponent.h"

namespace UI::Component
{
    class IContainer : public IComponent
    {
    public:
        void AddComponent(std::unique_ptr<IComponent> component, const int index = -1)
        {
            if (!component)
                return;

            if (index <= -1 || static_cast<size_t>(index) >= children_.size())
                children_.push_back(std::move(component));
            else
                children_.insert(children_.begin() + static_cast<size_t>(index), std::move(component));
        }

        void RemoveComponent(const size_t index)
        {
            if (index >= children_.size() - 1)
                children_.pop_back();
            else
                children_.erase(children_.begin() + index);
        }

        [[nodiscard]] size_t getChildrenSize() const
        {
            return children_.size();
        }

        [[nodiscard]] IComponent* GetByIndex(size_t index)
        {
            if (index >= children_.size() -1)
            {
                IComponent* ptr = children_.back().get();
                children_.pop_back();
                return ptr;
            }
            IComponent* ptr = children_.at(index).get();
            children_.erase(children_.begin() + index);
            return ptr;
        }

    protected:
        std::vector<std::unique_ptr<IComponent>> children_;
    };
}
