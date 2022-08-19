#include "UpgradeMenu.h"

UpgradeMenu::UpgradeMenu(MenuScreen* menu){
    menuPtr = menu;
        gameView = new sf::View(sf::Vector2f(menu->menuScreen->getSize().x/2,menu->menuScreen->getSize().y/2) , sf::Vector2f(menu->menuScreen->getSize().x,menu->menuScreen->getSize().y));
    initMenu();
}

UpgradeMenu::~UpgradeMenu(){
    delete gameView;
}

void UpgradeMenu::initMenu(){

    //TEXT

    // Centipede Mult Info
    centipedeMultiplierText.setFont(menuPtr->menuFont2);
    centipedeMultiplierText.setString("Centipede Game Multiplier: " + std::to_string(menuPtr->centipedeGameMultiplier));
    centipedeMultiplierText.setCharacterSize(15);
    centipedeMultiplierText.setFillColor(sf::Color::White);
    centipedeMultiplierText.setStyle(sf::Text::Bold);
    centipedeMultiplierText.setOrigin(centipedeMultiplierText.getLocalBounds().width / 2.f , centipedeMultiplierText.getLocalBounds().height / 2.f);
    centipedeMultiplierText.setPosition(0,0);

    // Centipede Mult Upgrade Text
    centipedeMultiplierCostText.setFont(menuPtr->menuFont2);
    centipedeMultiplierCostText.setString("Upgrade Centipede Multiplier: " + std::to_string(menuPtr->centipedeGameMultCost));
    centipedeMultiplierCostText.setCharacterSize(15);
    centipedeMultiplierCostText.setFillColor(sf::Color::White);
    centipedeMultiplierCostText.setStyle(sf::Text::Bold);
    centipedeMultiplierCostText.setOrigin(centipedeMultiplierCostText.getLocalBounds().width / 2, centipedeMultiplierCostText.getLocalBounds().height / 2);
    centipedeMultiplierCostText.setPosition(0, centipedeMultiplierText.getPosition().y + centipedeMultiplierText.getGlobalBounds().height);

}

void UpgradeMenu::update(){

    while (menuPtr->menuScreen->pollEvent(ev)) {

        switch(ev.type) {
            case sf::Event::Closed:
                gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                menuPtr->currentGameType = NULL_GAME;
                return;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (centipedeMultiplierText.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) {

                    }
                }
                break;

            case sf::Event::MouseWheelScrolled:   

                if ( ev.mouseWheelScroll.delta < 0) {
                    gameView->move(0, 20);
                    
                    if(gameView->getCenter().y > 800) { gameView->setCenter(gameView->getCenter().x, 800); }

                } else if (ev.mouseWheelScroll.delta > 0) {
                    gameView->move(0, -20);
                    if(gameView->getCenter().y < 400) { gameView->setCenter(gameView->getCenter().x, 400); }
                    
                }

            default:
                break;
        }
    }



    if (menuPtr->menuMusic.getStatus() == sf::SoundSource::Stopped) { menuPtr->nextSong(); }

    os << std::fixed << std::setprecision(2) << menuPtr->centipedeGameMultiplier;
    centipedeMultiplierText.setString("Centipede Game Multiplier: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << menuPtr->centipedeGameMultCost;
    centipedeMultiplierCostText.setString("Upgrade Centipede Multiplier: " + os.str());
    std::stringstream().swap(os);
}


void UpgradeMenu::render(){
    menuPtr->menuScreen->clear(sf::Color::Black);

    menuPtr->menuScreen->draw(centipedeMultiplierText);
    menuPtr->menuScreen->draw(centipedeMultiplierCostText);

    menuPtr->menuScreen->display();


}

