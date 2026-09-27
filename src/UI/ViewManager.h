#pragma once
#include <memory>
#include <unordered_map>

#include "Model/ViewType.h"
#include "Views/IView.h"

namespace UI {
    class ViewManager
    {
    public:
        explicit ViewManager() = default;
        ~ViewManager() = default;

        template<typename T, typename... Args>
        void RegisterView(const Model::ViewType viewType, Args&&... args)
        {
            static_assert(std::is_base_of_v<View::IView, T>);
            registeredViews_[viewType] = std::make_unique<T>(std::forward<Args>(args)...);
        }

        void InitializeViews();
        void InitializeView(Model::ViewType type);

        void Render() const;
        void Update() const;
        void SwitchView(Model::ViewType type);

        void OnViewportResize(const ImVec2& oldSize, const ImVec2& newSize) const;

        [[nodiscard]] Model::ViewType GetCurrentViewType() const;

    private:
        std::unordered_map<Model::ViewType, std::unique_ptr<View::IView>> registeredViews_;

        View::IView* currentView_{};
        Model::ViewType currentViewType_{};
    };
}
