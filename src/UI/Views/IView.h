#pragma once

class IView
{
public:
    virtual ~IView() = default;
    virtual void Render() = 0;
};