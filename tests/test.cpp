#define CATCH_CONFIG_MAIN
#include <3rdparty/catch.hpp>
#include <vehicle.hpp>
#include <ilocatable.hpp>
#include <vector>
#include <cstring>

using namespace std;

TEST_CASE("Движение с поворотом направо с возвратом в исходную точку") {
    cout << "Выполнение теста №1..." << endl;

    struct location_s start_location(0, 0);
    struct location_s expected_end_location(0, 0);
    struct speed_s tank_speed(1, 2);

    Vehicle *tank = new Vehicle("Танк", start_location, tank_speed);

    tank->move_forward();

    tank->turn_right();
    tank->move_forward();

    tank->turn_right();
    tank->move_forward();

    tank->turn_right();
    tank->move_forward();

    CHECK(tank->get_location() == expected_end_location);

    cout << endl;

    delete tank;
}

TEST_CASE("Движение с поворотом налево с возвратом в исходную точку") {
    cout << "Выполнение теста №2..." << endl;

    struct location_s start_location(0, 0);
    struct location_s expected_end_location(0, 0);
    struct speed_s tank_speed(1, 2);

    Vehicle *tank = new Vehicle("Танк", start_location, tank_speed);

    tank->move_forward();

    tank->turn_left();
    tank->move_forward();

    tank->turn_left();
    tank->move_forward();

    tank->turn_left();
    tank->move_forward();

    CHECK(tank->get_location() == expected_end_location);

    cout << endl;

    delete tank;
}

TEST_CASE("Движение с поворотами в разные стороны") {
    cout << "Выполнение теста №3..." << endl;

    struct location_s start_location(0, 0);
    struct location_s expected_end_location(1, 7);
    struct speed_s tank_speed(1, 2);

    Vehicle *tank = new Vehicle("Танк", start_location, tank_speed);

    tank->move_forward();

    tank->turn_left();
    tank->move_forward();

    tank->turn_right();
    tank->move_forward();
    tank->move_forward();

    CHECK(tank->get_location() == expected_end_location);

    cout << endl;

    delete tank;
}

TEST_CASE("9. Для объекта, находящегося в точке (12, 5) и движущегося со скоростью (-7, 3) движение меняет положение объекта на (5, 8)") {
    cout << "Выполнение теста №9..." << endl;

    struct location_s start_location(12, 5);
    struct location_s expected_end_location(5, 8);
    struct speed_s tank_speed(-7, 3);

    Vehicle *tank = new Vehicle("Танк", start_location, tank_speed);

    tank->move_forward();

    CHECK(tank->get_location() == expected_end_location);

    cout << endl;

    delete tank;
}

TEST_CASE("12. Попытка сдвинуть объект, у которого невозможно изменить положение в пространстве, приводит к ошибке. Попытка перемещения на занятую позицию") {
    cout << "Выполнение теста №12..." << endl;
    struct location_s start_location_1(5, 0);
    struct location_s start_location_2(0, 5);

    struct speed_s tank_1_speed(-1, 1);
    struct speed_s tank_2_speed(1, -1);

    struct location_s expected_first_tank_location(2, 3);
    struct location_s expected_second_tank_location_before_error(1, 4);

    Vehicle *tank_moving_north = new Vehicle("Танк 1", start_location_1, tank_1_speed);
    Vehicle *tank_moving_east = new Vehicle("Танк 2", start_location_2, tank_2_speed);

    // Передвигаем первый танк на три шага
    tank_moving_north->move_forward();
    tank_moving_north->move_forward();
    tank_moving_north->move_forward();

    // Проверяем, что конечная позиция первого танка соответствует ожидамой
    CHECK(tank_moving_north->get_location() == expected_first_tank_location);

    // Передвигаем второй танк на одну позицию
    tank_moving_east->move_forward();

    // Проверяем, что позиция первого танка после первого шага соответствует ожидамой
    CHECK(tank_moving_east->get_location() == expected_second_tank_location_before_error);

    // Проверяем, что при попытке передвинуть второй танк на позицию, где уже находится первый танк, выбрасывается исключение
    CHECK_THROWS_WITH(tank_moving_east->move_forward(), "Перемещение невозможно, точка уже занята другим объектом");

    cout << endl;

    delete tank_moving_north;
    delete tank_moving_east;
}
