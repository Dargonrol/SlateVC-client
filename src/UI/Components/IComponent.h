#pragma once

class IComponent
{
public:
    virtual ~IComponent() = default;
    virtual void Render() = 0;
};