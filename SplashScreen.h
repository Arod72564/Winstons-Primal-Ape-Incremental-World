#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include "headerFiles.h"

class SplashScreen {
    public:

        sf::Texture splashScreenTexture;
        sf::Sprite splashScreenSprite;
        sf::RenderWindow* window;
        sf::Event ev;
        bool is_splash_displayed;

        SplashScreen(sf::RenderWindow* mainWindow);
        virtual ~SplashScreen();
        void initScreen();
        void update();
        void render();

};

#endif