#ifndef ARCHERYGAMEENGINE_H
#define ARCHERYGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"

struct Archer;
struct Arrow;
class ArcheryGameEngine;

struct BloodSplat {
    const float MAX_SPEED = 5.f;
    int NUM_OF_PARTS = 1e2;

    sf::Vector2f emitter_position;

    std::vector<sf::Vector2f> particles = std::vector<sf::Vector2f>(NUM_OF_PARTS, sf::Vector2f());
    sf::VertexArray blood = sf::VertexArray(sf::Points, NUM_OF_PARTS);

    void createBloodSplat(const sf::Vector2f init_position, std::complex<float> intake_velocity, std::default_random_engine generator, const std::normal_distribution<float> norm_dist, int parts);
    void updateMovement();

};

struct Archer {

    sf::Texture archerArmTexture;
    sf::Sprite archerArmSprite;

    sf::Texture archerHeadTexture;
    sf::Sprite archerHeadSprite;

    sf::Texture archerTorsoTexture;
    sf::Sprite archerTorsoSprite;

    sf::Texture archerLegsTexture;
    sf::Sprite archerLegsSprite;

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
    ArrowCollisionType updateMovement(bool &isArrowPresent, MenuScreen* menuPtr, std::complex<float> drag, const float grav, sf::Sprite bgSprite, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, sf::Sprite self, sf::Sprite enemyHead, sf::Sprite enemyTorso, sf::Sprite enemyLegs);
};

class ArcheryGameEngine {
    public:
        MenuScreen* menuPtr;
        Archer archer1, archer2;
        Arrow *arrow1;
        ArrowCollisionType collisionType = none;
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

        BloodSplat bloodSplat;

        std::complex<float> panSpeed;
        std::complex<float> v;
        std::complex<float> drag = std::complex<float>(0.f, 0.f);
        float g = 0.05;

        // Random number generator for wind
        std::normal_distribution<float> norm_dist = std::normal_distribution<float>(1.f, 0.1f);;
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


        std::complex<float> calculateEnemyV(GameDifficulty game_diff);
        void calculateLine(Arrow* const arrow);

        void initGame();
        void update();
        void render();
        void pan(sf::Sprite target);
};

#endif
