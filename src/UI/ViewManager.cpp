#include "ViewManager.h"

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

void ViewManager::Render() const
{
    if (currentView_)
        currentView_->Render();
}

Model::ViewType ViewManager::GetCurrentViewType() const
{
    return currentViewType_;
}
