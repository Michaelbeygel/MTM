#include "Mtmchkin.h"
#include <cassert>

Mtmchkin::Mtmchkin(const string playerName, const Card* cardsArray, int numOfCards)
    :m_player(Player(playerName)),
     m_cardsArray(copyCardsArray(cardsArray, numOfCards)),
     m_numberOfCards(numOfCards),
     m_status(GameStatus::MidGame),
     m_cardIndex(0) {}


Card* Mtmchkin::copyCardsArray(const Card* cardsArray, int numOfCards) {

    Card* copiedCards = new Card[numOfCards];

    for (int i = 0; i < numOfCards; i++) {
        copiedCards[i] = cardsArray[i];
    }
    return copiedCards;
}

Mtmchkin::~Mtmchkin() {
    delete[] m_cardsArray;
}


Mtmchkin::Mtmchkin(const Mtmchkin& other)
    : m_player(other.m_player), 
      m_cardsArray(copyCardsArray(other.m_cardsArray, other.m_numberOfCards)),
      m_numberOfCards(other.m_numberOfCards),
      m_status(other.m_status),
      m_cardIndex(other.m_cardIndex) {}


Mtmchkin& Mtmchkin::operator=(const Mtmchkin& other) {

    // If it's a self-assignment
    if (this == &other) {
        return *this;
    }

    // create a temporary array to store the copied cards
    Card* temp = copyCardsArray(other.m_cardsArray, m_numberOfCards);

    delete[] m_cardsArray;

    m_cardsArray = temp;

    // Copy data from the other object
    m_player = other.m_player;
    m_numberOfCards = other.m_numberOfCards;
    m_status = other.m_status;
    m_cardIndex = other.m_cardIndex;

    return *this;
}


void Mtmchkin::playNextCard() {

    // Check if the game is over
    if (isOver()) {
        return;
    }

    // Print the info of the current card
    m_cardsArray[m_cardIndex].printInfo();

    // Apply encounter with the current card to the player
    m_cardsArray[m_cardIndex].applyEncounter(m_player);

    // Check if the player has won the game
    if (m_player.getLevel() >= Mtmchkin::GAME_MAX_LEVEL) {
        m_status = GameStatus::Win;
    }
    // Check if the player lost the game
    else if (m_player.isKnockedOut()) {
        m_status = GameStatus::Loss;
    }

    m_player.printInfo();

    // Increment the card index for the next round
    m_cardIndex++;

    // If we have reached the end of the deck, reset to the beginning
    if (m_cardIndex == m_numberOfCards) {
        m_cardIndex = 0;
    }

}


bool Mtmchkin::isOver() const {
    return (m_status == GameStatus::Win || m_status == GameStatus::Loss);
}


GameStatus Mtmchkin::getGameStatus() const {
    return m_status;
}

