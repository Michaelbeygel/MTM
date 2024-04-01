#include "Player.h"

using std::string;

Player::Player(const string name, unique_ptr<Job> job, unique_ptr<Behavior> behavior)
    : m_name(name),
      m_level(DEFAULT_LEVEL),
      m_force(DEFAULT_FORCE),
      m_hp(MAX_HP),
      m_coins(DEFAULT_COINS),
      m_job(std::move(job)),
      m_behavior(std::move(behavior)) {}

Player::Player(const Player &other)
    : m_name(other.m_name),
      m_level(other.m_level),
      m_force(other.m_force),
      m_hp(other.m_hp),
      m_coins(other.m_coins),
      m_job(other.m_job ? other.m_job->clone() : nullptr),
      m_behavior(other.m_behavior ? other.m_behavior->clone() : nullptr) {}

Player &Player::operator=(const Player &other)
{
    if (this != &other)
    {
        m_name = other.m_name;
        m_level = other.m_level;
        m_hp = other.m_hp;
        m_coins = other.m_coins;
        m_force = other.m_force;

        m_job = other.m_job ? other.m_job->clone() : nullptr;
        m_behavior = other.m_behavior ? other.m_behavior->clone() : nullptr;
    }
    return *this;
}

void Player::setJob(unique_ptr<Job> job)
{
    m_job = std::move(job);
}

void Player::setBehavior(unique_ptr<Behavior> behavior)
{
    m_behavior = std::move(behavior);
}

// void Player::setJob(Job* job) {
//     m_job.reset(job);
// }

string Player::getDescription() const
{
    return m_name + ", " + m_job->getName() + " with " + m_behavior->getName() +
           " behavior (level " + std::to_string(m_level) + ", force " +
           std::to_string(m_force) + ")";
}

string Player::getName() const
{
    return m_name;
}

int Player::getLevel() const
{
    return m_level;
}

int Player::getForce() const
{
    return m_force;
}

int Player::getHealthPoints() const
{
    return m_hp;
}

int Player::getCoins() const
{
    return m_coins;
}

int Player::getCombatPower() const
{
    return m_job->getCombatPower(*this);
}

const Job *Player::getJob() const
{
    return m_job.get();
}

const Behavior *Player::getBehavior() const
{
    return m_behavior.get();
}
//////////////////////////

void Player::levelUp()
{
    if (m_level < 10)
    {
        m_level++;
    }
}

void Player::buff(int amount)
{

    if (amount > 0)
    {
        m_force += amount;
    }
}

void Player::forceDown()
{
    if (m_force > 0)
    {
        m_force -= 1;
    }
}

void Player::heal(int amount)
{

    if (amount > 0)
    {
        // check if adding the amount will exceed the maxHP
        if (m_hp + amount > MAX_HP)
        {
            m_hp = MAX_HP;
        }
        else
        {
            m_hp += amount;
        }
    }
}

void Player::damage(int amount)
{

    if (amount > 0)
    {
        // check if the amount is bigger then the current HP
        if (amount > m_hp)
        {
            m_hp = 0;
        }
        else
        {
            m_hp -= amount;
        }
    }
}

bool Player::isKnockedOut() const
{
    return m_hp == 0;
}

void Player::addCoins(int amount)
{
    if (amount > 0)
    {
        m_coins += amount;
    }
}

bool Player::pay(int amount)
{

    if (amount >= 0 && m_coins >= amount)
    {
        m_coins -= amount;
        return true;
    }
    return false;
}

bool Player::isMaxHP() const
{
    return m_hp == MAX_HP;
}