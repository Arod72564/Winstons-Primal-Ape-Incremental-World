#include "ArcheryGameEngine.h"

ArcheryGameEngine::ArcheryGameEngine(MenuScreen* menu){
    menuPtr = menu;
    sf::View gameView(sf::Vector2f(0,0) , sf::Vector2f(menu->menuScreen->getSize().x,menu->menuScreen->getSize().y));
}

ArcheryGameEngine::~ArcheryGameEngine(){

}

void ArcheryGameEngine::initGame(){

    //Background
    if (!backgroundTexture.loadFromFile("images/Archery/Background.png")) {
        menuPtr->menuScreen->close();
    }
    backgroundSprite.setTexture(backgroundTexture);

    //Archers
    Archer player1;
    if (!player1.archerTexture.loadFromFile("images/Archery/PlayerRight.png")) {
        menuPtr->menuScreen->close();
    }
    player1.archerSprite.setTexture(player1.archerTexture);

    Archer player2;
    if (!player2.archerTexture.loadFromFile("images/Archery/PlayerLeft.png")) {
        menuPtr->menuScreen->close();
    }
    player2.archerSprite.setTexture(player2.archerTexture);

    //Platforms
    if (!platformTexture.loadFromFile("images/Archery/Platform.png")) {
        menuPtr->menuScreen->close();
    }

    platform1.setTexture(platformTexture);

    platform2.setTexture(platformTexture);
    
    platform3.setTexture(platformTexture);

        


}

void ArcheryGameEngine::update(){

}

void ArcheryGameEngine::render(){

}