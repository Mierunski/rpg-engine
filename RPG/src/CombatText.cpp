#include "CombatText.h"
#include <string>
CombatText::CombatText(const char * text, float x, float y, int frames)
{
    std::string temp;
    m_font.loadFromFile("arial.ttf");
    temp = text;
    m_text.setFont(m_font);
    m_text.setString(temp);

    m_frames = frames;
    m_currentFrame = 0;

    m_text.setPosition(x*32 + 10, y * 32 - 14);

    m_text.setColor(sf::Color::Magenta);

    //ctor
}

CombatText::~CombatText()
{
    //dtor
}

CombatText::CombatText(const CombatText & Cpy)
{
    m_font.loadFromFile("arial.ttf");
    m_text.setFont(m_font);
    m_text.setString(Cpy.m_text.getString());

    m_frames = Cpy.m_frames;
    m_currentFrame = Cpy.m_currentFrame;

    m_text.setPosition(Cpy.m_text.getPosition());

    m_text.setColor(Cpy.m_text.getColor());
}

CombatText & CombatText::operator=(const CombatText & Cpy)
{
    m_font.loadFromFile("arial.ttf");
    m_text.setFont(m_font);
    m_text.setString(Cpy.m_text.getString());

    m_frames = Cpy.m_frames;
    m_currentFrame = Cpy.m_currentFrame;

    m_text.setPosition(Cpy.m_text.getPosition());

    m_text.setColor(Cpy.m_text.getColor());

    return *this;
}


void CombatText::create(const char * text, float x, float y, int frames, sf::Color color)
{
    std::string temp;
    temp = text;
    m_text.setString(temp);

    m_frames = frames;
    m_currentFrame = 0;

    m_text.setPosition(x*32 + 10, y * 32 - 14);

    m_text.setColor(color);
}

bool CombatText::update()
{
    m_currentFrame++;
    m_text.move(0, -0.5);

    if (m_currentFrame >= m_frames)
        return true;
    else
        return false;
}

void CombatText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(m_text);
}
