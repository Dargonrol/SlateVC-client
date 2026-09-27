#pragma once

#include <imgui.h>

namespace Model {
    struct VirtualViewport
    {
        ImVec2 WorkSize{};
        ImVec2 WorkPos{};
    };
}