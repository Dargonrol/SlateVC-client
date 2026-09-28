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

    enum Flags : std::uint8_t
    {
        ResizableNone       = 0 << 0,
        ResizableRight      = 1 << 0,
        ResizableBottom     = 1 << 1,
        ResizableLeft       = 1 << 2,
        ResizableTop        = 1 << 3,
        ResizableTopRight   = 1 << 4,
        ResizableBottomRight= 1 << 5,
        ResizableBottomLeft = 1 << 6,
        ResizableTopLeft    = 1 << 7
    };

    static void MakeWindowResizable_AllDirections(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        MakeWindowResizable_AllDiagonalDirections(resizeDeltaSize, resizeDeltaPos, debug);
        MakeWindowResizable_AllHorizontalDirections(resizeDeltaSize, resizeDeltaPos, debug);
        MakeWindowResizable_AllVerticalDirections(resizeDeltaSize, resizeDeltaPos, debug);
    }
    static void MakeWindowResizable_AllDiagonalDirections(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        MakeWindowResizable_BottomLeft(resizeDeltaSize, resizeDeltaPos, debug);
        MakeWindowResizable_BottomRight(resizeDeltaSize, debug);
        MakeWindowResizable_TopLeft(resizeDeltaSize, resizeDeltaPos, debug);
        MakeWindowResizable_TopRight(resizeDeltaSize, resizeDeltaPos, debug);
    }
    static void MakeWindowResizable_AllHorizontalDirections(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        MakeWindowResizable_Right(resizeDeltaSize, debug);
        MakeWindowResizable_Left(resizeDeltaSize, resizeDeltaPos, debug);
    }
    static void MakeWindowResizable_AllVerticalDirections(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        MakeWindowResizable_Top(resizeDeltaSize, resizeDeltaPos, debug);
        MakeWindowResizable_Bottom(resizeDeltaSize, debug);
    }

    static void MakeWindowResizable_Top(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = padding;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle(debug);
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
    static void MakeWindowResizable_Right(ImVec2& resizeDeltaSize, const bool debug = false)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        const float cursorPosX = windowSize.x - buttonWidth;
        constexpr float cursorPosY = padding;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle(debug);
        ImGui::Button("##ResizeRight", ImVec2(buttonWidth, ImGui::GetContentRegionAvail().y - padding));
        PopStyle();

        if (ImGui::IsItemActive())
            resizeDeltaSize.x = ImGui::GetIO().MouseDelta.x;

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_Bottom(ImVec2& resizeDeltaSize, const bool debug = false)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        constexpr float cursorPosX = padding;
        const float cursorPosY = windowSize.y - buttonHeight;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle(debug);
        ImGui::Button("##ResizeBottom", ImVec2(ImGui::GetContentRegionAvail().x - padding, buttonHeight));
        PopStyle();

        if (ImGui::IsItemActive())
            resizeDeltaSize.y = ImGui::GetIO().MouseDelta.y;

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_Left(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = 0.0f;
        constexpr float cursorPosY = padding;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle(debug);
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

    static void MakeWindowResizable_TopRight(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        const float cursorPosX = windowSize.x - buttonWidth * 2;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle(debug);
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
    static void MakeWindowResizable_BottomRight(ImVec2& resizeDeltaSize, const bool debug = false)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        const float cursorPosX = windowSize.x - buttonWidth * 2;
        const float cursorPosY = windowSize.y - buttonWidth * 2;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle(debug);
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
    static void MakeWindowResizable_BottomLeft(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();

        constexpr float cursorPosX = 0.0f;
        const float cursorPosY = windowSize.y - buttonWidth * 2;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle(debug);
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
    static void MakeWindowResizable_TopLeft(ImVec2& resizeDeltaSize, ImVec2& resizeDeltaPos, const bool debug = false)
    {
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = 0.0f;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle(debug);
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
    static void PushStyle(const bool debug = false)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(255, 0, 0, debug ? 255 : 0));
    }
    static void PopStyle()
    {
        ImGui::PopStyleColor(4);
    }
};