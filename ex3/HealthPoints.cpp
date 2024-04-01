#include "HealthPoints.h"
#include <stdexcept>
#include <iostream>

// Constructor
HealthPoints::HealthPoints(int maxHP) : m_HP(maxHP), m_maxHP(maxHP)
{
    if (maxHP <= 0)
    {
        throw InvalidArgument();
    }
}

HealthPoints &HealthPoints::operator+=(int hp) // += operator.
{

    if (m_HP + hp > m_maxHP)
    {
        m_HP = m_maxHP;
    }
    else if (m_HP + hp < 0)
    {
        m_HP = 0;
    }
    else
    {
        m_HP += hp;
    }

    return *this;
}

HealthPoints &HealthPoints::operator-=(int hp) // += operator.
{
    return *this += -hp;
}

HealthPoints operator+(const HealthPoints &other, int hp)
{
    HealthPoints temp = other;
    return temp += hp;
}

HealthPoints operator+(int hp, const HealthPoints &other)
{
    HealthPoints temp = other;
    return temp += hp;
}

HealthPoints operator-(const HealthPoints &other, int hp)
{
    HealthPoints temp = other;
    return temp -= hp;
}

HealthPoints operator-(int hp, const HealthPoints &other)
{
    HealthPoints temp = other;
    return temp -= hp;
}

// implement using other operators
bool operator==(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2)
{
    return healthPoints1.m_HP == healthPoints2.m_HP;
}
// implement by yourself
bool operator<(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2)
{
    return healthPoints1.m_HP < healthPoints2.m_HP;
}

bool operator>(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2)
{
    return healthPoints2 < healthPoints1;
}

bool operator<=(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2)
{
    return !(healthPoints1 > healthPoints2);
}

bool operator>=(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2)
{
    return !(healthPoints1 < healthPoints2);
}

bool operator!=(const HealthPoints &healthPoints1, const HealthPoints &healthPoints2)
{
    return !(healthPoints1 == healthPoints2);
}

std::ostream &operator<<(std::ostream &os, const HealthPoints &healthPoints)
{
    return os << healthPoints.m_HP << "(" << healthPoints.m_maxHP << ")";
}