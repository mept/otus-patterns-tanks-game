#pragma once
#include <cmath>

struct location_s
{
    int x, y;

    location_s() {
        location_s(0, 0);
    }

    location_s(const int x, const int y)
    {
        this->x = x;
        this->y = y;
    }

    friend bool operator == (const location_s loc1, const location_s loc2)
    {
        if (loc1.x == loc2.x && loc1.y == loc2.y)
            return true;
        else
            return false;
    }

    friend std::ostream& operator << (std::ostream& out, const struct location_s& location)
    {
        return out << "(" << location.x << ", " << location.y << ")";
    }
};

class ILocatable
{
public:
    virtual ~ILocatable() {}
    virtual struct location_s get_location() = 0;
    virtual void set_location(const int x, const int y) = 0;
    virtual bool is_location_free(const location_s location) = 0;
    virtual void add_location_in_use(const location_s location) = 0;
    virtual void remove_location_in_use(const location_s location) = 0;
};
