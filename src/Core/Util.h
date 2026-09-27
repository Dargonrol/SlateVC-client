#pragma once
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

    static void MakeWindowResizable_AllDirections(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        MakeWindowResizable_AllDiagonalDirections(size, minSize, maxSize);
        MakeWindowResizable_AllHorizontalDirections(size, minSize, maxSize);
        MakeWindowResizable_AllVerticalDirections(size, minSize, maxSize);
    }
    static void MakeWindowResizable_AllDiagonalDirections(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        MakeWindowResizable_BottomLeft(size, minSize, maxSize);
        MakeWindowResizable_BottomRight(size, minSize, maxSize);
        MakeWindowResizable_TopLeft(size, minSize, maxSize);
        MakeWindowResizable_TopRight(size, minSize, maxSize);
    }
    static void MakeWindowResizable_AllHorizontalDirections(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        MakeWindowResizable_Right(size, minSize, maxSize);
        MakeWindowResizable_Left(size, minSize, maxSize);
    }
    static void MakeWindowResizable_AllVerticalDirections(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        MakeWindowResizable_Top(size, minSize, maxSize);
        MakeWindowResizable_Bottom(size, minSize, maxSize);
    }

    static void MakeWindowResizable_Top(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = padding;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeTop", ImVec2(ImGui::GetContentRegionAvail().x - padding, buttonWidth));
        PopStyle();

        if (ImGui::IsItemActive())
        {
            const float mouseDeltaY = ImGui::GetIO().MouseDelta.y;
            size.y -= mouseDeltaY;
            size.y = std::clamp(size.y, minSize.y, maxSize.y);
            ImGui::SetWindowSize(size);
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_Right(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        const float cursorPosX = size.x - buttonWidth;
        constexpr float cursorPosY = padding;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeRight", ImVec2(buttonWidth, ImGui::GetContentRegionAvail().y - padding));
        PopStyle();

        if (ImGui::IsItemActive())
        {
            const float mouseDeltaX = ImGui::GetIO().MouseDelta.x;
            size.x += mouseDeltaX;
            size.x = std::clamp(size.x, minSize.x, maxSize.x);
            ImGui::SetWindowSize(size);
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_Bottom(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = padding;
        const float cursorPosY = size.y - buttonHeight;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeBottom", ImVec2(ImGui::GetContentRegionAvail().x - padding, buttonHeight));
        PopStyle();

        if (ImGui::IsItemActive())
        {
            const float mouseDeltaY = ImGui::GetIO().MouseDelta.y;
            size.y += mouseDeltaY;
            size.y = std::clamp(size.y, minSize.y, maxSize.y);
            ImGui::SetWindowSize(size);
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_Left(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = 0.0f;
        constexpr float cursorPosY = padding;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeLeft", ImVec2(buttonWidth, ImGui::GetContentRegionAvail().y - padding));
        PopStyle();

        if (ImGui::IsItemActive())
        {
            const float mouseDeltaX = ImGui::GetIO().MouseDelta.x;
            size.x -= mouseDeltaX;
            size.x = std::clamp(size.x, minSize.x, maxSize.x);
            ImGui::SetWindowSize(size);
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        ImGui::SetCursorPos(savedCursorPos);
    }

    static void MakeWindowResizable_TopRight(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        const float cursorPosX = size.x - buttonWidth * 2;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeTopRight", ImVec2{buttonWidth * 2, buttonWidth * 2});
        PopStyle();

        if (ImGui::IsItemActive())
        {
            const float mouseDeltaX = ImGui::GetIO().MouseDelta.x;
            const float mouseDeltaY = ImGui::GetIO().MouseDelta.y;
            size.x += mouseDeltaX;
            size.y += mouseDeltaY;
            size.x = std::clamp(size.x, minSize.x, maxSize.x);
            size.y = std::clamp(size.y, minSize.y, maxSize.y);
            ImGui::SetWindowSize(size);
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_BottomRight(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        const float cursorPosX = size.x - buttonWidth * 2;
        const float cursorPosY = size.y - buttonWidth * 2;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeBottomRight", ImVec2{buttonWidth * 2, buttonWidth * 2});
        PopStyle();

        if (ImGui::IsItemActive())
        {
            const float mouseDeltaX = ImGui::GetIO().MouseDelta.x;
            const float mouseDeltaY = ImGui::GetIO().MouseDelta.y;
            size.x += mouseDeltaX;
            size.y += mouseDeltaY;
            size.x = std::clamp(size.x, minSize.x, maxSize.x);
            size.y = std::clamp(size.y, minSize.y, maxSize.y);
            ImGui::SetWindowSize(size);
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_BottomLeft(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = 0.0f;
        const float cursorPosY = size.y - buttonWidth * 2;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeBottomLeft", ImVec2{buttonWidth * 2, buttonWidth * 2});
        PopStyle();

        if (ImGui::IsItemActive())
        {
            const float mouseDeltaX = ImGui::GetIO().MouseDelta.x;
            const float mouseDeltaY = ImGui::GetIO().MouseDelta.y;
            size.x += mouseDeltaX;
            size.y += mouseDeltaY;
            size.x = std::clamp(size.x, minSize.x, maxSize.x);
            size.y = std::clamp(size.y, minSize.y, maxSize.y);
            ImGui::SetWindowSize(size);
        }

        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);

        ImGui::SetCursorPos(savedCursorPos);
    }
    static void MakeWindowResizable_TopLeft(ImVec2& size, const ImVec2& minSize, const ImVec2& maxSize)
    {
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        const ImVec2 savedCursorPos = ImGui::GetCursorPos();

        constexpr float cursorPosX = 0.0f;
        constexpr float cursorPosY = 0.0f;
        ImGui::SetCursorPos(ImVec2{cursorPosX, cursorPosY});

        PushStyle();
        ImGui::Button("##ResizeTopLeft", ImVec2{buttonWidth * 2, buttonWidth * 2});
        PopStyle();

        if (ImGui::IsItemActive())
        {
            const float mouseDeltaX = ImGui::GetIO().MouseDelta.x;
            const float mouseDeltaY = ImGui::GetIO().MouseDelta.y;
            size.x += mouseDeltaX;
            size.y += mouseDeltaY;
            size.x = std::clamp(size.x, minSize.x, maxSize.x);
            size.y = std::clamp(size.y, minSize.y, maxSize.y);
            ImGui::SetWindowSize(size);
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