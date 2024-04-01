#pragma once

#include "Monster.h"
#include <memory>
#include "../Players/Player.h"
#include "../utilities.h"

using std::move;
using std::unique_ptr;

class Encounter : public Card
{
private:
    unique_ptr<Monster> m_monster;

public:
    ~Encounter() override = default;

    string getDescription() const override;

    string applyCard(Player &player) const override;

    // constructor
    Encounter(unique_ptr<Monster> monster)
        : m_monster(move(monster)) {}
};

string Encounter::applyCard(Player &player) const
{
    if (player.getCombatPower() > m_monster->getCombatPower())
    {
        player.levelUp();
        player.addCoins(m_monster->getLoot());
        return getEncounterWonMessage(player, m_monster->getLoot());
    }
    else
    {
        player.damage(m_monster->getDamage());
        return getEncounterLostMessage(player, m_monster->getDamage());
    }
}

string Encounter::getDescription() const
{
    return m_monster->getName() + " (power " + std::to_string(m_monster->getCombatPower()) + ", loot " + std::to_string(m_monster->getLoot()) + ", damage " + std::to_string(m_monster->getDamage()) + ")";
}
