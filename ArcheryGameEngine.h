#ifndef ARCHERYGAMEENGINE_H
#define ARCHERYGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"

struct Archer {
    sf::Texture archerTexture;
    sf::Sprite archerSprite;
};

struct Arrow {
    static constexpr float EPSILON = 1e-7f;
    // sf::Texture arrowTexture;
    sf::Sprite arrowSprite;

    // Click and drag physics
    std::complex<float> arrow_velocity;

    // Arrow(sf::Texture &texture);

    // Arrow movement.  Might need to refactor to implement arrow collisions.
    BeamCollisionType updateMovement(bool &isArrowPresent, const float grav, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, Archer archer);
};

class ArcheryGameEngine {
    public:
        MenuScreen* menuPtr;
        Archer archer1, archer2;
        Arrow *arrow1;
        sf::Texture arrowTexture;
        sf::Texture platformTexture;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Sprite platform1;
        sf::Sprite platform2;
        sf::Sprite platform3;
        sf::View* gameView;
        sf::Event ev;

        sf::Vector2i initial_mouse_pos; // Calculating arrow power and angle
        sf::Vector2i final_mouse_pos; // Calculating arrow power and angle
        sf::Vertex line[2]; // Drawing line for mouse click hold and drag

        static const int MAX_ARROW_POWER = 10; // Maximum velocity in pixels.
        static const int LINE_LENGTH = 250;

        float degRotation;
        float x_offset;
        float y_offset;

        float v;
        float g = -0.01;

        bool is_mouse_first_pressed = true;
        //bool is_mouse_released;
        bool is_arrow_present = false;

        ArcheryGameEngine(MenuScreen* menu);
        virtual ~ArcheryGameEngine();
        void initGame();
        void update();
        void render();
};

#endif
