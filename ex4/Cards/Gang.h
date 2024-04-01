#include "Monster.h"
#include <vector>
#include <memory>

using std::move;
using std::unique_ptr;

using std::vector;
class Gang : public Monster
{
private:
    vector<unique_ptr<Monster>> m_gang; // at least 2 monstars

public:
    ~Gang() override = default;

    Gang() : Monster(0, 0, 0), m_gang(){};

    string getName() const override
    {
        return "Gang of " + std::to_string(m_gang.size()) + " members";
    }

    void addMonster(unique_ptr<Monster> monster)
    {
        m_loot += monster->getLoot();
        m_damage += monster->getDamage();
        m_combatPower += monster->getCombatPower();
        m_gang.push_back(std::move(monster));
    }
};