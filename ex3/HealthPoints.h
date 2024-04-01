#ifndef EX3_HealthPoints_H
#define EX3_HealthPoints_H

#include <iostream>

class HealthPoints
{
private:
    int m_HP;
    int m_maxHP;
    friend bool operator==(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2);
    friend bool operator<(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2);
    friend std::ostream &operator<<(std::ostream &os, const HealthPoints &healthPoints);

public:
    class InvalidArgument
    {
    };
    /*
     * C'tor of HealthPoints class
     *
     * @param m_maxHP - The maxHP of the object.
     * @return
     *      A new instance of HealthPoints.
     */
    HealthPoints(int m_maxHP = 100);

    HealthPoints(const HealthPoints &) = default; // defult copy cinstructor.

    HealthPoints &operator=(const HealthPoints &other) = default; // defult operator.

    HealthPoints &operator+=(int hp); // += operator.

    HealthPoints &operator-=(int hp); // -= operator.
};

HealthPoints operator+(const HealthPoints &other, int hp); // + operator between HealthPoint instance and int.

HealthPoints operator+(int hp, const HealthPoints &other); // + operator between int and HealthPoint instance.

HealthPoints operator-(const HealthPoints &other, int hp); // - operator between HealthPoint instance and int.

HealthPoints operator-(int hp, const HealthPoints &other); // - operator between int and HealthPoint instance.

bool operator>(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2);

bool operator<=(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2);

bool operator>=(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2);

bool operator!=(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2);

#endif // EX3_HealthPoints_H