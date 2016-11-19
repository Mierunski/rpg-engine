#include "Monster.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

Monster::Monster(const char * file, int height, int width) : Unit(file)
{

    std::string temp;
    temp = file;
    temp += ".txt";

    using std::ifstream;
    ifstream fileIn(temp);

    fileIn >> m_level;
    fileIn >> m_HP;
    fileIn >> m_atk;
    fileIn >> m_def;
    fileIn.close();
    m_cHP = m_HP;
    m_exp = m_level * 10 + m_atk * 2 + m_def * 2;

    m_position = sf::Vector2f(height, width);
    m_finalPos = m_position;

    m_armor = (float(m_def)*ARMOR_CONST)/(1+(float(m_def)*ARMOR_CONST));
    m_armor = 1 - m_armor;
    m_display.setPosition(m_position.x * 32,m_position.y * 32);

}

Monster::~Monster()
{
    //dtor
}

Monster::Monster(const Monster & Cpy) : Unit(Cpy)
{

}

int Monster::autoMove(const Map & block, Unit & target, std::vector<Monster> & monsterlist)
{
    char direction;
    sf::Vector2f tPos = target.getPosition();
    int dmg = -1;
    if(m_moving == false)
    {
        // sprawdzenie czy mozna zaatakowac
        if (((m_position.x == tPos.x && (m_position.y - 1 == tPos.y || m_position.y + 1 == tPos.y)) ||  (m_position.y == tPos.y && (m_position.x - 1 == tPos.x || m_position.x + 1 == tPos.x))) && m_moving == false)
        {
            dmg = attack(target);
            m_moving = true;
            m_direction = 'N';
            m_display.stop();
        } else if (m_moving == false)// jezeli nie to wykonanie ruchu
        {
            if (m_position.x - tPos.x < ATTACK_RANGE && m_position.x - tPos.x > -ATTACK_RANGE && m_position.y - tPos.y < ATTACK_RANGE && m_position.y - tPos.y > -ATTACK_RANGE)
            {
                if (m_position.x - tPos.x < ATTACK_RANGE && m_position.x - tPos.x > 0 && !block.collision(m_position.x - 1, m_position.y))
                    direction = 'L';
                else if (m_position.x - tPos.x > -ATTACK_RANGE && m_position.x - tPos.x < 0 && !block.collision(m_position.x + 1, m_position.y))
                    direction = 'R';
                else if (m_position.y - tPos.y < ATTACK_RANGE && m_position.y - tPos.y > 0 && !block.collision(m_position.x, m_position.y - 1))
                    direction = 'U';
                else if (m_position.y - tPos.y > -ATTACK_RANGE && m_position.y - tPos.y < 0 && !block.collision(m_position.x, m_position.y + 1))
                    direction = 'D';
            }
            else
            {
                int i = rand()%4;
                char temp[5] = "LRUD";
                direction = temp[i];
            }


            m_moving = true;
            switch (direction)
            {
            case 'D': // down
                if (!block.collision(m_position.x, m_position.y + 1))
                {
                    m_finalPos = sf::Vector2f(m_position.x, m_position.y + 1);
                    m_display.play(m_walking[0]);
                }
                else
                    m_moving = false;
                break;
            case 'L': // left
                if (!block.collision(m_position.x - 1, m_position.y))
                {
                    m_finalPos = sf::Vector2f(m_position.x - 1, m_position.y);
                    m_display.play(m_walking[1]);
                }
                else
                    m_moving = false;
                break;
            case 'R': // right
                if (!block.collision(m_position.x + 1, m_position.y))
                {
                    m_finalPos = sf::Vector2f(m_position.x + 1, m_position.y);
                    m_display.play(m_walking[2]);
                }
                else
                    m_moving = false;
                break;
            case 'U': // up
                if (!block.collision(m_position.x, m_position.y - 1))
                {
                    m_finalPos = sf::Vector2f(m_position.x, m_position.y - 1);
                    m_display.play(m_walking[3]);
                }
                else
                    m_moving = false;
                break;
            }

            m_direction = direction;

            for (int i = 0; i < monsterlist.size(); i++)
            {
                if (m_finalPos == monsterlist[i].getPosition())
                {
                    // atak
                    m_direction = 'N';
                    m_finalPos = m_position;
                    m_display.stop();

                }
            }



        }
    }
    return dmg;
}





Monster & Monster::operator=(const Monster & kopia)
{
    Unit::operator=(kopia);

    return *this;
}

void Monster::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(m_display);
    target.draw(m_HPBar);
}

sf::Vector2f Monster::getPosition()
{
    return m_position;
    m_display.setPosition(m_position.x*32, m_position.y*32);
}

bool Monster::update()
{
    if (m_moving)
    {
        switch (m_direction)
        {
        case 'D': // down
            m_HPBar.move(0, 1);
            break;
        case 'L': // left
            m_HPBar.move(-1, 0);
            break;
        case 'R': // right
            m_HPBar.move(1, 0);
            break;
        case 'U': // up
            m_HPBar.move(0, -1);
            break;
        case 'N':
            break;
        }
    }
    return Unit::update();
}

