#pragma once
#include "IView.h"
#include "Model/ViewType.h"
#include <functional>

#include "UI/Components/IComponent.h"
#include "UI/Components/TextInputField.h"

#define BUFFER_SIZE 256

namespace UI::View
{
    class LoginView : public IView
    {
    public:
        using NavCallback = std::function<void(Model::ViewType)>;

        explicit LoginView(NavCallback navCallback) : navCallback_(std::move(navCallback))
        {
            using SubmitCallback = std::function<void(const std::string&)>;

            const SubmitCallback cb = [this](const std::string&)
            {
                if (navCallback_)
                    navCallback_(Model::ViewType::MAIN);
            };

            serverAddressField_ = std::make_unique<Component::TextInputField>("##address", "server address", false);
            userNameField_ = std::make_unique<Component::TextInputField>("##user", "username", false);
            passwordField_ = std::make_unique<Component::TextInputField>("##pass", "password", true);

            serverAddressField_->SetInputBuffer(addressBuffer_, BUFFER_SIZE);
            userNameField_->SetInputBuffer(userNameBuffer_, BUFFER_SIZE);
            passwordField_->SetInputBuffer(passwordBuffer_, BUFFER_SIZE);
            serverAddressField_->SetSubmitCallback(cb);
            userNameField_->SetSubmitCallback(cb);
            passwordField_->SetSubmitCallback(cb);
        };

        void Render() override
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();

            const ImVec2 windowSize = ImVec2(
                std::clamp(viewport->WorkSize.x * 0.40f, 320.0f, 600.0f),
                std::clamp(viewport->WorkSize.y * 0.50f, 250.0f, 500.0f)
            );

            const ImVec2 windowPos = ImVec2(
                viewport->WorkPos.x + (viewport->WorkSize.x - windowSize.x) * 0.5f,
                viewport->WorkPos.y + (viewport->WorkSize.y - windowSize.y) * 0.5f
            );

            ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
            ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

            constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;

            Theme theme{};
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, theme.rounding); // z.B. 12.0f
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, theme.borderWidth); // z.B. 1.0f
            ImGui::PushStyleColor(ImGuiCol_WindowBg, theme.bgColor);
            ImGui::PushStyleColor(ImGuiCol_Border, theme.borderColor);

            ImGui::Begin("Login Window", nullptr, windowFlags);

            serverAddressField_->Render(theme);
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            userNameField_->Render(theme);
            passwordField_->Render(theme);

            ImGui::End();

            ImGui::PopStyleColor(2);
            ImGui::PopStyleVar(2);
        };

        void OnEnter() override {};
        void OnExit() override {};

    private:
        NavCallback navCallback_;

        // components
        std::unique_ptr<Component::TextInputField> serverAddressField_;
        std::unique_ptr<Component::TextInputField> userNameField_;
        std::unique_ptr<Component::TextInputField> passwordField_;

        char addressBuffer_[BUFFER_SIZE] = "";
        char userNameBuffer_[BUFFER_SIZE] = "";
        char passwordBuffer_[BUFFER_SIZE] = "";

    };
}
