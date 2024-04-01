#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string;

class Player {

public:
    
    /*
     * C'tor of Player class
     * 
     * @param name The name of the player.
     * @param maxHP The maximum HP of the player.
     * @param force The force of the player.
     * @return
     *      A new instance of Player.
     */
    Player(const string name, int maxHP = DEFAULT_MAX_HP, int force = DEFAULT_FORCE);


    /*
     * Here we are explicitly telling the compiler to use the default methods
    */
    ~Player() = default;
    Player(const Player&) = default;
    Player& operator=(const Player& other) = default;


     /*
     * Prints information about the player.
     */
    void printInfo() const;


    /*
     * Increases the player's level.
     */
    void levelUp();


     /*
     * Gets the player's level.
     * 
     * @return 
     *      int - The player's level.
     */
    int getLevel() const;


    /*
     * Increases the player's force.
     * 
     * @param amount The amount to increase the force by.
     */
    void buff(int amount);


    /*
     * Heals the player by a certain amount.
     * 
     * @param amount - The amount to heal the player.
     */
    void heal(int amount);


    /*
     * Damages the player's force by a certain amount.
     * 
     * @param amount The amount to damage the player.
     */
    void damage(int amount);


     /*
     * Checks if the player ran out of HP.
     * 
     * @return 
     *      bool - True if knocked out, false otherwise.
     */
    bool isKnockedOut() const;


    /*
     * Pays a certain amount of coins.
     * 
     * @param amount The amount of coins to pay.
     * @return 
     *      bool - True if payment successful, false otherwise.
     */
    void addCoins(int amount);


     /*
     * Pays a certain amount of coins.
     * 
     * @param amount The amount of coins to pay.
     * @return 
     *      bool - True if payment successful, false otherwise.
     */
    bool pay(int amount);


     /**
     * Gets the player's attack strength - force + level.
     * 
     * @return 
     *      int - The player's attack strength.
     */
    int getAttackStrength() const;


private:

    string m_name;
    int m_maxHP;
    int m_force;
    int m_HP;
    int m_level;
    int m_coins;

    // default values 
    static const int DEFAULT_MAX_HP = 100;
    static const int DEFAULT_FORCE = 5;
    static const int DEFAULT_LEVEL = 1;
    static const int DEFAULT_COINS = 0;

};

#endif // PLAYER_H
