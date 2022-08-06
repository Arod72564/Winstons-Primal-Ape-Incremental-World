#ifndef ARCHERYGAMEENGINE_H
#define ARCHERYGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"

struct Archer {
    sf::Texture archerTexture;
    sf::Sprite archerSprite;
};

struct Arrow {
    static const double EPSILON = 1e-7;
    sf::Texture arrowTexture;
    sf::Sprite arrowSprite;

    // Click and drag physics
    std::complex<double> arrow_velocity;

    Arrow(Arrow arrow);

    // Arrow movement.  Might need to refactor to implement arrow collisions.
    BeamCollisionType updateMovement(std::complex<double> velocity, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, Archer archer);
};

class ArcheryGameEngine {
    public:
        MenuScreen* menuPtr;
        Archer archer1, archer2;
        Arrow *arrow1;
        sf::Texture platformTexture;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Sprite platform1;
        sf::Sprite platform2;
        sf::Sprite platform3;
        sf::View* gameView;
        sf::Event ev;

        const int MAX_ARROW_POWER = 10; // Maximum velocity in pixels.

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
