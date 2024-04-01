#include "Card.h"

Card::Card(CardType type, const CardStats& stats)
    : m_effect(type),
      m_stats(stats) {}


void Card::applyEncounter(Player& player) const {

    // Case 1: The card is a battle card
    if (m_effect == CardType::Battle) {

        bool resultOfBattle = true;
        if (player.getAttackStrength() >= m_stats.force) {
            // The player wins the battle
            player.levelUp();
            player.addCoins(m_stats.loot);
        } else {
            player.damage(m_stats.hpLossOnDefeat);
            // Update the result of battle to false
            resultOfBattle = false;
        }
        printBattleResult(resultOfBattle);
    }

    // Case 2: The card is a buff card
    else if (m_effect == CardType::Buff) {

        if (player.pay(m_stats.cost)) {
            // The player has enough coins to buy the buff
            player.buff(m_stats.buff);
        }
    }

    // Case 3: The card is a heal card
    else if (m_effect == CardType::Heal) {

        if (player.pay(m_stats.cost)) {
            // The player has enough coins to buy the heal
            player.heal(m_stats.heal);
        }
    }

    // Case 4: The card is a treasure card
    else {
        // Add coins as the loot number on the card
        player.addCoins(m_stats.loot);
    }
}


void Card::printInfo() const {

     // Check the type of card and call the matching print function
    if (m_effect == CardType::Battle) {
        printBattleCardInfo(m_stats);

    } else if (m_effect == CardType::Buff) {
        printBuffCardInfo(m_stats);

    } else if (m_effect == CardType::Heal) {
        printHealCardInfo(m_stats);

    } else if (m_effect == CardType::Treasure) {
        printTreasureCardInfo(m_stats);
    }
}

