#pragma once

#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

class Player;

class Job
{
public:
    virtual int getCombatPower(const Player &player) const;
    virtual string getName() const = 0;
    virtual int applySolarEclipse(Player &player) const;
    virtual unique_ptr<Job> clone() const = 0;
    virtual ~Job() = default;
};

class Warrior : public Job
{
public:
    Warrior() = default;
    Warrior(const Warrior &other) = default;
    Warrior &operator=(const Warrior &other) = default;

    int getCombatPower(const Player &player) const override;
    string getName() const override;

    ~Warrior() override = default;
};

class Sorcerer : public Job
{
public:
    Sorcerer() = default;
    Sorcerer(const Sorcerer &other) = default;
    Sorcerer &operator=(const Sorcerer &other) = default;
    ~Sorcerer() override = default;

    string getName() const override;
    int applySolarEclipse(Player &player) const override;
};