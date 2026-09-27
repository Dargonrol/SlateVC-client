#pragma once
#include <complex>
#include <iostream>

#include "glad/glad.h"
#include <imgui.h>

#if defined(__clang__) || defined(__GNUC__)
    #define DEBUG_BREAK() __builtin_trap()
#elif defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#else
    #include <signal.h>
    #define DEBUG_BREAK() raise(SIGTRAP)
#endif

#ifndef SOURCE_DIR
    #define SOURCE_DIR ""
#endif
#define BASE_PATH std::filesystem::path(SOURCE_DIR)

#ifdef RELEASE
    #define ASSERT(x)
    #define GLCall(x) x;
#else
//#include "core/OpenGL.h"

inline void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << ") in " << function << " at " << file << ":" << line << "\n";
        return false;
    }
    return true;
}
#define ASSERT(x) if (!(x)) DEBUG_BREAK();
#define GLCall(x) {GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))}
#endif

inline void debug_info()
{
#ifdef DEBUG_BUILD
    std::cout << "Debug build\n";
    if (sizeof(void*) == 8) {
        std::cout << "Runtime: 64-bit process\n";
    } else if (sizeof(void*) == 4) {
        std::cout << "Runtime: 32-bit process\n";
    } else {
        std::cout << "Unknown pointer size\n";
    }
    std::cout << std::flush;
#endif
}

class InvisibleResizeGrip
{
public:
    InvisibleResizeGrip()
    {
        ImGui::PushStyleColor(ImGuiCol_ResizeGrip, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    }
    ~InvisibleResizeGrip()
    {
        ImGui::PopStyleColor(3);
    }
};

class Resizable
{
public:
    static constexpr float buttonWidth = 4.0f;
    static constexpr float buttonHeight = 4.0f;
    static constexpr float padding = 8.0f;

    static void MakeWindowResizable_AllDirections(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        MakeWindowResizable_AllDiagonalDirections(resizeDeltaSize, resizeDeltaPos);
        MakeWindowResizable_AllHorizontalDirections(resizeDeltaSize, resizeDeltaPos);
        MakeWindowResizable_AllVerticalDirections(resizeDeltaSize, resizeDeltaPos);
    }
    static void MakeWindowResizable_AllDiagonalDirections(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        MakeWindowResizable_BottomLeft(resizeDeltaSize, resizeDeltaPos);
        MakeWindowResizable_BottomRight(resizeDeltaSize);
        MakeWindowResizable_TopLeft(resizeDeltaSize, resizeDeltaPos);
        MakeWindowResizable_TopRight(resizeDeltaSize, resizeDeltaPos);
    }
    static void MakeWindowResizable_AllHorizontalDirections(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        MakeWindowResizable_Right(resizeDeltaSize);
        MakeWindowResizable_Left(resizeDeltaSize, resizeDeltaPos);
    }
    static void MakeWindowResizable_AllVerticalDirections(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        MakeWindowResizable_Top(resizeDeltaSize, resizeDeltaPos);
        MakeWindowResizable_Bottom(resizeDeltaSize);
    }

    static void MakeWindowResizable_Top(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = padding;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeTop", ImVec2(ImGui::GetContentRegionAvail().x - padding, buttonWidth));
        PopStyle();

        if (ImGui::IsItemActive())
        {
            resizeDeltaSize.y = -ImGui::GetIO().MouseDelta.y;
            resizeDeltaPos.y = ImGui::GetIO().MouseDelta.y;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_Right(ImVec2& resizeDeltaSize)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        const float cursorPosX = windowSize.x - buttonWidth;
        constexpr float cursorPosY = padding;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeRight", ImVec2(buttonWidth, ImGui::GetContentRegionAvail().y - padding));
        PopStyle();

        if (ImGui::IsItemActive())
            resizeDeltaSize.x = ImGui::GetIO().MouseDelta.x;

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_Bottom(ImVec2& resizeDeltaSize)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        constexpr float cursorPosX = padding;
        const float cursorPosY = windowSize.y - buttonHeight;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeBottom", ImVec2(ImGui::GetContentRegionAvail().x - padding, buttonHeight));
        PopStyle();

        if (ImGui::IsItemActive())
            resizeDeltaSize.y = ImGui::GetIO().MouseDelta.y;

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_Left(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = 0.0f;
        constexpr float cursorPosY = padding;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeLeft", ImVec2(buttonWidth, ImGui::GetContentRegionAvail().y - padding));
        PopStyle();

        if (ImGui::IsItemActive())
        {
            resizeDeltaSize.x = -ImGui::GetIO().MouseDelta.x;
            resizeDeltaPos.x = ImGui::GetIO().MouseDelta.x;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        ImGui::SetCursorPos(savedCursorPos);
    }

    static void MakeWindowResizable_TopRight(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        const float cursorPosX = windowSize.x - buttonWidth * 2;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeTopRight", ImVec2{buttonWidth * 2, buttonWidth * 2});
        PopStyle();

        if (ImGui::IsItemActive())
        {
            resizeDeltaSize.x = ImGui::GetIO().MouseDelta.x;
            resizeDeltaSize.y = -ImGui::GetIO().MouseDelta.y;
            resizeDeltaPos.y = ImGui::GetIO().MouseDelta.y;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_BottomRight(ImVec2& resizeDeltaSize)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        const float cursorPosX = windowSize.x - buttonWidth * 2;
        const float cursorPosY = windowSize.y - buttonWidth * 2;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeBottomRight", ImVec2{buttonWidth * 2, buttonWidth * 2});
        PopStyle();

        if (ImGui::IsItemActive())
        {
            resizeDeltaSize.x = ImGui::GetIO().MouseDelta.x;
            resizeDeltaSize.y = ImGui::GetIO().MouseDelta.y;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_BottomLeft(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        constexpr float cursorPosX = 0.0f;
        const float cursorPosY = windowSize.y - buttonWidth * 2;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeBottomLeft", ImVec2{buttonWidth * 2, buttonWidth * 2});
        PopStyle();

        if (ImGui::IsItemActive())
        {
            resizeDeltaSize.x = -ImGui::GetIO().MouseDelta.x;
            resizeDeltaSize.y = ImGui::GetIO().MouseDelta.y;
            resizeDeltaPos.x = ImGui::GetIO().MouseDelta.x;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_TopLeft(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = 0.0f;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeTopLeft", ImVec2{buttonWidth * 2, buttonWidth * 2});
        PopStyle();

        if (ImGui::IsItemActive())
        {
            resizeDeltaSize.x = -ImGui::GetIO().MouseDelta.x;
            resizeDeltaSize.y = -ImGui::GetIO().MouseDelta.y;
            resizeDeltaPos.x = ImGui::GetIO().MouseDelta.x;
            resizeDeltaPos.y = ImGui::GetIO().MouseDelta.y;
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);

        ImGui::SetCursorPos(savedCursorPos);
    }

private:
    static void PushStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(255, 0, 0, 255));
    }
    static void PopStyle()
    {
        ImGui::PopStyleColor(4);
    }
};