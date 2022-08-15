#ifndef MUSIC_MENU_H
#define MUSIC_MENU_H

#include "headerFiles.h"
#include "MenuScreen.h"

class MusicMenu {
    public:

        MenuScreen* menuPtr;
        sf::Texture bg1;
        sf::Texture bg1;
        sf::Texture bg1;
        sf::Texture fader;
        sf::Texture faderKnob;
        sf::Texture seekButton;

        sf::Sprite bgSprite;
        sf::Sprite faderSprite;
        sf::Sprite faderKnobSprite;
        sf::Sprite seekForward;
        sf::Sprite seekBackward;

        sf::Font font;
        sf::Text currentMusicName;


        MusicMenu(MenuScreen menu);
        virtual ~MusicMenu();
        void initMenu();
        void update();
        void render();
};

#endif