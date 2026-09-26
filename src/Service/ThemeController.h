#pragma once
#include "Model/Theme.h"

namespace Service
{
    class ThemeController
    {
    public:
        ThemeController() = default;
        ~ThemeController() = default;

        Model::Theme ParseTheme();

        void PushGlobalTheme() const;
        void PopGlobalTheme() const;

        void SetTheme();
        void RegisterTheme();

        [[nodiscard]] void GetThemes() const;
        [[nodiscard]] const Model::Theme& GetCurrentTeme() const;

        static void PushRenderContext(const Model::RenderContext& ctx);
        static void PopRenderContext(const Model::RenderContext& ctx);

    private:
        Model::Theme currentTheme_{};
    };
}
