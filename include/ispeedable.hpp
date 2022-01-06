#pragma once

struct speed_s
{
    int x, y;

    speed_s()
    {
        speed_s(0, 0);
    }

    speed_s(const int x, const int y)
    {
        this->x = x;
        this->y = y;
    }

    friend bool operator == (const speed_s speed1, const speed_s speed2)
    {
        if (speed1.x == speed2.x && speed1.y == speed2.y)
            return true;
        else
            return false;
    }

    friend std::ostream& operator << (std::ostream& out, const struct speed_s& speed)
    {
        return out << "(" << speed.x << ", " << speed.y << ")";
    }
};

class ISpeedable
{
public:
    virtual ~ISpeedable() {}
    virtual struct speed_s get_speed() = 0;
    virtual void set_speed(const int x, const int y) = 0;
};
