#ifndef UNIT_H
#define UNIT_H
#include "AnimatedSprite.hpp"
#include "SFML/Graphics.hpp"
#include "CombatText.h"


class Unit
{
    public:
        Unit(const char * name);
        virtual ~Unit();
        Unit(const Unit & Cpy);
        Unit & operator=(const Unit & Cpy);
        int move(char direction);
        bool update();
        const sf::Vector2f & getPosition() const;
        int attack(Unit & target);
        bool isAlive() const;
        int giveExp() const;
        void setPosition(sf::Vector2f);
    protected:
        const double ARMOR_CONST = 0.03;
        char m_direction;
        bool m_moving;
        int m_level, m_cHP, m_HP, m_atk, m_def, m_exp;
        float m_armor;
        sf::Vector2f m_position, m_finalPos;
        AnimatedSprite m_display;
        sf::Sprite m_HPBar;
        sf::Image m_HPBarImage;
        sf::Texture m_HPBarTexture;
        Animation m_walking[4];
    private:
        int m_counter;
        sf::Texture m_texture;
        sf::Image m_image;
        std::string m_name;
        std::string m_textureName;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // UNIT_H
