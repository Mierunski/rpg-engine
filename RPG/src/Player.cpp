#include "Player.h"
#include <iostream>
#include <string>
#include <cstring>


Player::Player(const char * texture) : Unit(texture)
{
    m_atk = 10;
    m_cHP = 150;
    m_level = 1;
    m_def = 10;
    m_exp = 0;
    m_HP = 150;
    m_wiek = 0;
    m_nextLvl = 100;
    m_position = sf::Vector2f(12, 10);
    m_moving = false;
    m_display.setPosition(m_position.x * 32,m_position.y * 32);


    m_armor = (float(m_def)*ARMOR_CONST)/(1+(float(m_def)*ARMOR_CONST));
    m_armor = 1 - m_armor;

    m_finalPos = m_position;

    m_HPBarImage.create(150, 10, sf::Color::Red);
    m_HPBarTexture.loadFromImage(m_HPBarImage);
    m_HPBar.setTexture(m_HPBarTexture, true);
    m_HPBar.setPosition(800, 50);

    m_ExpBarImage.create(150, 10, sf::Color::Yellow);
    m_ExpBarTexture.loadFromImage(m_ExpBarImage);
    m_ExpBar.setTexture(m_ExpBarTexture, true);
    m_ExpBar.setPosition(800, 100);
    m_ExpBar.setScale(0.0, 1.0);

    m_font.loadFromFile("arial.ttf");

    char tempC[4];
    sprintf(tempC, "%d", m_level);
    std::string temp = "Poziom ";
    temp += tempC;
    m_nameText.setString(temp);
    m_nameText.setPosition(810, 5);
    m_nameText.setFont(m_font);
    m_nameText.setCharacterSize(20);

    temp = "Zycie";
    m_HPText.setString(temp);
    m_HPText.setPosition(810, 30);
    m_HPText.setFont(m_font);
    m_HPText.setCharacterSize(15);
    temp = "Doswiadczenie";
    m_expText.setString(temp);
    m_expText.setPosition(810, 80);
    m_expText.setFont(m_font);
    m_expText.setCharacterSize(15);

    sprintf(tempC, "%d", m_atk);
    temp = "Atak: ";
    temp += tempC;
    m_attText.setString(temp);
    m_attText.setPosition(810, 110);
    m_attText.setFont(m_font);
    m_attText.setCharacterSize(15);

    sprintf(tempC, "%d", m_def);
    temp = "Obrona: ";
    temp += tempC;
    m_defText.setString(temp);
    m_defText.setPosition(810, 135);
    m_defText.setFont(m_font);
    m_defText.setCharacterSize(15);

    temp = "Muzyka on/off - 'M'";
    m_muteText.setString(temp);
    m_muteText.setPosition(810, 500);
    m_muteText.setFont(m_font);
    m_muteText.setCharacterSize(15);

}

Player::~Player()
{
    //dtor
}

int Player::move(char direction, const Map & block, std::vector<Monster> & monsterlist)
{
    int dmg = -1;


    if(m_moving == false)
    {
        m_moving = true;
        switch (direction)
        {
        case 'D': // down
            if (!block.collision(m_position.x, m_position.y + 1))
            {
                m_finalPos = sf::Vector2f(m_position.x, m_position.y + 1);
                m_display.play(m_walking[0]);
            } else
                m_moving = false;
            break;
        case 'L': // left
            if (!block.collision(m_position.x - 1, m_position.y))
            {
                m_finalPos = sf::Vector2f(m_position.x - 1, m_position.y);
                m_display.play(m_walking[1]);
            } else
                m_moving = false;
            break;
        case 'R': // right
            if (!block.collision(m_position.x + 1, m_position.y))
            {
                m_finalPos = sf::Vector2f(m_position.x + 1, m_position.y);
                m_display.play(m_walking[2]);
            } else
                m_moving = false;
            break;
        case 'U': // up
            if (!block.collision(m_position.x, m_position.y - 1))
            {
                m_finalPos = sf::Vector2f(m_position.x, m_position.y - 1);
                m_display.play(m_walking[3]);
            } else
                m_moving = false;
            break;
        }
        m_direction = direction;
        // sprawdzenie czy nie wejdzie na potwora
        for (int i = 0; i < monsterlist.size(); i++)
        {
            if (m_finalPos == monsterlist[i].getPosition())
            {
                // atak
                m_direction = 'N';
                m_finalPos = m_position;
                m_display.stop();
                dmg = attack(monsterlist[i]);
            }
        }

        m_position = m_finalPos;

    }
    return dmg;
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(m_display);
    target.draw(m_HPBar);
    target.draw(m_ExpBar);
    target.draw(m_nameText);
    target.draw(m_HPText);
    target.draw(m_expText);
    target.draw(m_attText);
    target.draw(m_defText);
    target.draw(m_muteText);
    //std::cout << m_cHP << "/" << m_HP << "\n";
}

const sf::Vector2f & Player::getPosition() const
{
    return m_position;
}

void Player::addExp(int exp)
{
    m_exp += exp;
    if (m_exp > m_nextLvl)
    {
        int statPoziom = 3;
        m_level++;
        m_HP += 5*statPoziom;
        m_cHP = m_HP;
        m_atk += statPoziom;
        m_def += statPoziom;
        m_exp = m_exp - m_nextLvl;
        m_nextLvl *=2;

        char tempC[4];
        std::string temp;
        sprintf(tempC, "%d", m_def);
        temp = "Obrona: ";
        temp += tempC;
        m_defText.setString(temp);
        sprintf(tempC, "%d", m_atk);
        temp = "Atak: ";
        temp += tempC;
        m_attText.setString(temp);
        sprintf(tempC, "%d", m_level);
        temp = "Poziom ";
        temp += tempC;
        m_nameText.setString(temp);


    }
    m_ExpBar.setScale(float(m_exp)/float(m_nextLvl), 1.0f);
}
