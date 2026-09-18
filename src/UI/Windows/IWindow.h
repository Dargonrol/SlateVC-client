#pragma once

class IWindow
{
public:
    virtual ~IWindow() = default;
    virtual void Render() = 0;
};