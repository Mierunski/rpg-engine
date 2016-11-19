#ifndef MONSTER_H
#define MONSTER_H
#include "AnimatedSprite.hpp"
#include <string>
#include "Map.h"
#include "Unit.h"

class Monster : public Unit, public sf::Drawable
{
    public:
        Monster(const char * file, int height = 15, int width = 15);
        Monster(const Monster & Cpy);
        ~Monster();
        int autoMove(const Map & block, Unit & target, std::vector<Monster> & monsterlist);
        Monster & operator=(const Monster & kopia);
        sf::Vector2f getPosition();
        bool update();
    protected:
    private:
        const int ATTACK_RANGE = 5;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // MONSTER_H
