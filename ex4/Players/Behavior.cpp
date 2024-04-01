#include "Behavior.h"
#include "Player.h"
using std::unique_ptr;

int Responsible::applyPotionsMerchant(Player &player) const
{
    // Calculate maximum number of potions based on available gold coins
    int maxPotions = player.getCoins() / POTION_COST;
    int remainingHealthPoints = MAX_HEALTH_POINTS - player.getHealthPoints();
    int maxPotionsToBuy = std::min(maxPotions, remainingHealthPoints / POTION_HEALTH_INCREASE);

    if (maxPotionsToBuy > 0)
    {
        // Buy potions
        player.heal(maxPotionsToBuy * POTION_HEALTH_INCREASE);
        player.pay(maxPotionsToBuy * POTION_COST);
        return maxPotionsToBuy;
    }
    return 0;
}

int RiskTaking::applyPotionsMerchant(Player &player) const
{
    if (player.getHealthPoints() < MAX_HEALTH_POINTS / 2)
    {
        // Buy one potion if the player's health is under 50
        if (player.getCoins() >= POTION_COST)
        {
            player.heal(POTION_HEALTH_INCREASE);
            player.pay(POTION_COST);
            return 1;
        }
    }
    return 0;
}
