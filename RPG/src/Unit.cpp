#include "Unit.h"
#include <string>
#include <iostream>
#include <cstring>

Unit::Unit(const char * name)
{
    m_name = name;
    m_textureName = name;
    m_textureName += ".png";
    m_image.loadFromFile(m_textureName);

    if (!m_texture.loadFromImage(m_image))
    {
        std::cout << "Failed to load " << m_textureName << " spritesheet!" << std::endl;
    }

    for (int i = 0; i < 4; i++)
    {
        m_walking[i].setSpriteSheet(m_texture);
        m_walking[i].addFrame(sf::IntRect(32, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect(64, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect(32, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect( 0, i*32, 32, 32));
    }

    m_display = AnimatedSprite(8, true, false);
    m_display.setPosition(m_position.x*32, m_position.y*32);
    m_display.setLooped(true);
    m_display.play(m_walking[0]);
    m_counter = 0;

    m_HPBarImage.create(32, 3, sf::Color::Red);
    m_HPBarTexture.loadFromImage(m_HPBarImage);
    m_HPBar.setTexture(m_HPBarTexture);
    m_HPBar.setPosition(m_position.x*32, m_position.y*32 - 5);
}

Unit::~Unit()
{
    //dtor
}

Unit::Unit(const Unit & Cpy)
{
    m_textureName = Cpy.m_textureName;
    m_direction = Cpy.m_direction;
    m_moving = Cpy.m_moving;
    m_image.loadFromFile(m_textureName);
    m_texture.loadFromImage(m_image);
    m_name = Cpy.m_name;

    m_level = Cpy.m_level;
    m_cHP = Cpy.m_cHP;
    m_HP = Cpy.m_HP;
    m_atk = Cpy.m_atk;
    m_def = Cpy.m_def;
    m_exp = Cpy.m_exp;
    m_position = Cpy.m_position;
    m_finalPos = Cpy.m_finalPos;
    m_counter = 0;
    for (int i = 0; i < 4; i++)
    {
        m_walking[i].setSpriteSheet(m_texture);
        m_walking[i].addFrame(sf::IntRect(32, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect(64, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect(32, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect( 0, i*32, 32, 32));
    }

    m_display = Cpy.m_display;
    switch (m_direction)
        {
        case 'D': // down
            m_display.play(m_walking[0]);
            break;
        case 'L': // left
            m_display.play(m_walking[1]);
            break;
        case 'R': // right
            m_display.play(m_walking[2]);
            break;
        case 'U': // up
            m_display.play(m_walking[3]);
            break;
        case 'N':
            break;
        }
    m_display.stop();

    m_HPBarImage.create(32, 4, sf::Color::Red);
    m_HPBarTexture.loadFromImage(m_HPBarImage);
    m_HPBar.setTexture(m_HPBarTexture);
    m_HPBar.setPosition(m_position.x*32, m_position.y*32 - 5);
}

Unit & Unit::operator=(const Unit & Cpy)
{
    m_textureName = Cpy.m_textureName;
    m_direction = Cpy.m_direction;
    m_moving = Cpy.m_moving;
    m_image.loadFromFile(m_textureName);
    m_texture.loadFromImage(m_image);
    m_name = Cpy.m_name;
    m_textureName = Cpy.m_textureName;
    m_level = Cpy.m_level;
    m_cHP = Cpy.m_cHP;
    m_HP = Cpy.m_HP;
    m_atk = Cpy.m_atk;
    m_def = Cpy.m_def;
    m_exp = Cpy.m_exp;
    m_position = Cpy.m_position;
    m_finalPos = Cpy.m_finalPos;
    m_counter = 0;
    for (int i = 0; i < 4; i++)
    {
        m_walking[i].setSpriteSheet(m_texture);
        m_walking[i].addFrame(sf::IntRect(32, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect(64, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect(32, i*32, 32, 32));
        m_walking[i].addFrame(sf::IntRect( 0, i*32, 32, 32));
    }

    m_display = Cpy.m_display;
    switch (m_direction)
        {
        case 'D': // down
            m_display.play(m_walking[0]);
            break;
        case 'L': // left
            m_display.play(m_walking[1]);
            break;
        case 'R': // right
            m_display.play(m_walking[2]);
            break;
        case 'U': // up
            m_display.play(m_walking[3]);
            break;
        case 'N':
            break;
        }
    m_display.stop();

    m_HPBarImage.create(32, 4, sf::Color::Red);
    m_HPBarTexture.loadFromImage(m_HPBarImage);
    m_HPBar.setTexture(m_HPBarTexture);
    m_HPBar.setPosition(m_position.x*32, m_position.y*32 - 5);

    return *this;
}

const sf::Vector2f & Unit::getPosition() const
{
    return m_position;
}

bool Unit::update()
{
    m_HPBar.setScale(float(m_cHP)/float(m_HP), 1.0f);
    if (m_moving)
    {
        m_display.update(1);

        switch (m_direction)
        {
        case 'D': // down
            m_display.move(0, 1);
            break;
        case 'L': // left
            m_display.move(-1, 0);
            break;
        case 'R': // right
            m_display.move(1, 0);
            break;
        case 'U': // up
            m_display.move(0, -1);
            break;
        case 'N':
            break;
        }
        m_counter++;
        if (m_counter >= 32)
        {
            m_moving = false;
            m_display.stop();
            m_position = m_finalPos;
            m_counter = 0;
            return true;
        }
    }
    return false;
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(m_display);
}

int Unit::attack(Unit & target)
{
    int attChance = rand()%(m_atk+1);
    int dmg = 0;
    float armor = (float(target.m_def)*ARMOR_CONST)/(1+(float(target.m_def)*ARMOR_CONST));
    armor = 1 - armor;


    if (attChance == m_atk)
    {
        dmg = float(attChance)*2*armor;
    } else
    {
        dmg = float(attChance)*armor;
    }
    //std::cout << m_name << "\n" << dmg << "\n" << attChance << "\n" << armor << "\n";
    target.m_cHP -= dmg;

    return dmg;
}

int Unit::giveExp() const
{
    return m_exp;
}

bool Unit::isAlive() const
{
    if (m_cHP > 0)
        return true;
    else
        return false;
}

void Unit::setPosition(sf::Vector2f pos)
{
    m_position = pos;
    m_finalPos = pos;
    m_display.setPosition(pos.x*32, pos.y*32);
    m_display.stop();
    m_moving = false;
    m_counter = 0;
}
