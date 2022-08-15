#ifndef ARCHERYGAMEENGINE_H
#define ARCHERYGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"

struct Archer {
    sf::Texture archerTexture;
    sf::Sprite archerSprite;

    sf::Texture archerArmTexture;
    sf::Sprite archerArmSprite;

    sf::Texture archerTorsoTexture;
    sf::Sprite archerTorsoSprite;
};

struct Arrow {
    static constexpr float EPSILON = 1e-7f;
    // sf::Texture arrowTexture;
    sf::Sprite arrowSprite;

    // Click and drag physics
    std::complex<float> arrow_velocity;

    Arrow(sf::Texture &texture, float x, float y, std::complex<float> velocity);

    // Arrow movement.  Might need to refactor to implement arrow collisions.
    BeamCollisionType updateMovement(bool &isArrowPresent, std::complex<float> drag, const float grav, sf::Sprite bgSprite, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, Archer enemy);
};

class ArcheryGameEngine {
    public:
        MenuScreen* menuPtr;
        Archer archer1, archer2;
        Arrow *arrow1;
        BeamCollisionType collisionType = nan_;
        sf::Texture arrowTexture;
        sf::Texture platformTexture;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Sprite platform1;
        sf::Sprite platform2;
        sf::Sprite platform3;
        sf::Sprite wind_indicator;
        sf::Text arrowPower;
        sf::Text arrowDeg;
        sf::Font textFont;
        sf::View* gameView;
        sf::Event ev;
        sf::CircleShape compass;
        // sf::Clock clock;
        // sf::Time time;

        sf::Vector2f initial_mouse_pos; // Calculating arrow power and angle
        sf::Vector2f final_mouse_pos; // Calculating arrow power and angle
        sf::Vertex line[2]; // Drawing line for mouse click hold and drag

        const double MAX_ARROW_POWER = 10.0; // Maximum velocity in pixels.
        const double LINE_LENGTH = 250.0;
        const int PLAYER_DIST = 2000;
        int turn_counter = 0;
        int pan_counter;
        int platform3_move = 5;

        float degRotation;
        float x_offset;
        float y_offset;

        std::complex<float> panSpeed;
        std::complex<float> v;
        std::complex<float> drag = std::complex<float>(0.f, 0.f);
        float g = 0.05;

        bool is_mouse_first_pressed = false;
        //bool is_mouse_released;
        bool is_arrow_present = false;
        bool drawline;
        bool is_player_turn = true;
        bool is_panning;
        bool is_a_turn = is_arrow_present || is_panning;

        ArcheryGameEngine(MenuScreen* menu);
        virtual ~ArcheryGameEngine();

        void calculateLine(Arrow* const arrow);

        void initGame();
        void update();
        void render();
        void pan(sf::Sprite target);
};

#endif
