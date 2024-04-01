#include "Job.h"
#include "Player.h"
using std::unique_ptr;

// Implement virtual functions of Job class

int Job::getCombatPower(const Player &player) const
{
    // Default implementation for generic job (not warrior)
    return player.getForce() + player.getLevel();
}

int Job::applySolarEclipse(Player &player) const
{
    // Default implementation for job that is not Sorcerer
    if (player.getForce() == 0)
    {
        return 0;
    }
    player.forceDown();
    return -1;
}

// Implement virtual functions of Warrior class

int Warrior::getCombatPower(const Player &player) const
{
    // Combat power calculation specific to Warrior
    return 2 * player.getForce() + player.getLevel();
}

std::string Warrior::getName() const
{
    return "Warrior";
}

// Implement virtual functions of Sorcerer class

std::string Sorcerer::getName() const
{
    return "Sorcerer";
}

int Sorcerer::applySolarEclipse(Player &player) const
{
    // Solar eclipse specific to Sorcerer
    player.buff(1);
    return 1;
}
