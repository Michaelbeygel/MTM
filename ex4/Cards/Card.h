
#pragma once

#include "../Players/Player.h"

class Card
{
public:
    /**
     * Gets the description of the card
     *
     * @return - the description of the card
     */
    virtual string getDescription() const = 0;

    virtual string applyCard(Player &player) const = 0;

    virtual ~Card() = default;
};
