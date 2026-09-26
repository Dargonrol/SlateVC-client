#include "ThemeController.h"

namespace Service
{
    void ThemeController::PushGlobalTheme() const
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBg, currentTheme_.globalContext.bgColor);
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, currentTheme_.globalContext.bgColor2);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, currentTheme_.globalContext.bgColor2);
        ImGui::PushStyleColor(ImGuiCol_Border, currentTheme_.globalContext.borderColor);
        ImGui::PushStyleColor(ImGuiCol_Text, currentTheme_.globalContext.textColor);
        ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.26f, 0.59f, 0.98f, 0.35f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, currentTheme_.globalContext.rounding);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, currentTheme_.globalContext.borderWidth);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, currentTheme_.globalContext.framePadding);
    }

    void ThemeController::PopGlobalTheme() const
    {
        ImGui::PopStyleVar(4);
        ImGui::PopStyleColor(6);
    }

    const Model::Theme& ThemeController::GetCurrentTeme() const
    {
        return currentTheme_;
    }

    void ThemeController::PushRenderContext(const Model::RenderContext& ctx)
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ctx.bgColor);
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ctx.bgColor2);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ctx.bgColor2);
        ImGui::PushStyleColor(ImGuiCol_Border, ctx.borderColor);
        ImGui::PushStyleColor(ImGuiCol_Text, ctx.textColor);
        ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.26f, 0.59f, 0.98f, 0.35f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, ctx.rounding);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, ctx.borderWidth);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ctx.framePadding);
    }

    void ThemeController::PopRenderContext(const Model::RenderContext& ctx)
    {
        ImGui::PopStyleVar(ctx.countStyleVar);
        ImGui::PopStyleColor(ctx.countStyleColor);
    }
}
