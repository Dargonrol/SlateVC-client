#pragma once
#include "IView.h"

class MainView : public IView
{
    MainView() = default;

    void Render() override;
};