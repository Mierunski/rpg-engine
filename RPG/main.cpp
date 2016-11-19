#include <iostream>
#include "include/Map.h"
#include "include/MapSprites.h"
#include "Monster.h"
#include "Player.h"
#include "CombatText.h"
#include <ctime>
#include <vector>
#include <cstring>
#include <fstream>
#include <SFML/Audio/Music.hpp>

using namespace std;

struct nameCords
{
    char name[30];
    int x, y;
};

int main()
{

    srand(time(0));

    // stworzenie i ustawienie okna

    sf::RenderWindow window(sf::VideoMode(950, 640), "Sashir RPG");
    window.setFramerateLimit(60);

    // muzyka
    sf::Music music;
    if (!music.openFromFile("soundtrack/s1.ogg"))
        return -1; // error



    bool gameStop = false, win = false;

    //wczytanie listy map
    ifstream filein("maplist.txt");
    int numberOfMaps;
    filein >> numberOfMaps;
    char ** mapList = new char * [numberOfMaps];
    int ** mapExits = new int * [numberOfMaps];
    nameCords ** monsterList = new nameCords * [numberOfMaps];
    for (int i = 0; i < numberOfMaps; i++)
    {
        filein.get();
        mapList[i] = new char [20];
        filein.getline(mapList[i], 20);
        mapExits[i] = new int [5];
        filein >> mapExits[i][0] >> mapExits[i][1] >> mapExits[i][2] >> mapExits[i][3] >> mapExits[i][4];
        monsterList[i] = new nameCords[mapExits[i][4]];

        for (int j = 0; j < mapExits[i][4]; j++)
        {
            filein.get();
            filein.getline(monsterList[i][j].name, 30);
            filein >> monsterList[i][j].x >> monsterList[i][j].y;
        }
    }

    int currentMap = 0;
    sf::Vector2f currentExit, currentEntry;





    //wczytanie spriteow
    MapSprites maps("sprites.txt", "maps.png");
    MapSprites objects("objects.txt", "objects.png");
    objects.mode(true);


    // stworzenie postaci
    Player player("player");

    // ekran powitalny

    sf::Image backImg;
    backImg.loadFromFile("graphics/background.png");
    sf::Texture backText;
    backText.loadFromImage(backImg);
    sf::Sprite background;
    background.setTexture(backText);

    sf::Image frontTextImg;
    frontTextImg.loadFromFile("graphics/fronttext.png");
    sf::Texture frontTextText;
    frontTextText.loadFromImage(frontTextImg);
    sf::Sprite frontText;
    frontText.setTexture(frontTextText);
    frontText.setPosition(40, 250);

    bool roundStop = false;
    float frontTimer = 0;
    bool frontFlag = true;
    music.play();
    while (!roundStop == true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                roundStop = true;
                gameStop = true;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {

                gameStop = true;
                roundStop = true;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            {
                roundStop = true;
            }
        }
        if (frontFlag)
        {
            if (frontTimer < 254) frontTimer += 1.5f;
            else frontFlag = false;
        } else
        {
            if (frontTimer > 1) frontTimer -= 1.5f;
            else frontFlag = true;
        }
        frontText.setColor(sf::Color(255, 255, 255, frontTimer));
        window.clear();
        window.draw(background);
        window.draw(frontText);
        window.display();
    }
    music.stop();


    while(!gameStop == true)
    {

        // wczytanie mapy


        Map mainMap(mapList[currentMap], &maps, &objects);
        currentExit = sf::Vector2f(mapExits[currentMap][0], mapExits[currentMap][1]);
        currentEntry = sf::Vector2f(mapExits[currentMap][2], mapExits[currentMap][3]);

        player.setPosition(currentEntry);
        // Wczytanie potworów

        std::vector<Monster> monsters;
        Monster temp("graphics/snake", 10, 18);
        for (int i = 0; i < mapExits[currentMap][4]; i++)
        {
            temp = Monster(monsterList[currentMap][i].name, monsterList[currentMap][i].x, monsterList[currentMap][i].y);
            monsters.push_back(temp);
        }



        bool turn = false;


        // Wyswietlanie ataków
        std::vector<CombatText> texts;
        int dmg = -1, dmgX, dmgY;
        CombatText damage("none", 0, 0, 0);


        roundStop = false;
        //petla glowna



        music.play();
        while (!roundStop == true)
        {

            // Obsługa Eventów

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    roundStop = true;
                    gameStop = true;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {

                    gameStop = true;
                    roundStop = true;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    turn = true;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
                {
                    if (music.getVolume() == 100)
                        music.setVolume(0);
                    else
                        music.setVolume(100);
                }
            }

            if (!player.isAlive())
            {
                gameStop = true;
                    roundStop = true;
            }


            // Obsługa strzałek
            dmg = -1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && turn == false)
            {
                dmg = player.move('D', mainMap, monsters);
                dmgX = player.getPosition().x;
                dmgY = player.getPosition().y + 1;
                turn = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && turn == false)
            {
                dmg = player.move('L', mainMap, monsters);
                dmgX = player.getPosition().x - 1;
                dmgY = player.getPosition().y;
                turn = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && turn == false)
            {
                dmg = player.move('R', mainMap, monsters);
                dmgX = player.getPosition().x + 1;
                dmgY = player.getPosition().y;
                turn = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && turn == false)
            {
                dmg = player.move('U', mainMap, monsters);
                dmgX = player.getPosition().x;
                dmgY = player.getPosition().y - 1;
                turn = true;
            }

            if (player.getPosition() == currentExit)
            {
                roundStop = true;
            }

            if (sf::SoundSource::Stopped == music.getStatus())
            {
                int songNumber = rand()%13 + 1;
                char tempC[3];
                sprintf(tempC, "%d", songNumber);
                string temp = "soundtrack/s";
                temp += tempC;
                temp += ".ogg";
                music.openFromFile(temp);
                music.play();
            }

            // stworzenie napisu

            if (dmg > -1)
            {
                char temp[20];
                sprintf(temp, "%d", dmg);
                damage.create(temp, dmgX, dmgY, 20, sf::Color::Black);
                texts.push_back(damage);
                //cout << endl << dmg;
            }







            // Ruch potworów

            if (turn == true)
            {
                for (unsigned int i = 0; i < monsters.size(); i++)
                {
                    dmg = monsters[i].autoMove(mainMap, player, monsters);
                    if (dmg > -1)
                    {
                        char temp[20];
                        sprintf(temp, "%d", dmg);
                        damage.create(temp, player.getPosition().x, player.getPosition().y, 20, sf::Color::Red);
                        texts.push_back(damage);
                        //cout << endl << dmg;
                    }
                }


            }



            // Sprawdzenie czy postać żyje
            if (!player.isAlive())
            {
                gameStop = true;
                roundStop = true;
            }

            if (monsters.size() == 0)
                turn = false;


            // Czyszczenie martwych potworów
            for (unsigned int i = 0; i < monsters.size(); i++)
            {
                if (!monsters[i].isAlive())
                {
                    player.addExp(monsters[i].giveExp());
                    //cout << i << endl;
                    monsters.erase(monsters.begin()+i);
                    i--;
                }

            }


            // Czyszczenie okna

            window.clear();


            // rysowanie

            window.draw(mainMap.draw());
            player.update();
            window.draw(player);
            for (unsigned int i = 0; i < monsters.size(); i++)
            {

                if (monsters[i].Monster::update())
                    turn = false;
                window.draw(monsters[i]);


            }

            for (unsigned int i = 0; i < texts.size(); i++)
            {

                window.draw(texts[i]);
                if (texts[i].update())
                {
                    texts.erase(texts.begin()+i);
                    i--;
                }
            }

            // wyswietlanie

            window.display();
        }
        if(currentMap < numberOfMaps - 1) currentMap++;
        else
        {
            gameStop = true;
            roundStop = true;
            win = true;
        }
        music.pause();

    }

    if (win)
    {
        frontTextImg.loadFromFile("graphics/win.png");
    } else
    {
        frontTextImg.loadFromFile("graphics/lose.png");
    }
    roundStop = false;
    frontTextText.loadFromImage(frontTextImg);

    music.play();
    while (!roundStop == true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                roundStop = true;
                gameStop = true;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {

                gameStop = true;
                roundStop = true;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            {
                roundStop = true;
            }
        }
        if (frontFlag)
        {
            if (frontTimer < 254) frontTimer += 1.5f;
            else frontFlag = false;
        } else
        {
            if (frontTimer > 1) frontTimer -= 1.5f;
            else frontFlag = true;
        }
        frontText.setColor(sf::Color(255, 255, 255, frontTimer));
        window.clear();
        window.draw(background);
        window.draw(frontText);
        window.display();
    }
    window.close();
    return 0;
}
