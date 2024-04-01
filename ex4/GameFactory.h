#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Cards/Card.h"
#include "Players/Player.h"

using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

class GameFactory
{
public:
    static vector<unique_ptr<Card>> createDeck(const string &deckPath);

    static vector<shared_ptr<Player>> createPlayers(const string &playersPath);
};