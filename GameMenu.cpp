#include "GameMenu.h"

GameMenu::GameMenu(MenuScreen* menu){
    top = 400; //middle of screen
    bottom = 800; //bottom of last game 
    menuPtr = menu;
    gameView = new sf::View(sf::Vector2f(menu->menuScreen->getSize().x/2,menu->menuScreen->getSize().y/2) , sf::Vector2f(menu->menuScreen->getSize().x,menu->menuScreen->getSize().y));
    initMenu();

}

GameMenu::~GameMenu(){
    delete gameView;
}

void GameMenu::initMenu() {

    //Textures
    if (!dungeonGameTexture.loadFromFile("images/GameMenu/PuzzleDungeon.png")) {
        std::cout << "Error loading dungeon game texture.\n";
        menuPtr->menuScreen->close();
    }
  
    if (!ArcheryGameTexture.loadFromFile("images/GameMenu/ArcheryGame.png")) {
        std::cout << "Error loading archery game texture.\n";
        menuPtr->menuScreen->close();
    }

    if (!centipedeGameTexture.loadFromFile("images/GameMenu/CentipedeGame.png")) {
        std::cout << "Error loading centipede game texture.\n";
        menuPtr->menuScreen->close();
    }

    if (!centipedeGameMult_Texture.loadFromFile("images/MenuScreen/CentipedeGameMult.png")) {
        std::cout << "Error loading centipede mult texture.\n";
        menuPtr->menuScreen->close();
    }

    //Sprites

    //Centipede Game
    centipedeGameSprite.setTexture(centipedeGameTexture);
    centipedeGameSprite.setPosition(0, 0);

    //Dungeon game
    dungeonGameSprite.setTexture(dungeonGameTexture);
    dungeonGameSprite.setPosition(centipedeGameSprite.getPosition().x,centipedeGameSprite.getPosition().y + centipedeGameSprite.getGlobalBounds().height);

    //Archery Game
    archerygameSprite.setTexture(ArcheryGameTexture);
    archerygameSprite.setPosition(dungeonGameSprite.getPosition().x, dungeonGameSprite.getPosition().y + dungeonGameSprite.getGlobalBounds().height);



    //Centipede Game Upgrades
    centipedeGameMult_Sprite.setTexture(centipedeGameMult_Texture);
    centipedeGameMult_Sprite.setOrigin(centipedeGameMult_Sprite.getLocalBounds().width / 2, centipedeGameMult_Sprite.getLocalBounds().height / 2);
    centipedeGameMult_Sprite.setPosition(menuPtr->menuScreen->getSize().x / 2, 80);
    centipedeGameMult_Sprite.setScale(0.2, 0.2);


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
    centipedeMultiplierCostText.setPosition(centipedeGameMult_Sprite.getPosition().x, centipedeGameMult_Sprite.getPosition().y + centipedeGameMult_Sprite.getGlobalBounds().height);
}

void GameMenu::update(){

    while (menuPtr->menuScreen->pollEvent(ev)) {

        switch(ev.type) {
            case sf::Event::Closed:
                gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                menuPtr->currentGameType = NULL_GAME;
                return;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (centipedeGameSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) { //CentipedeGame Prompt
                        gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                        menuPtr->currentGameType = centipedeGame;
                    } else if (dungeonGameSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) { //DungeonGame Prompt
                        gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                        menuPtr->currentGameType = dungeonGame;
                    } else if (archerygameSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) { //Archery Game Prompt
                        gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                        menuPtr->currentGameType = archeryGame;
                    }
                }
                break;

            case sf::Event::MouseWheelScrolled:   

                if ( ev.mouseWheelScroll.delta < 0) {
                    gameView->move(0, 20);
                    
                    if(gameView->getCenter().y > bottom) { gameView->setCenter(gameView->getCenter().x, bottom); }

                } else if (ev.mouseWheelScroll.delta > 0) {
                    gameView->move(0, -20);
                    if(gameView->getCenter().y < top) { gameView->setCenter(gameView->getCenter().x, top); }
                    
                }

            default:
                break;
        }
    }

    os << std::fixed << std::setprecision(2) << menuPtr->centipedeGameMultiplier;
    centipedeMultiplierText.setString("Centipede Game Multiplier: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << menuPtr->centipedeGameMultCost;
    centipedeMultiplierCostText.setString("Upgrade Centipede Multiplier: " + os.str());
    std::stringstream().swap(os);

    if (menuPtr->menuMusic.getStatus() == sf::SoundSource::Stopped) { menuPtr->nextSong(); }
}

void GameMenu::render(){
    menuPtr->menuScreen->setView(*gameView);

    if (menuPtr->currentGameType == games) {
        menuPtr->menuScreen->clear(sf::Color::Black);

        menuPtr->menuScreen->draw(centipedeGameSprite);
        menuPtr->menuScreen->draw(dungeonGameSprite);
        menuPtr->menuScreen->draw(archerygameSprite);

        menuPtr->menuScreen->display();
    }

}