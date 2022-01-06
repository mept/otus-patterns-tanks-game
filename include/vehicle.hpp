#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <imovable.hpp>
#include <irotable.hpp>
#include <ilocatable.hpp>
#include <ispeedable.hpp>

using namespace std;

vector<location_s> locations_in_use_list; // Список занятых на текущий момент координат

class Vehicle : public IMovable, IRotable, ILocatable, ISpeedable
{
private:
    string name;
    struct location_s current_location;
    struct speed_s current_speed;
public:
    Vehicle()
    {
        Vehicle("Объект", location_s(), speed_s());
    }

    Vehicle(const string name, const struct location_s location, const struct speed_s speed) {
        set_name(name);
        set_location(location.x, location.y);
        set_speed(speed.x, speed.y);
    }
    ~Vehicle()
    {
        remove_location_in_use(get_location());
    }

    void set_name(const string name)
    {
        this->name = name;
    }

    string get_name()
    {
        return name;
    }

    struct location_s get_location() override
    {
        return current_location;
    }

    void set_location(const int x, const int y) override
    {
        current_location = location_s(x, y);

        cout << get_name() << " помещен в точку (" << current_location.x << ", " << current_location.y << ")" << endl;
    }

    void move_forward() override
    {
        cout << "Занятые позиции: ";
        for (unsigned int i = 0; i < locations_in_use_list.size(); i++)
        {
            cout << "(" << locations_in_use_list[i].x << ", " << locations_in_use_list[i].y << "), ";
        }

        cout << endl;

        location_s next_location(current_location.x, current_location.y);
        next_location.x += current_speed.x;
        next_location.y += current_speed.y;

        cout << "Проверка занятости позиции (" << next_location.x << ", " << next_location.y << ")" << endl;

        if (is_location_free(next_location))
        {
            remove_location_in_use(current_location);
            current_location = next_location;
            add_location_in_use(current_location);
            cout << get_name() << " переместился в точку (" << current_location.x << ", " << current_location.y << ")" << endl;
        }
        else
        {
            cout << "[Ошибка] Перемещение невозможно, точка (" << next_location.x << ", " << next_location.y << ") уже занята другим объектом" << endl;
            throw invalid_argument("Перемещение невозможно, точка уже занята другим объектом");
        }
    }

    void turn_left() override
    {
        turn_left(get_speed().x, get_speed().y);
    }

    void turn_left(const int x, const int y)
    {
        set_speed(-y, x);

        cout << "Поворот налево" << endl;
    }

    void turn_right() override
    {
        turn_right(get_speed().x, get_speed().y);
    }

    void turn_right(const int x, const int y)
    {
        set_speed(y, -x);
        cout << "Поворот направо" << endl;
    }

    struct speed_s get_speed() override
    {
        return current_speed;
    }

    void set_speed(const int x, const int y) override
    {
        current_speed = speed_s(x, y);
    }

    bool is_location_free(const location_s location) override
    {
        return std::find(locations_in_use_list.begin(), locations_in_use_list.end(), location) == locations_in_use_list.end();
    }

    void add_location_in_use(const location_s location) override
    {
        locations_in_use_list.push_back(location);
    }

    void remove_location_in_use(const location_s location) override
    {
        locations_in_use_list.erase(std::remove(locations_in_use_list.begin(), locations_in_use_list.end(), location), locations_in_use_list.end());
    }
};
