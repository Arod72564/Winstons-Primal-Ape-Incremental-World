#include "MenuScreen.h"

MenuScreen::MenuScreen(){
    this->initMenuScreen();
    this->initText();
}

MenuScreen::MenuScreen(sf::RenderWindow *window){
    this->menuScreen = nullptr;

    this->initMenuScreen2(window);
    this->initText();
}

MenuScreen::~MenuScreen(){
    this->menuMusic.stop();
    delete this->menuScreen;
}

void MenuScreen::initMenuScreen(){
    this->videoMode.height = 800;
    this->videoMode.width = 800;
    this->menuScreen = new sf::RenderWindow(this->videoMode, "Centipede", sf::Style::Titlebar | sf::Style::Close);
    std::cout << "Menu Screen sucessfully set up.\n";
    this->currentGameType = NULL_GAME;
    this->playerPoints = 0;
}

void MenuScreen::initMenuScreen2(sf::RenderWindow *window){
    std::cout << "Initializing menu screen... ";

    this->menuScreen = window;
    if(menuScreen == nullptr){
        std::cout << "the menu screen is fucked, son.\n";
        window->close();
        return;
    }

    std::cout << "Menu Screen sucessfully set up.\n";

    //Set game type to NULL_GAME for game loop in main
    this->currentGameType = NULL_GAME;

    //Initialize Player Points
    this->playerPoints = 0;

    //Initialize Game Multipliers
        //Centipede Game
    this->centipedeGameMultiplier = 1.0;
    this->centipedeGameMultCost = 100;

    //Initialize Clicker Multipliers
        // Cost to upgrade reward and multiplier
    this->clickerCostReward = 10.0;
    this->clickerCostMultiplier = 10.0;
        // Reward per click and reward multiplier
    this->clickerReward = 1.0;
    this->clickerRewardMultiplier = 1.0;
        // Multiplier for upgrade prices
    this->clickerUpgradePriceScaling = 1.15;

    //Initialize Unlocks
        //Centipede Game
        bool is_CentipedeGame_Unlocked = false;
        bool is_CheaterBeam_Unlocked = false;

}

void MenuScreen::initText(){

        //TEXTURES
    std::cout << "Initializing Textures... ";
    if(!this->clickBoxTexture.loadFromFile("images/clickBoxWinston.png")){
        std::cout << "Error loading click box texture.\n";
        this->menuScreen->close();
    }

    if(!this->clickUpgrade1_Texture.loadFromFile("images/ClickerPower.png")){
        std::cout << "Error loading clicker upgrade texture.\n";
        this->menuScreen->close();
    }

    if(!this->clickUpgrade2_Texture.loadFromFile("images/ClickerMult.png")){
        std::cout << "Error loading clicker mult texture.\n";
        this->menuScreen->close();
    }
    
    if(!this->centipedeGameMult_Texture.loadFromFile("images/CentipedeGameMult.png")){
        std::cout << "Error loading centipede mult texture.\n";
        this->menuScreen->close();
    }
    std::cout << "Textures Sucessfully Initialized.\n";

        //SPRITES
    std::cout << "Initializing Sprites... ";
    //Click box
    this->clickBoxSprite.setTexture(clickBoxTexture);
    this->clickBoxSprite.setOrigin(this->clickBoxSprite.getLocalBounds().width / 2, this->clickBoxSprite.getLocalBounds().height / 2);
    this->clickBoxSprite.setScale(0.15,0.15);
    this->clickBoxSprite.setPosition(this->menuScreen->getSize().x / 2, this->menuScreen->getSize().y / 2);

    //Click box upgrades
    this->clickUpgrade1_Sprite.setTexture(clickUpgrade1_Texture);
    this->clickUpgrade1_Sprite.setPosition(70, 650);
    this->clickUpgrade1_Sprite.setScale(0.15, 0.15);

    this->clickUpgrade2_Sprite.setTexture(clickUpgrade2_Texture);
    this->clickUpgrade2_Sprite.setPosition(clickUpgrade1_Sprite.getPosition().x + clickUpgrade1_Sprite.getGlobalBounds().width + 10, clickUpgrade1_Sprite.getPosition().y);
    this->clickUpgrade2_Sprite.setScale(0.15, 0.15);

    //Centipede Game Upgrades
    this->centipedeGameMult_Sprite.setTexture(centipedeGameMult_Texture);
    this->centipedeGameMult_Sprite.setOrigin(this->centipedeGameMult_Sprite.getLocalBounds().width / 2, this->centipedeGameMult_Sprite.getLocalBounds().height / 2);
    this->centipedeGameMult_Sprite.setPosition(this->menuScreen->getSize().x / 2, 80);
    this->centipedeGameMult_Sprite.setScale(0.2, 0.2);
    std::cout << "Sprites Sucessfully Initialized.\n";

        //FONTS
    std::cout << "Initializing Fonts... ";
    if(!this->menuFont1.loadFromFile("fonts/ALGER.TTF")){
        std::cout << "Error loading menu font 1.\n";
        this->menuScreen->close();
    }

    if(!this->menuFont2.loadFromFile("fonts/ARLRDBD.TTF")){
        std::cout << "Error loading menu font 2.\n";
        this->menuScreen->close();
    }
    std::cout << "Fonts Sucessfully Initialized.\n";

        //TEXT
    std::cout << "Initializing Text... ";
    //Centipede Game Text
    this->centipedeGameText.setFont(menuFont2);
    this->centipedeGameText.setString("Buy Centipede Game: 100");
    this->centipedeGameText.setCharacterSize(30);
    this->centipedeGameText.setFillColor(sf::Color::Blue);
    this->centipedeGameText.setStyle(sf::Text::Bold);
    this->centipedeGameText.setPosition((this->menuScreen->getSize().x / 2) - (this->centipedeGameText.getLocalBounds().width / 2), 0);

    // Player Points Text
    this->pointsText.setFont(menuFont2);
    this->pointsText.setString(std::to_string(this->playerPoints));
    this->pointsText.setCharacterSize(20);
    this->pointsText.setFillColor(sf::Color::Red);
    this->pointsText.setStyle(sf::Text::Bold);
    this->pointsText.setOrigin(pointsText.getLocalBounds().width / 2 , pointsText.getLocalBounds().height / 2);
    this->pointsText.setPosition(menuScreen->getSize().x / 2, clickBoxSprite.getPosition().y + (clickBoxSprite.getGlobalBounds().height / 2.f) + 50);

    // Clicker Reward Info
    this->clickerRewardInfo.setFont(menuFont2);
    this->clickerRewardInfo.setString("Clicker Reward per Click: " + std::to_string(this->clickerReward));
    this->clickerRewardInfo.setCharacterSize(15);
    this->clickerRewardInfo.setFillColor(sf::Color::White);
    this->clickerRewardInfo.setStyle(sf::Text::Bold);
    this->clickerRewardInfo.setOrigin(clickerRewardInfo.getLocalBounds().width / 2 , clickerRewardInfo.getLocalBounds().height / 2);
    this->clickerRewardInfo.setPosition(this->pointsText.getPosition().x, this->pointsText.getPosition().y + 30);

    // Clicker Mult Info
    this->clickerMultiplierInfo.setFont(menuFont2);
    this->clickerMultiplierInfo.setString("Clicker Multiplier: " + std::to_string(this->clickerRewardMultiplier));
    this->clickerMultiplierInfo.setCharacterSize(15);
    this->clickerMultiplierInfo.setFillColor(sf::Color::White);
    this->clickerMultiplierInfo.setStyle(sf::Text::Bold);
    this->clickerMultiplierInfo.setOrigin(clickerMultiplierInfo.getLocalBounds().width / 2 , clickerMultiplierInfo.getLocalBounds().height / 2);
    this->clickerMultiplierInfo.setPosition(this->clickerRewardInfo.getPosition().x, this->clickerRewardInfo.getPosition().y + 20);

    // Centipede Mult Info
    this->centipedeMultiplierText.setFont(menuFont2);
    this->centipedeMultiplierText.setString("Centipede Game Multiplier: " + std::to_string(this->centipedeGameMultiplier));
    this->centipedeMultiplierText.setCharacterSize(15);
    this->centipedeMultiplierText.setFillColor(sf::Color::White);
    this->centipedeMultiplierText.setStyle(sf::Text::Bold);
    this->centipedeMultiplierText.setOrigin(centipedeMultiplierText.getLocalBounds().width / 2.f , centipedeMultiplierText.getLocalBounds().height / 2.f);
    this->centipedeMultiplierText.setPosition(this->clickerMultiplierInfo.getPosition().x, this->clickerMultiplierInfo.getPosition().y + 20);

    // Clicker Reward Upgrade Text
    this->upgradeClickerRewardText.setFont(menuFont2);
    this->upgradeClickerRewardText.setString("Upgrade Cost: " + std::to_string(this->clickerCostReward));
    this->upgradeClickerRewardText.setCharacterSize(15);
    this->upgradeClickerRewardText.setFillColor(sf::Color::White);
    this->upgradeClickerRewardText.setStyle(sf::Text::Bold);
    this->upgradeClickerRewardText.setPosition(clickUpgrade1_Sprite.getPosition().x + 50, clickUpgrade1_Sprite.getPosition().y + clickUpgrade1_Sprite.getGlobalBounds().height + 10);

    // Clicker Multiplier Upgrade Text
    this->upgradeClickerMultiplierText.setFont(menuFont2);
    this->upgradeClickerMultiplierText.setString("Upgrade Cost: " + std::to_string(this->clickerCostMultiplier));
    this->upgradeClickerMultiplierText.setCharacterSize(15);
    this->upgradeClickerMultiplierText.setFillColor(sf::Color::White);
    this->upgradeClickerMultiplierText.setStyle(sf::Text::Bold);
    this->upgradeClickerMultiplierText.setPosition(clickUpgrade2_Sprite.getPosition().x + 50, clickUpgrade2_Sprite.getPosition().y + clickUpgrade2_Sprite.getGlobalBounds().height + 10);

    // Centipede Mult Upgrade Text
    this->centipedeMultiplierCostText.setFont(menuFont2);
    this->centipedeMultiplierCostText.setString("Upgrade Centipede Multiplier: " + std::to_string(this->centipedeGameMultCost));
    this->centipedeMultiplierCostText.setCharacterSize(15);
    this->centipedeMultiplierCostText.setFillColor(sf::Color::White);
    this->centipedeMultiplierCostText.setStyle(sf::Text::Bold);
    this->centipedeMultiplierCostText.setOrigin(this->centipedeMultiplierCostText.getLocalBounds().width / 2, this->centipedeMultiplierCostText.getLocalBounds().height / 2);
    this->centipedeMultiplierCostText.setPosition(centipedeGameMult_Sprite.getPosition().x, centipedeGameMult_Sprite.getPosition().y + centipedeGameMult_Sprite.getGlobalBounds().height);
    
    std::cout << "Text Sucessfully Initialized.\n";

        //MUSIC
    std::cout << "Initializing Music... ";
    if(!this->menuMusic.openFromFile("Music/WinstonSexyRage2.wav")){
        std::cout << "Error loading menu music.\n";
        this->menuScreen->close();
    }
    this->menuMusic.setVolume(100);
    this->menuMusic.setPitch(1);
    this->menuMusic.setLoop(true);
    this->menuMusic.play();
    std::cout << "Music Sucessfully Initialized.\n";
}

void MenuScreen::update(){
    std::srand(std::time(nullptr));

    //Event Polling
    while (this->menuScreen->pollEvent(this->event)) {

        switch(this->event.type){
            case sf::Event::Closed:
                this->menuScreen->close();
                return;

            case sf::Event::MouseButtonPressed:
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if(this->clickBoxSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))){ //ClickBox
                        playerPoints += clickerReward * clickerRewardMultiplier;

                    } else if (this->upgradeClickerRewardText.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen))) || this->clickUpgrade1_Sprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))){ //ClickerReward
                        if(this->playerPoints >= this->clickerCostReward) { 
                            this->playerPoints -= clickerCostReward;
                            clickerReward++;
                            clickerCostReward = clickerCostReward * clickerUpgradePriceScaling;
                        }

                    } else if (this->upgradeClickerMultiplierText.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen))) || this->clickUpgrade2_Sprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //ClickerMult
                        if(this->playerPoints >= this->clickerCostMultiplier) { 
                            this->playerPoints -= clickerCostMultiplier;
                            clickerRewardMultiplier += double((rand() % 10) + 1) / 100;
                            clickerCostMultiplier = clickerCostMultiplier * clickerUpgradePriceScaling;
                        }

                    } else if (this->centipedeMultiplierCostText.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen))) || this->centipedeGameMult_Sprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //CentipedeGame Mult
                        if(this->playerPoints >= this->centipedeGameMultCost) { 
                            this->playerPoints -= this->centipedeGameMultCost;
                            centipedeGameMultiplier += double((rand() % 50) + 26) / 100;
                            centipedeGameMultCost = centipedeGameMultCost * clickerUpgradePriceScaling;
                        }

                    } else if (this->centipedeGameText.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) { //CentipedeGame Prompt
                        if(is_CentipedeGame_Unlocked == false && this->playerPoints >= 100.f) {
                            is_CentipedeGame_Unlocked = true;
                            this->playerPoints -= 100.f;
                            centipedeGameText.setString("Centipede Game");
                            this->centipedeGameText.setCharacterSize(50);
                        } else if(is_CentipedeGame_Unlocked == true){
                            this->currentGameType = centipedeGame;
                        }
                    }
                break;
            case sf::Event::MouseWheelMoved:
                if (sf::Mouse::Wheel::HorizontalWheel && this->clickBoxSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) {
                    playerPoints += clickerReward * clickerRewardMultiplier;
                } else if (sf::Mouse::Wheel::VerticalWheel && this->clickBoxSprite.getGlobalBounds().contains(menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuScreen)))) {
                    playerPoints += clickerReward * clickerRewardMultiplier;
                }
        }
    }

    //Update Text on Screen using SS to format
    std::stringstream os;
    long double totalRewardPerClick = this->clickerReward * this->clickerRewardMultiplier;

    os << std::fixed << std::setprecision(2) << this->playerPoints;
    this->pointsText.setString(os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << this->clickerCostReward;
    this->upgradeClickerRewardText.setString("Upgrade Cost: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << this->clickerCostMultiplier;
    this->upgradeClickerMultiplierText.setString("Upgrade Cost: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << totalRewardPerClick;
    this->clickerRewardInfo.setString("Clicker Reward per Click: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << this->clickerRewardMultiplier;
    this->clickerMultiplierInfo.setString("Clicker Multiplier: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << this->centipedeGameMultiplier;
    this->centipedeMultiplierText.setString("Centipede Game Multiplier: " + os.str());
    std::stringstream().swap(os);

    os << std::fixed << std::setprecision(2) << this->centipedeGameMultCost;
    this->centipedeMultiplierCostText.setString("Upgrade Centipede Multiplier: " + os.str());
    std::stringstream().swap(os);
    }
}

void MenuScreen::render() {
    this->menuScreen->clear(sf::Color::Black);

    this->menuScreen->draw(this->pointsText);
    this->menuScreen->draw(clickUpgrade1_Sprite);
    this->menuScreen->draw(clickUpgrade2_Sprite);

    this->menuScreen->draw(this->upgradeClickerRewardText);
    this->menuScreen->draw(this->upgradeClickerMultiplierText);

    this->menuScreen->draw(this->clickerRewardInfo);
    this->menuScreen->draw(this->clickerMultiplierInfo);
    this->menuScreen->draw(this->clickBoxSprite);

    //Centipede Game
    this->menuScreen->draw(this->centipedeGameText);
    if(this->is_CentipedeGame_Unlocked) {
        this->menuScreen->draw(this->centipedeMultiplierText);
        this->menuScreen->draw(this->centipedeMultiplierCostText);
        this->menuScreen->draw(this->centipedeGameMult_Sprite);
    }


    this->menuScreen->display();
}

bool MenuScreen::isWindowOpen(){
    return this->menuScreen->isOpen();
}

