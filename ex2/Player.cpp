#include <iostream>
#include "Player.h"
#include "utilities.h" 


Player::Player(const string name, int maxHP, int force)
    : m_name(name),
      m_maxHP((maxHP > 0) ? maxHP : DEFAULT_MAX_HP),
      m_force((force >= 0) ? force : DEFAULT_FORCE),
      m_HP(m_maxHP),
      m_level(DEFAULT_LEVEL),
      m_coins(DEFAULT_COINS) {}


void Player::printInfo() const {
    printPlayerInfo(m_name.c_str(), m_level, m_force, m_HP, m_coins);
}


void Player::levelUp() {
    if (m_level < 10) {
        m_level++;
    }
}


int Player::getLevel() const {
    return m_level;
}


void Player::buff(int amount) {
    
    if(amount > 0) {
        m_force += amount;
    }
}


void Player::heal(int amount) {

    if (amount > 0) {
        // check if adding the amount will exceed the maxHP
        if (m_HP + amount > m_maxHP) {
            m_HP = m_maxHP;

        } else {
            m_HP += amount;
        }
    }
}


void Player::damage(int amount) {
    
    if (amount > 0) {
        // check if the amount is bigger then the current HP
        if (amount > m_HP) {
            m_HP = 0;
        }
        else {
            m_HP -= amount;
        }
    }
}


bool Player::isKnockedOut() const {
    return m_HP == 0;
}


void Player::addCoins(int amount) {
    if (amount > 0) {
        m_coins += amount;
    }
}


bool Player::pay(int amount) {

    if (amount >= 0 && m_coins >= amount ) {
        m_coins -= amount;
        return true;
    } 
    return false;
}


int Player::getAttackStrength() const {
    return m_force + m_level;
}

