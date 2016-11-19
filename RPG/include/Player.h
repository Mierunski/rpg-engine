#ifndef PLAYER_H
#define PLAYER_H
#include "AnimatedSprite.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "Map.h"
#include <string>
#include <vector>
#include "Unit.h"
#include "Monster.h"

class Player : public Unit, public sf::Drawable
{
    public:
        Player(const char * texture);
        ~Player();
        int move(char direction, const Map & block, std::vector<Monster> & monsterlist);
        //void update();
        const sf::Vector2f & getPosition() const;
        void addExp(int exp);
    private:
        int m_wiek, m_nextLvl;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        // Exp bar

        sf::Sprite m_ExpBar;
        sf::Image m_ExpBarImage;
        sf::Texture m_ExpBarTexture;


        // Hud

        sf::Font m_font;
        sf::Text m_nameText, m_HPText, m_expText, m_attText, m_defText, m_muteText;

};

#endif // PLAYER_H
