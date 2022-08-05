#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "headerFiles.h"

class MenuScreen {

    public:
        sf::VideoMode videoMode;
        sf::RenderWindow* menuScreen;
        sf::Texture clickBoxTexture;
        sf::Texture clickUpgrade1_Texture;
        sf::Texture clickUpgrade2_Texture;
        sf::Texture centipedeGameMult_Texture;
        sf::Texture muteButtonTexture;
        sf::Sprite clickBoxSprite;
        sf::Sprite clickUpgrade1_Sprite;
        sf::Sprite clickUpgrade2_Sprite;
        sf::Sprite centipedeGameMult_Sprite;
        sf::Sprite muteButtonSprite;
        sf::Font menuFont1;
        sf::Font menuFont2;

        sf::Text centipedeGameText;
        sf::Text dungeonGameText;
        sf::Text ArcheryGameText;

        sf::Text pointsText;

        sf::Text upgradeClickerRewardText;
        sf::Text upgradeClickerMultiplierText;

        sf::Text clickerRewardInfo;
        sf::Text clickerMultiplierInfo;
 
        sf::Text centipedeMultiplierText;
        sf::Text centipedeMultiplierCostText;

        sf::Music menuMusic;
        sf::SoundBuffer soundBuffer;
        sf::Sound unlockSound;
        sf::Event event;
        GameTypes currentGameType;

        //Player Points
        long double playerPoints;

        //Game Multipliers
        double centipedeGameMultiplier;
        double centipedeGameMultCost;

        //Clicker Multipliers
        double clickerCostReward;
        double clickerCostMultiplier;
        double clickerReward;
        double clickerRewardMultiplier;
        double clickerUpgradePriceScaling;

        //Unlocks
            //CentipedeGame Unlocks
        bool is_CentipedeGame_Unlocked;
        bool is_CheaterBeam_Unlocked;

        bool is_MenuMusic_Paused;



        MenuScreen();
        MenuScreen(sf::RenderWindow *window);
        virtual ~MenuScreen();
        void initMenuScreen();
        void initMenuScreen2(sf::RenderWindow *window);
        void initText();
        void update();
        void render();
        bool isWindowOpen();
        void showShopMenu();
        

};

#endif