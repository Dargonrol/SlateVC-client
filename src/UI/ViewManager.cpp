#include "ViewManager.h"
#include <ranges>

using namespace UI;

void ViewManager::SwitchView(const Model::ViewType type)
{
    const auto iter = registeredViews_.find(type);
    if (iter == registeredViews_.end())
        return;

    if (currentView_)
        currentView_->OnExit();

    currentView_ = iter->second.get();
    currentViewType_ = type;

    if (currentView_)
        currentView_->OnEnter();
}

void ViewManager::InitializeViews()
{
    for (const auto& value: registeredViews_ | std::views::values)
    {
        if (!value->initialized)
        {
            value->Init();
            value->initialized = true;
        }
    }
}
void ViewManager::InitializeView(Model::ViewType type)
{
    auto iter = registeredViews_.find(type);
    if (iter != registeredViews_.end())
        if (!iter->second->initialized)
        {
            iter->second->Init();
            iter->second->initialized = true;
        }
}

void ViewManager::Render() const
{
    if (currentView_)
        currentView_->Render();
}

void ViewManager::Update() const
{
    if (currentView_)
        currentView_->Update();
}

Model::ViewType ViewManager::GetCurrentViewType() const
{
    return currentViewType_;
}

void ViewManager::OnViewportResize(const ImVec2& oldSize, const ImVec2& newSize) const
{
    if (currentView_)
        currentView_->OnViewportResize(oldSize, newSize);
}
