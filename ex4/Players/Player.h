
#pragma once

#include <string>
#include <memory>
#include "Job.h"
#include "Behavior.h"

using std::string;
using std::unique_ptr;

class Player
{
public:
    /*
     * C'tor of Player class
     *
     * @param name The name of the player.
     * @param job The job of the player.
     * @param behavior The behavior of the player.
     * @return
     *      A new instance of Player.
     */
    Player(const string name, unique_ptr<Job> job, unique_ptr<Behavior> behavior);

    /*
     * Do not support copy of play
     */
    Player(const Player &other);

    Player &operator=(const Player &other);

    /**
     * Gets the description of the player
     *
     * @return - description of the player
     */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
     */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
     */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
     */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
     */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
     */
    int getCoins() const;

    void setJob(unique_ptr<Job> job);

    void setBehavior(unique_ptr<Behavior> behavior);

    int getCombatPower() const;

    const Job *getJob() const;

    const Behavior *getBehavior() const;

    void levelUp();

    void buff(int amount);

    void forceDown();

    void heal(int amount);

    void damage(int amount);

    bool isKnockedOut() const;

    void addCoins(int amount);

    bool pay(int amount);

    bool isMaxHP() const;

private:
    string m_name;
    int m_level;
    int m_force;
    int m_hp;
    int m_coins;
    unique_ptr<Job> m_job;
    unique_ptr<Behavior> m_behavior;

    // default values
    static const int MAX_HP = 100;
    static const int DEFAULT_FORCE = 5;
    static const int DEFAULT_LEVEL = 1;
    static const int DEFAULT_COINS = 10;
};