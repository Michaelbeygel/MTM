
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>

#include "Mtmchkin.h"
#include "utilities.h"
#include "GameFactory.h"

using std::ifstream;
using std::istringstream;
using std::move;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

Mtmchkin::Mtmchkin(const string &deckPath, const string &playersPath)
{

    // open and read cards and Players file
    m_deck = GameFactory::createDeck(deckPath);
    m_players = GameFactory::createPlayers(playersPath);

    this->m_turnIndex = 1;
}

void Mtmchkin::playTurn(Player &player)
{

    // Calculate the index of the card to draw
    int cardIndex = (m_turnIndex - 1) % m_deck.size();

    const unique_ptr<Card> &currentCard = m_deck[cardIndex];

    // Print turn details
    printTurnDetails(m_turnIndex, player, *currentCard);

    string outcome = currentCard->applyCard(player);

    // Print turn outcome
    printTurnOutcome(outcome);

    m_turnIndex++;
}

// Custom comparison function to sort players based on the rules
static bool comparePlayers(const shared_ptr<Player> &player1, const shared_ptr<Player> &player2)
{

    // Compare by level (higher level first)
    if (player1->getLevel() != player2->getLevel())
    {
        return player1->getLevel() > player2->getLevel();
    }

    // If levels are equal, compare by amount of coins (higher coins first)
    if (player1->getCoins() != player2->getCoins())
    {
        return player1->getCoins() > player2->getCoins();
    }

    // If levels and coins are equal, compare by name (lexicographically)
    return player1->getName() < player2->getName();
}

void Mtmchkin::playRound()
{

    printRoundStart();

    // Iterate over the players and play one turn for each
    for (shared_ptr<Player> &currentPlayer : m_players)
    {
        if (!currentPlayer->isKnockedOut())
        {
            // Play turn for the current player only if he alive
            playTurn(*currentPlayer);
        }
    }

    printRoundEnd();

    // Sort the leaderboard based on the custom comparison function
    std::sort(m_leaderboard.begin(), m_leaderboard.end(), comparePlayers);

    printLeaderBoardMessage();

    // Print leaderboard entry for each player
    int leaderboardSize = m_leaderboard.size();
    for (int i = 0; i < leaderboardSize; i++)
    {
        printLeaderBoardEntry(i + 1, *m_leaderboard[i]);
    }

    printBarrier();
}

bool Mtmchkin::isGameOver() const
{

    // If a player has reached level 10, the game is over
    for (const shared_ptr<Player> &player : m_players)
    {
        if (player->getLevel() == 10)
        {
            return true;
        }
    }

    // If there are no players left alive the game is over
    for (const shared_ptr<Player> &player : m_players)
    {
        if (!player->isKnockedOut())
        {
            return false;
        }
    }
    return true;
}

void Mtmchkin::play()
{

    printStartMessage();

    // Print start message entry for each player using "printStartPlayerEntry
    int index = 1;
    for (const shared_ptr<Player> &player : m_players)
    {
        printStartPlayerEntry(index, *player);
        index++;
    }

    printBarrier();

    for (const shared_ptr<Player> &player : m_players)
    {
        m_leaderboard.push_back(move(player));
    }

    while (!isGameOver())
    {
        playRound();
    }

    printGameOver();

    shared_ptr<Player> leaderPlayer = m_leaderboard.front();

    if (leaderPlayer->getLevel() == 10)
    {
        printWinner(*leaderPlayer);
    }
    else
    {
        printNoWinners();
    }
}
