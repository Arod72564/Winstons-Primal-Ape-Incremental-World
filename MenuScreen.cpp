#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::RenderWindow *window) {
    menuScreen = nullptr;

    initMenuScreen(window);
    initText();
}

MenuScreen::~MenuScreen() {
    menuMusic.stop();
    delete menuScreen;
}


void MenuScreen::initMenuScreen(sf::RenderWindow *window) {
    std::cout << "Initializing menu screen... ";

    menuScreen = window;
    if (menuScreen == nullptr) {
        std::cout << "the menu screen is fucked, son.\n";
        window->close();
        return;
    }

    std::cout << "Menu Screen sucessfully set up.\n";

    //Set game type to NULL_GAME for game loop in main
    currentGameType = NULL_GAME;

    //Initialize Player Points
    playerPoints = 0;

    //Initialize Game Multipliers
        //Centipede Game
    centipedeGameMultiplier = 1.0;
    centipedeGameMultCost = 100;

    //Initialize Clicker Multipliers
        // Cost to upgrade reward and multiplier
    clickerCostReward = 10.0;
    clickerCostMultiplier = 10.0;
        // Reward per click and reward multiplier
    clickerReward = 1.0;
    clickerRewardMultiplier = 1.0;
        // Multiplier for upgrade prices
    clickerUpgradePriceScaling = 1.15;

    //Initialize Unlocks
        //Centipede Game
        bool is_CentipedeGame_Unlocked = false;
        bool is_CheaterBeam_Unlocked = true;

        bool is_MenuMusic_Paused = false;

}

void MenuScreen::initText() {

        //TEXTURES
    std::cout << "Initializing Textures... ";
    if (!clickBoxTexture.loadFromFile("images/MenuScreen/clickBoxWinston.png")) {
        std::cout << "Error loading click box texture.\n";
        menuScreen->close();
    }

    if (!clickUpgrade1_Texture.loadFromFile("images/MenuScreen/ClickerPower.png")) {
        std::cout << "Error loading clicker upgrade texture.\n";
        menuScreen->close();
    }

    if (!clickUpgrade2_Texture.loadFromFile("images/MenuScreen/ClickerMult.png")) {
        std::cout << "Error loading clicker mult texture.\n";
        menuScreen->close();
    }

    if (!muteButtonTexture.loadFromFile("images/MenuScreen/MuteButton.png")) {
        std::cout << "Error loading mute button texture.\n";
        menuScreen->close();
    }

    if (!backgroundTexture1.loadFromFile("images/MenuScreen/background1.png")) {
        std::cout << "Error loading background texture.\n";
        menuScreen->close();
    }

    if (!backgroundTexture2.loadFromFile("images/MenuScreen/background2.png")) {
        std::cout << "Error loading background texture.\n";
        menuScreen->close();
    }

    if (!backgroundTexture3.loadFromFile("images/MenuScreen/background3.png")) {
        std::cout << "Error loading background texture.\n";
        menuScreen->close();
    }

    if (!gameMenuTexture.loadFromFile("images/MenuScreen/GAMES.png")) {
        menuScreen->close();
    }

    if (!upgradeMenuTexture.loadFromFile("images/MenuScreen/UPGRADES.png")) {
        menuScreen->close();
    }

    std::cout << "Textures Sucessfully Initialized.\n";

        //SPRITES
    std::cout << "Initializing Sprites... ";
    //Click box
    clickBoxSprite.setTexture(clickBoxTexture);
    clickBoxSprite.setOrigin(clickBoxSprite.getLocalBounds().width / 2, clickBoxSprite.getLocalBounds().height / 2);
    clickBoxSprite.setScale(0.15,0.15);
    clickBoxSprite.setPosition(menuScreen->getSize().x / 2, menuScreen->getSize().y / 2);

    //Click box upgrades
    clickUpgrade1_Sprite.setTexture(clickUpgrade1_Texture);
    clickUpgrade1_Sprite.setPosition(70, 650);
    clickUpgrade1_Sprite.setScale(0.15, 0.15);

    clickUpgrade2_Sprite.setTexture(clickUpgrade2_Texture);
    clickUpgrade2_Sprite.setPosition(clickUpgrade1_Sprite.getPosition().x + clickUpgrade1_Sprite.getGlobalBounds().width + 10, clickUpgrade1_Sprite.getPosition().y);
    clickUpgrade2_Sprite.setScale(0.15, 0.15);



    //Mute Button
    muteButtonSprite.setTexture(muteButtonTexture);
    muteButtonSprite.setPosition(menuScreen->getSize().x - muteButtonSprite.getGlobalBounds().width, menuScreen->getSize().y - muteButtonSprite.getGlobalBounds().height);
    
    //Background
    backgroundSprite.setTexture(backgroundTexture1);

    //Game Menu
    gameMenuSprite.setTexture(gameMenuTexture);
    gameMenuSprite.setPosition(0,200);
    gameMenuSprite.setScale(0.6, 0.6);

    upgradeMenuSprite.setTexture(upgradeMenuTexture);
    upgradeMenuSprite.setPosition(0, gameMenuSprite.getPosition().y + gameMenuSprite.getGlobalBounds().height);
    upgradeMenuSprite.setScale(0.6, 0.6);

    std::cout << "Sprites Sucessfully Initialized.\n";



        //FONTS
    std::cout << "Initializing Fonts... ";
    if (!menuFont1.loadFromFile("fonts/ALGER.TTF")) {
        std::cout << "Error loading menu font 1.\n";
        menuScreen->close();
    }

    if (!menuFont2.loadFromFile("fonts/ARLRDBD.TTF")) {
        std::cout << "Error loading menu font 2.\n";
        menuScreen->close();
    }
    std::cout << "Fonts Sucessfully Initialized.\n";

        //TEXT
    std::cout << "Initializing Text... ";

    //Centipede Game Text
    centipedeGameText.setFont(menuFont2);
    centipedeGameText.setString("Buy Centipede Game: 100");
    centipedeGameText.setCharacterSize(30);
    centipedeGameText.setFillColor(sf::Color::Blue);
    centipedeGameText.setStyle(sf::Text::Bold);
    centipedeGameText.setPosition( (menuScreen->getSize().x / 2) - (centipedeGameText.getLocalBounds().width / 2), 0);

    // Player Points Text
    pointsText.setFont(menuFont2);
    pointsText.setString(std::to_string(playerPoints));
    pointsText.setCharacterSize(20);
    pointsText.setFillColor(sf::Color::Red);
    pointsText.setStyle(sf::Text::Bold);
    pointsText.setOrigin(pointsText.getLocalBounds().width / 2 , pointsText.getLocalBounds().height / 2);
    pointsText.setPosition(menuScreen->getSize().x / 2, clickBoxSprite.getPosition().y + (clickBoxSprite.getGlobalBounds().height / 2.f) + 50);

    // Clicker Reward Info
    clickerRewardInfo.setFont(menuFont2);
    clickerRewardInfo.setString("Clicker Reward per Click: " + std::to_string(clickerReward));
    clickerRewardInfo.setCharacterSize(15);
    clickerRewardInfo.setFillColor(sf::Color::White);
    clickerRewardInfo.setStyle(sf::Text::Bold);
    clickerRewardInfo.setOrigin(clickerRewardInfo.getLocalBounds().width / 2 , clickerRewardInfo.getLocalBounds().height / 2);
    clickerRewardInfo.setPosition(pointsText.getPosition().x, pointsText.getPosition().y + 30);

    // Clicker Mult Info
    clickerMultiplierInfo.setFont(menuFont2);
    clickerMultiplierInfo.setString("Clicker Multiplier: " + std::to_string(clickerRewardMultiplier));
    clickerMultiplierInfo.setCharacterSize(15);
    clickerMultiplierInfo.setFillColor(sf::Color::White);
    clickerMultiplierInfo.setStyle(sf::Text::Bold);
    clickerMultiplierInfo.setOrigin(clickerMultiplierInfo.getLocalBounds().width / 2 , clickerMultiplierInfo.getLocalBounds().height / 2);
    clickerMultiplierInfo.setPosition(clickerRewardInfo.getPosition().x, clickerRewardInfo.getPosition().y + 20);



    // Clicker Reward Upgrade Text
    upgradeClickerRewardText.setFont(menuFont2);
    upgradeClickerRewardText.setString("Upgrade Cost: " + std::to_string(clickerCostReward));
    upgradeClickerRewardText.setCharacterSize(15);
    upgradeClickerRewardText.setFillColor(sf::Color::White);
    upgradeClickerRewardText.setStyle(sf::Text::Bold);
    upgradeClickerRewardText.setPosition(clickUpgrade1_Sprite.getPosition().x + 50, clickUpgrade1_Sprite.getPosition().y + clickUpgrade1_Sprite.getGlobalBounds().height + 10);

    // Clicker Multiplier Upgrade Text
    upgradeClickerMultiplierText.setFont(menuFont2);
    upgradeClickerMultiplierText.setString("Upgrade Cost: " + std::to_string(clickerCostMultiplier));
    upgradeClickerMultiplierText.setCharacterSize(15);
    upgradeClickerMultiplierText.setFillColor(sf::Color::White);
    upgradeClickerMultiplierText.setStyle(sf::Text::Bold);
    upgradeClickerMultiplierText.setPosition(clickUpgrade2_Sprite.getPosition().x + 50, clickUpgrade2_Sprite.getPosition().y + clickUpgrade2_Sprite.getGlobalBounds().height + 10);



    std::cout << "Text Sucessfully Initialized.\n";

        //MUSIC
    std::cout << "Initializing Music... ";

    musicNameVec.push_back("Music/MusicVec/WinstonTrap.ogg");
    musicNameVec.push_back("Music/MusicVec/WinstonSexyRage2.ogg");
    musicNameVec.push_back("Music/MusicVec/Schizstoned-phrenia Audio.ogg");


    if (!menuMusic.openFromFile("Music/MusicVec/WinstonTrap.ogg")) {
        std::cout << "Error loading menu music.\n";
        menuScreen->close();
    }
    
    menuMusic.setVolume(musicVolume);
    menuMusic.setPitch(1);
    menuMusic.setLoop(false);
    menuMusic.play();
    std::cout << "Music Sucessfully Initialized.\n";
}

void MenuScreen::update() {
    std::srand(std::time(nullptr));

    //Event Polling
    while (menuScreen->pollEvent(event)) {

        switch(event.type) {
            case sf::Event::Closed:
                menuScreen->close();
                return;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (clickBoxSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //ClickBox
                        playerPoints += clickerReward * clickerRewardMultiplier;

                    } else if (upgradeClickerRewardText.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen))) || clickUpgrade1_Sprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //ClickerReward
                        if (playerPoints >= clickerCostReward) {
                            playerPoints -= clickerCostReward;
                            clickerReward++;
                            clickerCostReward = clickerCostReward * clickerUpgradePriceScaling;
                        }

                    } else if (upgradeClickerMultiplierText.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen))) || clickUpgrade2_Sprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //ClickerMult
                        if (playerPoints >= clickerCostMultiplier) {
                            playerPoints -= clickerCostMultiplier;
                            clickerRewardMultiplier += double( (rand() % 10) + 1) / 100;
                            clickerCostMultiplier = clickerCostMultiplier * clickerUpgradePriceScaling;
                        }
                    } else if (muteButtonSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //Pause music button
                        currentGameType = music;
                    } else if (gameMenuSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //Game menu
                        currentGameType = games;
                    } else if (upgradeMenuSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //Game menu
                        currentGameType = upgrades;
                    }
                break;

            case sf::Event::MouseWheelMoved:
                if (sf::Mouse::Wheel::HorizontalWheel && clickBoxSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) {
                    playerPoints += clickerReward * clickerRewardMultiplier;
                } else if (sf::Mouse::Wheel::VerticalWheel && clickBoxSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) {
                    playerPoints += clickerReward * clickerRewardMultiplier;
                }
        }
    }

    //Update Text on Screen using SS to format
    std::stringstream os;
    long double totalRewardPerClick = clickerReward * clickerRewardMultiplier;

    os << std::fixed << std::setprecision(2) << playerPoints;
    pointsText.setString(os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << clickerCostReward;
    upgradeClickerRewardText.setString("Upgrade Cost: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << clickerCostMultiplier;
    upgradeClickerMultiplierText.setString("Upgrade Cost: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << totalRewardPerClick;
    clickerRewardInfo.setString("Clicker Reward per Click: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << clickerRewardMultiplier;
    clickerMultiplierInfo.setString("Clicker Multiplier: " + os.str());
    std::stringstream().swap(os);


    }

    //set background texture
    counter = (1+counter) % 60;
    if (counter == 19) {
        backgroundSprite.setTexture(backgroundTexture2);
    } else if (counter == 39 ) {
        backgroundSprite.setTexture(backgroundTexture3);
    } else if (counter == 59) {
        backgroundSprite.setTexture(backgroundTexture1);
    }
}

void MenuScreen::render() {
    menuScreen->clear(sf::Color::Black);

    menuScreen->draw(backgroundSprite);

    menuScreen->draw(pointsText);
    menuScreen->draw(clickUpgrade1_Sprite);
    menuScreen->draw(clickUpgrade2_Sprite);

    menuScreen->draw(upgradeClickerRewardText);
    menuScreen->draw(upgradeClickerMultiplierText);

    menuScreen->draw(clickerRewardInfo);
    menuScreen->draw(clickerMultiplierInfo);
    menuScreen->draw(clickBoxSprite);

    menuScreen->draw(muteButtonSprite);

    menuScreen->draw(gameMenuSprite);
    menuScreen->draw(upgradeMenuSprite);

    // Display menu screen
    menuScreen->display();
}

bool MenuScreen::isWindowOpen() {
    return menuScreen->isOpen();
}

void MenuScreen::showShopMenu() {
    bool isInShop = true;
    while(isInShop) {
        menuScreen->clear(sf::Color::Black);
        while (menuScreen->pollEvent(event)) {
            switch(event.type) {
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        //Click upgrade sprites
                        //If click exit button
                            // isInShop = false;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

void MenuScreen::nextSong(){
    currentMusicIndex++;
    
    menuMusic.openFromFile(musicNameVec[abs(currentMusicIndex % int(musicNameVec.size()))]);
    currentMusicName.setString(musicNameVec[abs(currentMusicIndex % int(musicNameVec.size()))]);

    menuMusic.setVolume(musicVolume);
    menuMusic.play();
    is_MenuMusic_Paused = false;
}