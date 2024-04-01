
#pragma once

#include <string>
#include <memory>

class Player;

using std::string;
using std::unique_ptr;

class Behavior
{
public:
    virtual int applyPotionsMerchant(Player &player) const = 0;

    virtual string getName() const = 0;

    virtual unique_ptr<Behavior> clone() const = 0;

    virtual ~Behavior() = default;

protected:
    static const int POTION_COST = 5;
    static const int POTION_HEALTH_INCREASE = 10;
    static const int MAX_HEALTH_POINTS = 100;
};

class Responsible : public Behavior
{
public:
    ~Responsible() override = default;

    int applyPotionsMerchant(Player &player) const override;

    string getName() const override
    {
        return "Responsible";
    }
};

class RiskTaking : public Behavior
{
public:
    ~RiskTaking() override = default;

    int applyPotionsMerchant(Player &player) const override;

    string getName() const override
    {
        return "RiskTaking";
    }
};