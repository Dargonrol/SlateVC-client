#pragma once
#include <functional>
#include <string>
#include <imgui.h>

#include "IComponent.h"

namespace  UI::Component
{
    class TextInputField : public IComponent
    {
    public:
        using SubmitCallback = std::function<void(const std::string&)>;

        TextInputField(std::string label, std::string placeholder, const bool isPassword = false) : label_(std::move(label)), placeholder_(std::move(placeholder)), isPassword_(isPassword) {}

        void SetSubmitCallback(const SubmitCallback& onSubmit) { onSubmit_ = onSubmit; }
        void SetInputBuffer(char* buffer, size_t bufferSize) { buffer_ = buffer; bufferSize_ = bufferSize; }

        void Render(Theme& theme) override
        {
            ImGui::PushID(this);

            if (!buffer_ || !bufferSize_)
            {
                ImGui::PopID();
                return;
            }

            ImGui::PushStyleColor(ImGuiCol_FrameBg, theme.bgColor);
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, theme.bgColor2);
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, theme.bgColor2);
            ImGui::PushStyleColor(ImGuiCol_Border, theme.borderColor);
            ImGui::PushStyleColor(ImGuiCol_Text, theme.textColor);
            ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.26f, 0.59f, 0.98f, 0.35f));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, theme.rounding);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, theme.borderWidth);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, theme.framePadding);

            ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
            if (isPassword_)
                flags |= ImGuiInputTextFlags_Password;

            ImGui::PushItemWidth(-FLT_MIN);

            bool submitted = ImGui::InputTextWithHint(label_.c_str(), placeholder_.c_str(), buffer_, bufferSize_, flags);

            if (submitted && onSubmit_ && buffer_[0] != '\0')
                onSubmit_(buffer_);

            ImGui::PopItemWidth();

            ImGui::PopStyleVar(3);
            ImGui::PopStyleColor(6);

            ImGui::PopID();
        }

    private:
        std::string label_;
        std::string placeholder_;
        bool isPassword_ = false;
        SubmitCallback onSubmit_ = nullptr;
        char* buffer_ = nullptr;
        size_t bufferSize_;
    };
}
