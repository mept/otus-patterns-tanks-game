#pragma once

class IMovable
{
public:
    virtual ~IMovable() {}
    virtual void move_forward() = 0;
};
