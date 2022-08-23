#include "GameMenu.h"

GameMenu::GameMenu(MenuScreen* menu){
    top = 400; //middle of screen
    bottom = 1200; //bottom of last game
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

    if (!ragdollGameTexture.loadFromFile("images/GameMenu/bg.png")) {
        std::cout << "Error loading background game texture.\n";
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

    //Ragdoll Game
    ragdollGameSprite.setTexture(ragdollGameTexture);
    ragdollGameSprite.setPosition(archerygameSprite.getPosition().x, archerygameSprite.getPosition().y + archerygameSprite.getGlobalBounds().height);



    //Centipede Game Upgrades
    centipedeGameMult_Sprite.setTexture(centipedeGameMult_Texture);
    centipedeGameMult_Sprite.setOrigin(centipedeGameMult_Sprite.getLocalBounds().width / 2, centipedeGameMult_Sprite.getLocalBounds().height / 2);
    centipedeGameMult_Sprite.setPosition(menuPtr->menuScreen->getSize().x / 2, 80);
    centipedeGameMult_Sprite.setScale(0.2, 0.2);



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
                    } else if (ragdollGameSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) { //Ragdoll Game Prompt
                        gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                        menuPtr->currentGameType = ragdollGame;
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



    if (menuPtr->menuMusic.getStatus() == sf::SoundSource::Stopped) { menuPtr->nextSong(); }
}

void GameMenu::render(){
    menuPtr->menuScreen->setView(*gameView);

    if (menuPtr->currentGameType == games) {
        menuPtr->menuScreen->clear(sf::Color::Black);

        menuPtr->menuScreen->draw(centipedeGameSprite);
        menuPtr->menuScreen->draw(dungeonGameSprite);
        menuPtr->menuScreen->draw(archerygameSprite);
        menuPtr->menuScreen->draw(ragdollGameSprite);

        menuPtr->menuScreen->display();
    }

}
