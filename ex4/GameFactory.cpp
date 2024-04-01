#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "GameFactory.h"
#include "Cards/Event.h"
#include "Cards/Encounter.h"
#include "Cards/Monster.h"
#include "Cards/Gang.h"

using std::ifstream;
using std::istringstream;
using std::move;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;

static bool isNameValid(const string &name)
{
    // Check for valid length of name
    if (name.length() < 3 || name.length() > 15)
    {
        return false;
    }

    // Check that all characters are English letters
    for (char c : name)
    {
        if (!isalpha(c))
        {
            return false;
        }
    }
    return true;
}

static bool isJobValid(const string &job)
{
    return job == "Warrior" || job == "Sorcerer";
}

static bool isBehaviorValid(const string &behavior)
{
    return behavior == "Responsible" || behavior == "RiskTaking";
}

static bool isDigit(char c)
{
    return std::isdigit(c);
}

static bool isValidGangSize(const string &str)
{
    return !str.empty() &&
           std::all_of(str.begin(), str.end(), isDigit) &&
           std::stoi(str) >= 2;
}

static void readInnerGang(vector<string> &tokens, vector<string>::iterator &it, Gang &outerGang)
{
    if (it == tokens.end() || !isValidGangSize(*it))
    {
        throw std::runtime_error("Invalid Cards File");
    }

    int gangSize = std::stoi(*it);

    for (int i = 0; i < gangSize; ++i)
    {
        it++;
        if (it == tokens.end())
        {
            throw std::runtime_error("Invalid Cards File");
        }

        if (*it == "Gang")
        {
            unique_ptr<Gang> innerGang(new Gang());
            readInnerGang(tokens, ++it, *innerGang);
            outerGang.addMonster(move(innerGang));
        }
        else
        {
            if (*it == "Goblin")
            {
                outerGang.addMonster(move(unique_ptr<Goblin>(new Goblin())));
            }
            else if (*it == "Giant")
            {
                outerGang.addMonster(move(unique_ptr<Giant>(new Giant())));
            }
            else if (*it == "Dragon")
            {
                outerGang.addMonster(move(unique_ptr<Dragon>(new Dragon())));
            }
            else
            {
                throw std::runtime_error("Invalid Cards File");
            }
        }
    }
}

vector<unique_ptr<Card>> GameFactory::createDeck(const string &deckPath)
{
    vector<unique_ptr<Card>> deck;

    ifstream cardsFile(deckPath);
    if (!cardsFile.is_open())
    {
        throw std::runtime_error("Invalid Cards File");
    }

    vector<string> tokens;
    string word;
    while (cardsFile >> word)
    {
        tokens.push_back(word);
    }

    cardsFile.close();

    vector<string>::iterator it = tokens.begin();
    while (it != tokens.end())
    {
        if (*it == "Gang")
        {
            unique_ptr<Gang> outerGang(new Gang());
            readInnerGang(tokens, ++it, *outerGang);
            deck.push_back(unique_ptr<Card>(new Encounter(move(outerGang))));
        }
        else
        {
            if (*it == "Goblin")
            {
                deck.push_back(unique_ptr<Card>(new Encounter(unique_ptr<Goblin>(new Goblin()))));
            }
            else if (*it == "Giant")
            {
                deck.push_back(unique_ptr<Card>(new Encounter(unique_ptr<Giant>(new Giant()))));
            }
            else if (*it == "Dragon")
            {
                deck.push_back(unique_ptr<Card>(new Encounter(unique_ptr<Dragon>(new Dragon()))));
            }
            else if (*it == "SolarEclipse")
            {
                deck.push_back(unique_ptr<Card>(new SolarEclipse()));
            }
            else if (*it == "PotionsMerchant")
            {
                deck.push_back(unique_ptr<Card>(new PotionsMerchant()));
            }
            else
            {
                throw std::runtime_error("Invalid Cards File");
            }
        }
        ++it;
    }

    if (deck.size() < 2)
    {
        throw std::runtime_error("Invalid Cards File");
    }

    return deck;
}

vector<shared_ptr<Player>> GameFactory::createPlayers(const string &playersPath)
{
    ifstream playersFile(playersPath);

    if (!playersFile.is_open())
    {
        throw std::runtime_error("Invalid Players File");
    }

    vector<shared_ptr<Player>> players;

    string line;
    while (std::getline(playersFile, line))
    {
        istringstream issLine(line);
        string name, job, behavior;
        if (!(issLine >> name >> job >> behavior) || !(isNameValid(name)) || !(isBehaviorValid(behavior)) || !(isJobValid(job)))
        {
            throw std::runtime_error("Invalid Players File");
        }

        shared_ptr<Player> player(new Player(name, nullptr, nullptr));

        // Create Job and Behavior objects
        if (job == "Warrior")
        {
            player->setJob(unique_ptr<Job>(new Warrior()));
        }
        else if (job == "Sorcerer")
        {
            player->setJob(unique_ptr<Job>(new Sorcerer()));
        }

        if (behavior == "Responsible")
        {
            player->setBehavior(unique_ptr<Behavior>(new Responsible()));
        }
        else if (behavior == "RiskTaking")
        {
            player->setBehavior(unique_ptr<Behavior>(new RiskTaking()));
        }

        // Add the Player object to the vector of shared_ptr
        players.push_back(move(player));
    }

    playersFile.close();

    // Check for the minimum and maximum number of players
    if (players.size() < 2 || players.size() > 6)
    {
        throw std::runtime_error("Invalid Players File");
    }

    return players;
}