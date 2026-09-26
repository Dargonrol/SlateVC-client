#pragma once
#include "IContainer.h"

namespace UI::Component
{
    class HorizontalContainer : public IContainer
    {
    public:
        explicit HorizontalContainer(const bool centered = false) : centered_(centered){};

        void SetPadding(const float padding) { padding_ = padding; }

        void Render(const Model::Theme& theme) override
        {
            if (children_.empty())
                return;

            if (children_.size() == 1)
            {
                children_[0]->Render(theme);
                return;
            }

            if (centered_)
            {
                for (size_t i = 0; i < children_.size(); ++i)
                {
                    children_[i]->Render(theme);

                    if (i + 1 < children_.size())
                    {
                        float remainingSpace = ImGui::GetContentRegionAvail().x;
                        float spacePerItem = remainingSpace / static_cast<float>(children_.size() - 1 - i);

                        ImGui::SameLine(0, spacePerItem);
                    }
                }
            } else
            {
                for (const auto& component: children_)
                {
                    component->Render(theme);
                    ImGui::SameLine(0, padding_);
                }
            }
        }

    private:
        bool centered_;
        float padding_ = 0;
    };
}
