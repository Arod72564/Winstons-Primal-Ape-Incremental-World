#include "ArcheryGameEngine.h"

ArcheryGameEngine::ArcheryGameEngine(MenuScreen* menu){
    menuPtr = menu;
    gameView = new sf::View(sf::Vector2f(0,0) , sf::Vector2f(menu->menuScreen->getSize().x,menu->menuScreen->getSize().y));
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
    
    sf::Vector2f mousePosition = menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen));

    while (menuPtr->menuScreen->pollEvent(ev)) {
        switch (ev.type) {

            case sf::Event::EventType::Closed:
                menuPtr->currentGameType = NULL_GAME;
                break;

            case sf::Event::MouseButtonReleased:
                break;

            case sf::Event::MouseButtonPressed:
                break;

        }
    }
}

void ArcheryGameEngine::render(){

    menuPtr->menuScreen->setView(*gameView);
    menuPtr->menuScreen->display();

}