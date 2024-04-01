#pragma once

#include <memory>
#include <string>

using std::string;
using std::to_string;
using std::unique_ptr;

class Monster
{
protected:
    int m_loot;
    int m_damage;
    int m_combatPower;

public:
    virtual ~Monster() = default;

    Monster(int loot, int damage, int combatPower) : m_loot(loot), m_damage(damage), m_combatPower(combatPower) {}

    virtual string getName() const = 0;

    int getLoot() const
    {
        return m_loot;
    }
    int getDamage() const
    {
        return m_damage;
    }
    int getCombatPower() const
    {
        return m_combatPower;
    }
};

class Dragon : public Monster
{
private:
    static const int DRAGON_LOOT = 100;
    static const int DRAGON_DAMAGE = 9001;
    static const int DRAGON_COMBAT_POWER = 17;

public:
    ~Dragon() override = default;

    Dragon() : Monster(DRAGON_LOOT, DRAGON_DAMAGE, DRAGON_COMBAT_POWER) {}
    string getName() const override
    {
        return "Dragon";
    }
};

class Goblin : public Monster
{
private:
    static const int GOBLIN_LOOT = 2;
    static const int GOBLIN_DAMAGE = 10;
    static const int GOBLIN_COMBAT_POWER = 5;

public:
    ~Goblin() override = default;

    Goblin() : Monster(GOBLIN_LOOT, GOBLIN_DAMAGE, GOBLIN_COMBAT_POWER) {}
    string getName() const override
    {
        return "Goblin";
    }
};

class Giant : public Monster
{
private:
    static const int GIANT_LOOT = 5;
    static const int GIANT_DAMAGE = 25;
    static const int GIANT_COMBAT_POWER = 12;

public:
    ~Giant() override = default;

    Giant() : Monster(GIANT_LOOT, GIANT_DAMAGE, GIANT_COMBAT_POWER) {}
    string getName() const override
    {
        return "Giant";
    }
};