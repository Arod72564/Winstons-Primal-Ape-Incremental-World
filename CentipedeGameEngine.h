#ifndef CENTIPEDEGAMEENGINE_H
#define CENTIPEDEGAMEENGINE_H

#include "headerFiles.h"
#include "Centipede.h"
#include "Mushroom.h"
#include "Player.h"
#include "Beam.h"
#include "MenuScreen.h"

class CentipedeGameEngine {
    private:
        sf::RenderWindow* gameWindow;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::Font pauseFont;
        sf::Text pauseText;
        sf::Text winText;
        sf::Text pacifistWinText;
        sf::Texture centipedeTexture;
        sf::Texture centipedeTexture2;
        sf::Texture playerTexture;
        sf::Texture beamTexture;
        sf::Texture mushroomTexture4;
        sf::Texture mushroomTexture3;
        sf::Texture mushroomTexture2;
        sf::Texture mushroomTexture1;
        sf::Music pauseMusic;
        std::vector <Centipede> centipedeVector;
        std::vector <Mushroom> mushroomVector;
        BeamCollisionType beamCollisionType;
        BeamCollisionType cheaterBeamCollisionType;
        Player* player1;
        MenuScreen* menuPtr;
        Beam* playerBeam;
        Beam* cheaterBeam;
        bool displayFirstAnimation;
        bool isBeamPresent;
        bool isCheaterBeamPresent;
        bool isPaused;
        long long int animationCounter;
        long double sessionPoints;
        int beamCollisionIndex;
        int cheaterBeamCollisionIndex;
        int centipedesKilled;

    public:
        CentipedeGameEngine();
        CentipedeGameEngine(MenuScreen *menu);
        void initWindow();
        void initWindow2();
        void initTextures();
        void initSprites();
        virtual ~CentipedeGameEngine();
        void update();
        void render();
        void displayWinScreen(sf::Text &text);
};

#endif