#pragma once
#include <imgui.h>

namespace Model
{
    struct RenderContext
    {
        ImVec4 bgColor          = ImVec4(0.15f, 0.16f, 0.18f, 1.0f);
        ImVec4 bgColor2         = ImVec4(0.20f, 0.22f, 0.25f, 0.8f);
        ImVec4 borderColor      = ImVec4(0.30f, 0.32f, 0.35f, 1.0f);
        ImVec4 textColor        = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
        ImVec4 mutedTextColor   = ImVec4(0.80f, 0.80f, 0.80f, 1.0f);
        ImVec4 placeholderColor = ImVec4(0.50f, 0.52f, 0.55f, 1.0f);
        ImVec4 bgColor3         = ImVec4(0.15f, 0.16f, 0.18f, 1.0f);

        bool roundInnerCorners = true;
        bool roundOuterCorners = true;
        bool border = false;
        float innerRounding = 6.0f;
        float outerRounding = 10.0f;
        float borderWidth = 1.0f;
        ImVec2 framePadding = ImVec2(12.0f, 8.0f);
        ImVec2 innerWindowPadding = ImVec2{4.0f, 4.0f};
        ImVec2 outerWindowPadding = ImVec2{5.0f, 5.0f};

        static constexpr size_t countStyleVar = 4;
        static constexpr size_t countStyleColor = 6;
    };

    struct Theme
    {
        RenderContext globalContext{};
        bool customTextInputField = false; // rename to hasCustomTextInputField
        RenderContext textInputField;

    };
}
