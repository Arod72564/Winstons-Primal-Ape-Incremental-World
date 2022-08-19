#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "headerFiles.h"
#include "MenuScreen.h"

class GameMenu {
    public:
        MenuScreen* menuPtr;
        sf::Texture centipedeGameTexture;
        sf::Texture dungeonGameTexture;
        sf::Texture ArcheryGameTexture;
        sf::Texture centipedeGameMult_Texture;

        sf::Sprite centipedeGameSprite;
        sf::Sprite dungeonGameSprite;
        sf::Sprite archerygameSprite;
        sf::Sprite centipedeGameMult_Sprite;

        sf::Text centipedeMultiplierText;
        sf::Text centipedeMultiplierCostText;

        std::stringstream os;

        sf::Event ev;

        GameMenu(MenuScreen* menu);
        virtual ~GameMenu();
        void initMenu();
        void update();
        void render();

};

#endif