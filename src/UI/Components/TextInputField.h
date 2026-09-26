#pragma once
#include <functional>
#include <string>
#include <imgui.h>

#include "IComponent.h"
#include "Model/Alignment.h"
#include "Service/ThemeController.h"

namespace  UI::Component
{
    class TextInputField : public IComponent
    {
    public:
        using SubmitCallback = std::function<void(const std::string&)>;

        TextInputField(std::string label, std::string placeholder, const bool isPassword = false) : label_(std::move(label)), placeholder_(std::move(placeholder)), isPassword_(isPassword) {}

        void SetSubmitCallback(const SubmitCallback& onSubmit) { onSubmit_ = onSubmit; }
        void SetInputBuffer(char* buffer, const size_t bufferSize) { buffer_ = buffer; bufferSize_ = bufferSize; }

        void Render(const Model::Theme& theme) override
        {
            ImGui::PushID(this);

            if (!buffer_ || !bufferSize_)
            {
                ImGui::PopID();
                return;
            }

            if (theme.customTextInputField)
                Service::ThemeController::PushRenderContext(theme.textInputField);

            ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;

            if (isPassword_)
                flags |= ImGuiInputTextFlags_Password;

            ImGui::SetNextItemWidth(-FLT_MIN);

            bool submitted = ImGui::InputTextWithHint(label_.c_str(), placeholder_.c_str(), buffer_, bufferSize_, flags);

            if (submitted && onSubmit_ && buffer_[0] != '\0')
                onSubmit_(buffer_);

            if (theme.customTextInputField)
                Service::ThemeController::PopRenderContext(theme.textInputField);

            ImGui::PopID();
        }

    private:
        std::string label_;
        std::string placeholder_;
        bool isPassword_ = false;
        SubmitCallback onSubmit_ = nullptr;
        char* buffer_ = nullptr;
        size_t bufferSize_ = 0;

        // Todo: No submit button. This is atomic  element. element can be transparent. place button next to textfield and place both in horizontal alignment conatiner. The container can then be rounded ans stylized
        // Model::Position textPosition_ = Model::Position::CENTER; // not possible in ImGui
    };
}
