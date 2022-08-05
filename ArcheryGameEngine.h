#ifndef ARCHERYGAMEENGINE_H
#define ARCHERYGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"

struct Archer {
    sf::Texture archerTexture;
    sf::Sprite archerSprite;
};

struct Arrow {
    sf::Texture arrowTexture;
    sf::Sprite arrowSprite;
};

class ArcheryGameEngine {
    public:
        MenuScreen* menuPtr;
        Archer archer1, archer2;
        sf::Texture platformTexture;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Sprite platform1;
        sf::Sprite platform2;
        sf::Sprite platform3;
        sf::View* gameView;
        sf::Event ev;

        float degRotation;
        float x_offset;
        float y_offset;

        float v;
        float g = -0.01;

        bool is_mouse_pressed;
        //bool is_mouse_released;
        bool is_arrow_present;

        ArcheryGameEngine(MenuScreen* menu);
        virtual ~ArcheryGameEngine();
        void initGame();
        void update();
        void render();
};

#endif