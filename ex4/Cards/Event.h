#pragma once

#include "../utilities.h"
#include "../Players/Job.h"
#include "../Players/Behavior.h"

class Event : public Card
{
public:
    virtual ~Event() override = default;

    virtual string getName() const = 0;

    virtual string getDescription() const = 0;

    virtual string applyCard(Player &player) const = 0;
};

class PotionsMerchant : public Event
{
public:
    ~PotionsMerchant() override = default;

    string getName() const override
    {
        return "PotionsMerchant";
    }

    string applyCard(Player &player) const override
    {
        const Behavior *playerBehavior = player.getBehavior();
        int amount = playerBehavior->applyPotionsMerchant(player);
        return getPotionsPurchaseMessage(player, amount);
    }
    string getDescription() const override
    {
        return "PotionsMerchant";
    }
};

class SolarEclipse : public Event
{
public:
    ~SolarEclipse() override = default;

    string getName() const override
    {
        return "SolarEclipse";
    }
    string applyCard(Player &player) const override
    {
        const Job *playerJob = player.getJob();
        int effect = playerJob->applySolarEclipse(player);
        return getSolarEclipseMessage(player, effect);
    }
    string getDescription() const override
    {
        return "SolarEclipse";
    }
};
