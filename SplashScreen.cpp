#include "SplashScreen.h"

SplashScreen::SplashScreen(sf::RenderWindow* mainWindow){
    window = mainWindow;
    is_splash_displayed = true;
    initScreen();
}

SplashScreen::~SplashScreen(){

}

void SplashScreen::initScreen(){
    if (!splashScreenTexture.loadFromFile("images/SplashScreen/splashScreen_bg.png")) {
        window->close();
    }

     splashScreenSprite.setTexture(splashScreenTexture);
     splashScreenSprite.setPosition(0,0);
}

void SplashScreen::update(){
    while( window->pollEvent(ev) ) {
        switch (ev.type) {
            case sf::Event::MouseButtonPressed:
            case sf::Event::KeyPressed:
                is_splash_displayed = false;
        };
    }


}

void SplashScreen::render(){

    window->clear(sf::Color::Black);

    window->draw(splashScreenSprite);

    window->display();
}