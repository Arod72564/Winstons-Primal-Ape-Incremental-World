#ifndef ARCHERYGAMEENGINE_H
#define ARCHERYGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"

struct Archer;
struct Arrow;
class ArcheryGameEngine;

struct BloodSplat {

    sf::Vector2f emitter_position;
    std::complex<float> intit_velocity;

    std::vector<sf::Vector2f> particles[100];
    sf::VertexArray emitter = sf::VertexArray(sf::Points, 100);

    BloodSplat(std::complex<float> intake_velocity);

};

struct Archer {

    sf::Texture archerArmTexture;
    sf::Sprite archerArmSprite;

    sf::Texture archerTorsoTexture;
    sf::Sprite archerTorsoSprite;

    std::vector<Arrow*> arrow_vector;
};

struct Arrow {
    static constexpr float EPSILON = 1e-7f;
    int frame_time = 0;
    // sf::Texture arrowTexture;
    sf::Sprite arrowSprite;

    // Click and drag physics
    std::complex<float> arrow_velocity;

    Arrow(sf::Texture &texture, float x, float y, std::complex<float> velocity);

    // Arrow movement.  Might need to refactor to implement arrow collisions.
    BeamCollisionType updateMovement(bool &isArrowPresent, MenuScreen* menuPtr, std::complex<float> drag, const float grav, sf::Sprite bgSprite, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, sf::Sprite self, sf::Sprite enemy);
};

class ArcheryGameEngine {
    public:
        MenuScreen* menuPtr;
        Archer archer1, archer2;
        Arrow *arrow1;
        BeamCollisionType collisionType = nan_;
        std::stringstream os;

        sf::Texture arrowTexture;
        sf::Texture arrowTexture2;
        sf::Texture arrowTexture3;
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

        const double MAX_ARROW_POWER = 14.0; // Maximum velocity in pixels.
        const double LINE_LENGTH = 250.0;
        const int PLAYER_DIST = 2000;
        const int WIND_CHANGE_FREQ = 3;
        int player_dist_deviation;
        int turn_counter = 0;
        int pan_counter;
        int platform3_move = 2;

        float wind_deg_increment;
        float degRotation;
        float x_offset;
        float y_offset;

        std::complex<float> panSpeed;
        std::complex<float> v;
        std::complex<float> drag = std::complex<float>(0.f, 0.f);
        float g = 0.05;

        // Random number generator for wind
        std::normal_distribution<float> norm_dist;
        std::default_random_engine generator;

        bool is_mouse_first_pressed = false;
        //bool is_mouse_released;
        bool is_arrow_present = false;
        bool drawline;
        bool is_player_turn = true;
        bool is_panning;
        bool is_a_turn = is_arrow_present || is_panning;

        ArcheryGameEngine(MenuScreen* menu);
        virtual ~ArcheryGameEngine();


        std::complex<float> calculateEnemyV();
        void calculateLine(Arrow* const arrow);

        void initGame();
        void update();
        void render();
        void pan(sf::Sprite target);
};

#endif
