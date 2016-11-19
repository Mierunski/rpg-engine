#ifndef COMBATTEXT_H
#define COMBATTEXT_H
#include <SFML/Graphics.hpp>

class CombatText : public sf::Drawable
{
    public:
        CombatText(const char * text, float x, float y, int frames);
        CombatText(const CombatText & Cpy);
        CombatText & operator=(const CombatText & Cpy);
        void create(const char * text, float x, float y, int frames, sf::Color color = sf::Color::Red);
        bool update();
        ~CombatText();
    protected:
    private:
        sf::Text m_text;
        sf::Font m_font;
        int m_frames, m_currentFrame;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};

#endif // COMBATTEXT_H
