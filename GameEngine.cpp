#include "GameEngine.h"

#define NUM_CENTIPEDE 10


GameEngine::GameEngine(){
    this->initWindow();
    this->initTextures();
    this->initSprites();
}

GameEngine::GameEngine(MenuScreen *menu){
    this->menuPtr = menu;
    this->gameWindow = menu->menuScreen;
    this->initWindow2();
    this->initTextures();
    this->initSprites();
}

GameEngine::~GameEngine(){
    sf::Vector2u tempVec(800,800);
    this->gameWindow->setSize(tempVec);
    delete this->player1;
}

void GameEngine::initWindow(){
    this->videoMode.height = WINDOW_HEIGHT;
    this->videoMode.width = WINDOW_WIDTH;
    this->gameWindow = new sf::RenderWindow(this->videoMode, "Centipede", sf::Style::Titlebar | sf::Style::Close);
    std::cout << "Centipede Game window sucessfully set up.\n";
}

void GameEngine::initWindow2(){
    sf::Vector2u tempVec(800,800);
    this->gameWindow->setSize(tempVec);
    std::cout << "Centipede Game window sucessfully set up.\n";
}

void GameEngine::initTextures() {
    std::cout << "Loading textures... ";

    if(!this->centipedeTexture.loadFromFile("images/winstonpede_right1.png")){
        std::cout << "Failed to load centipede texture 1.\n";
        this->gameWindow->close();
    }

    if(!this->centipedeTexture2.loadFromFile("images/winstonpede_right2.png")){
        std::cout << "Failed to load centipede textures 2.\n";
        this->gameWindow->close();
    }

    if(!this->mushroomTexture4.loadFromFile("images/Winston4.png")){
        std::cout << "Failed to load mushroom texture 4.\n";
        this->gameWindow->close();
    }

    if(!this->mushroomTexture3.loadFromFile("images/Winston3.png")){
        std::cout << "Failed to load mushroom texture 3.\n";
        this->gameWindow->close();
    }

    if(!this->mushroomTexture2.loadFromFile("images/Winston2.png")){
        std::cout << "Failed to load mushroom texture 2.\n";
        this->gameWindow->close();
    }

    if(!this->mushroomTexture1.loadFromFile("images/Winston1.png")){
        std::cout << "Failed to load mushroom texture 1.\n";
        this->gameWindow->close();
    }

    if(!this->playerTexture.loadFromFile("images/WinstonedPlayer1.png")){
        std::cout << "Failed to load penis warrior texture.\n";
        this->gameWindow->close();
    }

    if(!this->beamTexture.loadFromFile("images/CUMbeam.png")){
        std::cout << "Failed to load beam texture.\n";
        this->gameWindow->close();
    }

    if(!this->pauseFont.loadFromFile("fonts/ALGER.TTF")){
        std::cout << "Error loading pause font.\n";
        this->gameWindow->close();
    }

    if(!this->pauseMusic.openFromFile("Music/WinstonPauseMenuMusic.wav")){
        std::cout << "Error loading pause music.\n";
    }


    //Pause Text
    this->pauseText.setFont(pauseFont);
    this->pauseText.setString("Paused... Left Click to continue.");
    this->pauseText.setCharacterSize(40);
    this->pauseText.setFillColor(sf::Color::White);
    this->pauseText.setStyle(sf::Text::Bold || sf::Text::Underlined);
    this->pauseText.setPosition(this->gameWindow->getSize().x / 2, this->gameWindow->getSize().y / 2);
    this->pauseText.setOrigin(this->pauseText.getLocalBounds().width / 2, this->pauseText.getLocalBounds().height / 2);
    
    //Win Text
    this->winText.setFont(pauseFont);
    this->winText.setString(" ");
    this->winText.setCharacterSize(30);
    this->winText.setFillColor(sf::Color::White);
    this->winText.setStyle(sf::Text::Bold || sf::Text::Underlined);
    this->winText.setPosition(120, this->gameWindow->getSize().y / 2.f);
    
    //Pacifist win Text
    this->pacifistWinText.setFont(pauseFont);
    this->pacifistWinText.setString(" ");
    this->pacifistWinText.setCharacterSize(30);
    this->pacifistWinText.setFillColor(sf::Color::White);
    this->pacifistWinText.setStyle(sf::Text::Bold || sf::Text::Underlined);
    this->pacifistWinText.setPosition(10, this->gameWindow->getSize().y / 2);

    std::cout << "Textures sucessfully loaded.\n";

}

void GameEngine::initSprites() {
    std:: cout << "Initializing Sprites... ";

    std::srand(std::time(nullptr));
    //Initialize game variables
    this->animationCounter = 0;
    this->displayFirstAnimation = true;
    this->isBeamPresent = false;
    this->isCheaterBeamPresent = false;
    this->beamCollisionType =  BeamCollisionType::nan;
    this->centipedesKilled = 0;

    //Initialze player variables
    this->menuPtr->is_CheaterBeam_Unlocked = true;
    this->sessionPoints = 0;


    //Centipedes
    int numCentipedes = -1;
    for(int i = 0; i < NUM_CENTIPEDE; i++){
        this->centipedeVector.push_back(Centipede(this->centipedeTexture, (i*50)+25 , 25 ));
        centipedeVector[++numCentipedes].centipedeSprite.scale(0.7, 0.7);
    }

    //Mushrooms
    int numShrooms = -1;
    for(int i = 1; i < (this->gameWindow->getSize().x / 50) - 1; i++) {
        for(int j = 1; j < 13; j++) {
            int rng = (rand() % 100) + 1;
            if(rng > 89){ 
                this->mushroomVector.push_back(Mushroom(this->mushroomTexture4, i*50, j*50));
                mushroomVector[++numShrooms].mushroomSprite.scale(0.9, 0.9);
            }
        }
    }

    //Player
    this->player1 = new Player(this->playerTexture, this->gameWindow->getSize().x / 2, this->gameWindow->getSize().y - 50 );
    this->player1->playerSprite.setOrigin(this->player1->playerSprite.getLocalBounds().width / 2, this->player1->playerSprite.getLocalBounds().height / 2);
    
    std::cout << "Sprite intialization completed.\n";
}

void GameEngine::update(){

    //Update Player Movement
    sf::Vector2f mousePosition = gameWindow->mapPixelToCoords(sf::Mouse::getPosition(*gameWindow)); // MOUSE POSITION
    this->player1->updateMovement(mousePosition, gameWindow);

    //update centipede movement
    for(int i = 0; i < this->centipedeVector.size(); i++){
        this->centipedeVector[i].updateMovement(this->mushroomVector, this->centipedeVector, gameWindow);
    }    

    //Event Polling for player input
    while (this->gameWindow->pollEvent(this->event)) {
    
        switch(this->event.type){
            case sf::Event::Closed: //Close Game
            this->menuPtr->playerPoints += this->sessionPoints;
                this->menuPtr->currentGameType = NULL_GAME;
                return;

            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { //Shoot
                    if(!isBeamPresent){
                        this->playerBeam = new Beam(this->beamTexture, this->player1, this->player1->playerSprite.getGlobalBounds().left + (this->player1->playerSprite.getGlobalBounds().width / 2), this->player1->playerSprite.getGlobalBounds().top + (this->player1->playerSprite.getGlobalBounds().height / 2));
                        this->playerBeam->beamSprite.setScale(1,.5);
                        isBeamPresent = true;
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { //Pause
                    this->menuPtr->menuMusic.pause();
                    this->gameWindow->clear(sf::Color::Black);
                    this->gameWindow->draw(pauseText);
                    this->gameWindow->display();

                    this->pauseMusic.setVolume(120);
                    this->pauseMusic.setPitch(1);
                    this->pauseMusic.setLoop(true);
                    this->pauseMusic.play();
                    while(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    }
                    this->pauseMusic.pause();
                    this->menuPtr->menuMusic.play();
                    break;
                } 
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) { //Cheater beam
                    if(!isCheaterBeamPresent && menuPtr->is_CheaterBeam_Unlocked){
                        if (this->centipedeVector[0].isMovingDown) {
                            this->cheaterBeam = new Beam(this->beamTexture, this->player1,(this->centipedeVector[0].centipedeSprite.getPosition().x), 700);
                            this->isCheaterBeamPresent = true;
                        } else if (this->centipedeVector[0].isMovingRight) {
                            int xPlayer = (this->centipedeVector[0].centipedeSprite.getPosition().x) + ((0.1/0.8) * (700 - this->centipedeVector[0].centipedeSprite.getPosition().y));
                            if(xPlayer < 0){
                                this->cheaterBeam = new Beam(this->beamTexture, this->player1, xPlayer * -1, 700);
                                this->isCheaterBeamPresent = true;
                            } else if (xPlayer > this->gameWindow->getSize().x) {
                                this->cheaterBeam = new Beam(this->beamTexture, this->player1, (2 * this->gameWindow->getSize().x) - xPlayer, 700);
                                this->isCheaterBeamPresent = true;
                            } else {
                                this->cheaterBeam = new Beam(this->beamTexture, this->player1, xPlayer, 700);
                                this->isCheaterBeamPresent = true;
                            }
                        } else {
                            this->cheaterBeam = new Beam(this->beamTexture, this->player1, (this->centipedeVector[0].centipedeSprite.getPosition().x) - ((0.1/0.8) * (700 - this->centipedeVector[0].centipedeSprite.getPosition().y)), 700);
                            this->isCheaterBeamPresent = true;
                        }
                    }
                }
        }
    }

    // Check Player collision with centipedes
    for(int i = 0; i < centipedeVector.size(); i++){ 
        if(this->player1->playerSprite.getGlobalBounds().intersects(this->centipedeVector[i].centipedeSprite.getGlobalBounds())){
            std::stringstream os;
            os << std::fixed << std::setprecision(2) << this->sessionPoints;
            winText.setString("You died. " + os.str() + " points added.\nLMB to continue." );
            displayWinScreen(winText);
            this->menuPtr->playerPoints += this->sessionPoints * 0.85;
            this->menuPtr->currentGameType = NULL_GAME;
        }
    }

    // update beams movement if one is present
    
    if(isCheaterBeamPresent){
        this->cheaterBeamCollisionType = cheaterBeam->updateMovement(this->isCheaterBeamPresent, this->mushroomVector, this->centipedeVector, this->cheaterBeamCollisionIndex);
        //handle cheater beam collision types appropriately
        if(this->cheaterBeamCollisionType == BeamCollisionType::centipede){ //Create shroom at position of collision, and pop off dead centipede
            mushroomVector.push_back(Mushroom(mushroomTexture4, centipedeVector[cheaterBeamCollisionIndex].centipedeSprite.getPosition().x, centipedeVector[cheaterBeamCollisionIndex].centipedeSprite.getPosition().y, true));
            Centipede tempCentipede = centipedeVector[cheaterBeamCollisionIndex];
            centipedeVector[cheaterBeamCollisionIndex] = centipedeVector[centipedeVector.size()-1];
            centipedeVector[centipedeVector.size()-1] = tempCentipede;
            centipedeVector.pop_back();
            this->sessionPoints += 20 * this->menuPtr->centipedeGameMultiplier;
            this->centipedesKilled++;
            delete this->cheaterBeam;

        } else if(this->cheaterBeamCollisionType == BeamCollisionType::mushroom){ // damage mushroom and pop off 
            mushroomVector[cheaterBeamCollisionIndex].health = 0;
            //mushroomVector[cheaterBeamCollisionIndex].damageMushroom(mushroomTexture4, mushroomTexture3, mushroomTexture2, mushroomTexture1);
            if(mushroomVector[cheaterBeamCollisionIndex].health < 1){
                Mushroom tempMushroom = mushroomVector[cheaterBeamCollisionIndex];
                mushroomVector[cheaterBeamCollisionIndex] = mushroomVector[mushroomVector.size()-1];
                mushroomVector[mushroomVector.size()-1] = tempMushroom;
                this->sessionPoints += 5 * this->menuPtr->centipedeGameMultiplier;
                mushroomVector.pop_back();
            }
            delete this->cheaterBeam;
        } else if (this->cheaterBeamCollisionType == BeamCollisionType::boundary){
            delete this->cheaterBeam;
        }
    }

    if(isBeamPresent){
        this->beamCollisionType = playerBeam->updateMovement(this->isBeamPresent, this->mushroomVector, this->centipedeVector, this->beamCollisionIndex);
        //handle beam collision types appropriately
        if(this->beamCollisionType == BeamCollisionType::centipede){ //Create shroom at position of collision, and pop off dead centipede
            mushroomVector.push_back(Mushroom(mushroomTexture4, centipedeVector[beamCollisionIndex].centipedeSprite.getPosition().x, centipedeVector[beamCollisionIndex].centipedeSprite.getPosition().y, true));
            Centipede tempCentipede = centipedeVector[beamCollisionIndex];
            centipedeVector[beamCollisionIndex] = centipedeVector[centipedeVector.size()-1];
            centipedeVector[centipedeVector.size()-1] = tempCentipede;
            centipedeVector.pop_back();
            this->sessionPoints += 20 * this->menuPtr->centipedeGameMultiplier;
            this->centipedesKilled++;
            delete this->playerBeam;

        } else if(this->beamCollisionType == BeamCollisionType::mushroom){ // damage mushroom and pop off 
            mushroomVector[beamCollisionIndex].damageMushroom(mushroomTexture4, mushroomTexture3, mushroomTexture2, mushroomTexture1);
            if(mushroomVector[beamCollisionIndex].health < 1){
                Mushroom tempMushroom = mushroomVector[beamCollisionIndex];
                mushroomVector[beamCollisionIndex] = mushroomVector[mushroomVector.size()-1];
                mushroomVector[mushroomVector.size()-1] = tempMushroom;
                this->sessionPoints += 5 * this->menuPtr->centipedeGameMultiplier;
                mushroomVector.pop_back();
            }
            delete this->playerBeam;
        } else if (this->beamCollisionType == BeamCollisionType::boundary){
            delete this->playerBeam;
        }
    }

    // Default Win condition
    if(centipedeVector.size() <= 0){
        std::stringstream os;
        os << std::fixed << std::setprecision(2) << this->sessionPoints;
        winText.setString("Game won. " + os.str() + " points added.\nLMB to continue." );
        displayWinScreen(winText);
        this->menuPtr->playerPoints += this->sessionPoints;
        this->menuPtr->currentGameType = NULL_GAME;
        return;
    }

    // Pacifist Win Condition
    if(centipedesKilled == 0 && this->mushroomVector.size() <= 0){
        this->sessionPoints += (NUM_CENTIPEDE * 40);
        this->sessionPoints *= 10;
        std::stringstream os;
        os << std::fixed << std::setprecision(2) << this->sessionPoints;
        pacifistWinText.setString("Game won Mahatma Ghandi Style.\n" + os.str() + " points added.\nLMB to continue." );
        displayWinScreen(pacifistWinText);
        this->menuPtr->playerPoints += this->sessionPoints;
        this->menuPtr->currentGameType = NULL_GAME;
        return;
    }
}

void GameEngine::render(){
    // Clear Screen
    this->gameWindow->clear(sf::Color::Black);
    
    // render centipedes
    for(int i = 0; i < this->centipedeVector.size(); i++){
        if(this->displayFirstAnimation){
            this->centipedeVector[i].centipedeSprite.setTexture(this->centipedeTexture);
            if(this->animationCounter % 500 == 0){
                this->displayFirstAnimation = !(this->displayFirstAnimation);
            }
        } else {
            this->centipedeVector[i].centipedeSprite.setTexture(this->centipedeTexture2);
            if(this->animationCounter % 500 == 0){
                this->displayFirstAnimation = !(this->displayFirstAnimation);
            }
        }
        this->gameWindow->draw(this->centipedeVector[i].centipedeSprite);
    }

    // render mushrooms
    for(int j = 0; j < this->mushroomVector.size(); j++){
        this->gameWindow->draw(this->mushroomVector[j].mushroomSprite);
    }

    // render player
    this->gameWindow->draw(player1->playerSprite);

    // render beams
    if(isBeamPresent){
        this->gameWindow->draw(playerBeam->beamSprite);
    }

    if(isCheaterBeamPresent) {
        this->gameWindow->draw(cheaterBeam->beamSprite);
    }
    
    // Display screem
    this->gameWindow->display();

    // Increment Animation Counter
    animationCounter++;
}

void GameEngine::displayWinScreen(sf::Text &text){
    this->gameWindow->clear(sf::Color::Black);
    this->gameWindow->draw(text);
    this->gameWindow->display();
    while(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->animationCounter % 500 == 0) {
            text.rotate(0.001);
            this->gameWindow->draw(text);
            this->gameWindow->display();
            this->animationCounter++;
        }
    }
}