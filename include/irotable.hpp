#pragma once

class IRotable
{
public:
    virtual ~IRotable() {}
    virtual void turn_left() = 0;
    virtual void turn_right() = 0;
};
