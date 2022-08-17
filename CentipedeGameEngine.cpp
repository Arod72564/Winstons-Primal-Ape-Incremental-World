#include "CentipedeGameEngine.h"

#define NUM_CENTIPEDE 10


CentipedeGameEngine::CentipedeGameEngine(){
    initWindow();
    initTextures();
    initSprites();
}

CentipedeGameEngine::CentipedeGameEngine(MenuScreen *menu){
    menuPtr = menu;
    gameWindow = menu->menuScreen;
    initWindow2();
    initTextures();
    initSprites();
}

CentipedeGameEngine::~CentipedeGameEngine(){
    sf::Vector2u tempVec(800,800);
    gameWindow->setSize(tempVec);
    delete player1;
}

void CentipedeGameEngine::initWindow(){
    videoMode.height = WINDOW_HEIGHT;
    videoMode.width = WINDOW_WIDTH;
    gameWindow = new sf::RenderWindow(videoMode, "Centipede", sf::Style::Titlebar | sf::Style::Close);
    std::cout << "Centipede Game window sucessfully set up.\n";
}

void CentipedeGameEngine::initWindow2(){
    sf::Vector2u tempVec(800,800);
    gameWindow->setSize(tempVec);
    std::cout << "Centipede Game window sucessfully set up.\n";
}

void CentipedeGameEngine::initTextures() {
    std::cout << "Loading textures... ";

    if(!centipedeTexture.loadFromFile("images/Centipede/winstonpede_right1.png")){
        std::cout << "Failed to load centipede texture 1.\n";
        gameWindow->close();
    }

    if(!centipedeTexture2.loadFromFile("images/Centipede/winstonpede_right2.png")){
        std::cout << "Failed to load centipede textures 2.\n";
        gameWindow->close();
    }

    if(!mushroomTexture4.loadFromFile("images/Centipede/Winston4.png")){
        std::cout << "Failed to load mushroom texture 4.\n";
        gameWindow->close();
    }

    if(!mushroomTexture3.loadFromFile("images/Centipede/Winston3.png")){
        std::cout << "Failed to load mushroom texture 3.\n";
        gameWindow->close();
    }

    if(!mushroomTexture2.loadFromFile("images/Centipede/Winston2.png")){
        std::cout << "Failed to load mushroom texture 2.\n";
        gameWindow->close();
    }

    if(!mushroomTexture1.loadFromFile("images/Centipede/Winston1.png")){
        std::cout << "Failed to load mushroom texture 1.\n";
        gameWindow->close();
    }

    if(!playerTexture.loadFromFile("images/Centipede/WinstonedPlayer1.png")){
        std::cout << "Failed to load penis warrior texture.\n";
        gameWindow->close();
    }

    if(!beamTexture.loadFromFile("images/Centipede/CUMbeam.png")){
        std::cout << "Failed to load beam texture.\n";
        gameWindow->close();
    }

    if(!pauseFont.loadFromFile("fonts/ALGER.TTF")){
        std::cout << "Error loading pause font.\n";
        gameWindow->close();
    }

    if(!pauseMusic.openFromFile("Music/WinstonPauseMenuMusic.wav")){
        std::cout << "Error loading pause music.\n";
    }


    //Pause Text
    pauseText.setFont(pauseFont);
    pauseText.setString("Paused... Left Click to continue.");
    pauseText.setCharacterSize(40);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold || sf::Text::Underlined);
    pauseText.setPosition(gameWindow->getSize().x / 2, gameWindow->getSize().y / 2);
    pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);
    
    //Win Text
    winText.setFont(pauseFont);
    winText.setString(" ");
    winText.setCharacterSize(30);
    winText.setFillColor(sf::Color::White);
    winText.setStyle(sf::Text::Bold || sf::Text::Underlined);
    winText.setPosition(120, gameWindow->getSize().y / 2.f);
    
    //Pacifist win Text
    pacifistWinText.setFont(pauseFont);
    pacifistWinText.setString(" ");
    pacifistWinText.setCharacterSize(30);
    pacifistWinText.setFillColor(sf::Color::White);
    pacifistWinText.setStyle(sf::Text::Bold || sf::Text::Underlined);
    pacifistWinText.setPosition(10, gameWindow->getSize().y / 2);

    std::cout << "Textures sucessfully loaded.\n";

}

void CentipedeGameEngine::initSprites() {
    std:: cout << "Initializing Sprites... ";

    //Initialize game variables
    std::srand(std::time(nullptr));
    animationCounter = 0;
    displayFirstAnimation = true;
    isBeamPresent = false;
    isCheaterBeamPresent = false;
    beamCollisionType = BeamCollisionType::nan_;
    centipedesKilled = 0;
    isPaused = false;

    //Initialze player variables
    sessionPoints = 0;

    //Centipedes
    int numCentipedes = -1;
    for(int i = 0; i < NUM_CENTIPEDE; i++){
        centipedeVector.push_back(Centipede(centipedeTexture, (i*50)+25 , 25 ));
        centipedeVector[++numCentipedes].centipedeSprite.scale(0.7, 0.7);
    }

    //Mushrooms
    int numShrooms = -1;
    for(int i = 1; i < (gameWindow->getSize().x / 50) - 1; i++) {
        for(int j = 1; j < 13; j++) {
            int rng = (rand() % 100) + 1;
            if(rng > 89){ 
                mushroomVector.push_back(Mushroom(mushroomTexture4, i*50, j*50));
                mushroomVector[++numShrooms].mushroomSprite.scale(0.9, 0.9);
            }
        }
    }

    //Player
    player1 = new Player(playerTexture, gameWindow->getSize().x / 2, gameWindow->getSize().y - 50 );
    player1->playerSprite.setOrigin(player1->playerSprite.getLocalBounds().width / 2, player1->playerSprite.getLocalBounds().height / 2);
    
    std::cout << "Sprite intialization completed.\n";
}

void CentipedeGameEngine::update(){

    //Update Player Movement
    sf::Vector2f mousePosition = gameWindow->mapPixelToCoords(sf::Mouse::getPosition(*gameWindow)); // MOUSE POSITION
    player1->updateMovement(mousePosition, gameWindow);

    //update centipede movement
    for(int i = 0; i < centipedeVector.size(); i++){
        centipedeVector[i].updateMovement(mushroomVector, centipedeVector, gameWindow);
    }    

    //Event Polling for player input
    while (gameWindow->pollEvent(event)) {
    
        switch(event.type){
            case sf::Event::Closed: //Close Game
                menuPtr->playerPoints += sessionPoints;
                menuPtr->currentGameType = NULL_GAME;
                return;
            
            case sf::Event::MouseButtonPressed:
                if (menuPtr->muteButtonSprite.getGlobalBounds().contains(gameWindow->mapPixelToCoords(sf::Mouse::getPosition(*gameWindow)))) {
                    if(menuPtr->is_MenuMusic_Paused){
                        menuPtr->menuMusic.play();
                    } else {
                        menuPtr->menuMusic.pause();
                    }
                    menuPtr->is_MenuMusic_Paused = !(menuPtr->is_MenuMusic_Paused);
                }
                break;

            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { //Shoot
                    if(!isBeamPresent){
                        playerBeam = new Beam(beamTexture, player1, player1->playerSprite.getGlobalBounds().left + (player1->playerSprite.getGlobalBounds().width / 2), player1->playerSprite.getGlobalBounds().top + (player1->playerSprite.getGlobalBounds().height / 2));
                        playerBeam->beamSprite.setScale(1,.5);
                        isBeamPresent = true;
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { //Pause
                    isPaused = true;
                    menuPtr->menuMusic.pause();
                    gameWindow->clear(sf::Color::Black);
                    gameWindow->draw(pauseText);
                    gameWindow->display();

                    pauseMusic.setVolume(120);
                    pauseMusic.setPitch(1);
                    pauseMusic.setLoop(true);
                    pauseMusic.play();
                    
                    while (isPaused == true) {
                        while (gameWindow->pollEvent(event)) {
                            switch (event.type) {
                                case sf::Event::MouseButtonPressed:
                                    isPaused = false;
                                    break;
                                
                                default:
                                    break;
                            }
                        }
                    }

                    pauseMusic.pause();

                    if (!menuPtr->is_MenuMusic_Paused) {
                        menuPtr->menuMusic.play();
                    }
                    
                    break;
                } 
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) { //Cheater beam
                    if(isCheaterBeamPresent == false && menuPtr->is_CheaterBeam_Unlocked == true) {
                        if (centipedeVector[0].isMovingDown) {
                            cheaterBeam = new Beam(beamTexture, player1,(centipedeVector[0].centipedeSprite.getPosition().x), 700);
                            isCheaterBeamPresent = true;
                        } else if (centipedeVector[0].isMovingRight) {
                            int xPlayer = (centipedeVector[0].centipedeSprite.getPosition().x) + ((CENTIPEDE_SPEED/BEAM_SPEED) * (700 - centipedeVector[0].centipedeSprite.getPosition().y));
                            if(xPlayer < 0){
                                cheaterBeam = new Beam(beamTexture, player1, xPlayer * -1, 700);
                                isCheaterBeamPresent = true;
                            } else if (xPlayer > gameWindow->getSize().x) {
                                cheaterBeam = new Beam(beamTexture, player1, (2 * gameWindow->getSize().x) - xPlayer, 700);
                                isCheaterBeamPresent = true;
                            } else {
                                cheaterBeam = new Beam(beamTexture, player1, xPlayer, 700);
                                isCheaterBeamPresent = true;
                            }
                        } else {
                            cheaterBeam = new Beam(beamTexture, player1, (centipedeVector[0].centipedeSprite.getPosition().x) - ((CENTIPEDE_SPEED/BEAM_SPEED) * (700 - centipedeVector[0].centipedeSprite.getPosition().y)), 700);
                            isCheaterBeamPresent = true;
                        }
                    }
                }
        }
    }

    // Check Player collision with centipedes
    for(int i = 0; i < centipedeVector.size(); i++){ 
        if(player1->playerSprite.getGlobalBounds().intersects(centipedeVector[i].centipedeSprite.getGlobalBounds())){
            std::stringstream os;
            os << std::fixed << std::setprecision(2) << sessionPoints;
            winText.setString("You died. " + os.str() + " points added.\nLMB to continue." );
            displayWinScreen(winText);
            menuPtr->playerPoints += sessionPoints * 0.85;
            menuPtr->currentGameType = NULL_GAME;
        }
    }

    // update beams movement if one is present
    
    if(isCheaterBeamPresent){
        cheaterBeamCollisionType = cheaterBeam->updateMovement(isCheaterBeamPresent, mushroomVector, centipedeVector, cheaterBeamCollisionIndex);
        //handle cheater beam collision types appropriately
        if(cheaterBeamCollisionType == BeamCollisionType::centipede){ //Create shroom at position of collision, and pop off dead centipede
            mushroomVector.push_back(Mushroom(mushroomTexture4, centipedeVector[cheaterBeamCollisionIndex].centipedeSprite.getPosition().x, centipedeVector[cheaterBeamCollisionIndex].centipedeSprite.getPosition().y, true));
            Centipede tempCentipede = centipedeVector[cheaterBeamCollisionIndex];
            centipedeVector[cheaterBeamCollisionIndex] = centipedeVector[centipedeVector.size()-1];
            centipedeVector[centipedeVector.size()-1] = tempCentipede;
            centipedeVector.pop_back();
            sessionPoints += 20 * menuPtr->centipedeGameMultiplier;
            centipedesKilled++;
            delete cheaterBeam;

        } else if(cheaterBeamCollisionType == BeamCollisionType::mushroom){ // damage mushroom and pop off 
            mushroomVector[cheaterBeamCollisionIndex].health = 0;
            //mushroomVector[cheaterBeamCollisionIndex].damageMushroom(mushroomTexture4, mushroomTexture3, mushroomTexture2, mushroomTexture1);
            if(mushroomVector[cheaterBeamCollisionIndex].health < 1){
                Mushroom tempMushroom = mushroomVector[cheaterBeamCollisionIndex];
                mushroomVector[cheaterBeamCollisionIndex] = mushroomVector[mushroomVector.size()-1];
                mushroomVector[mushroomVector.size()-1] = tempMushroom;
                sessionPoints += 5 * menuPtr->centipedeGameMultiplier;
                mushroomVector.pop_back();
            }
            delete cheaterBeam;
        } else if (cheaterBeamCollisionType == BeamCollisionType::boundary){
            delete cheaterBeam;
        }
    }

    if(isBeamPresent){
        beamCollisionType = playerBeam->updateMovement(isBeamPresent, mushroomVector, centipedeVector, beamCollisionIndex);
        //handle beam collision types appropriately
        if(beamCollisionType == BeamCollisionType::centipede){ //Create shroom at position of collision, and pop off dead centipede
            mushroomVector.push_back(Mushroom(mushroomTexture4, centipedeVector[beamCollisionIndex].centipedeSprite.getPosition().x, centipedeVector[beamCollisionIndex].centipedeSprite.getPosition().y, true));
            Centipede tempCentipede = centipedeVector[beamCollisionIndex];
            centipedeVector[beamCollisionIndex] = centipedeVector[centipedeVector.size()-1];
            centipedeVector[centipedeVector.size()-1] = tempCentipede;
            centipedeVector.pop_back();
            sessionPoints += 20 * menuPtr->centipedeGameMultiplier;
            centipedesKilled++;
            delete playerBeam;

        } else if(beamCollisionType == BeamCollisionType::mushroom){ // damage mushroom and pop off 
            mushroomVector[beamCollisionIndex].damageMushroom(mushroomTexture4, mushroomTexture3, mushroomTexture2, mushroomTexture1);
            if(mushroomVector[beamCollisionIndex].health < 1){
                Mushroom tempMushroom = mushroomVector[beamCollisionIndex];
                mushroomVector[beamCollisionIndex] = mushroomVector[mushroomVector.size()-1];
                mushroomVector[mushroomVector.size()-1] = tempMushroom;
                sessionPoints += 5 * menuPtr->centipedeGameMultiplier;
                mushroomVector.pop_back();
            }
            delete playerBeam;
        } else if (beamCollisionType == BeamCollisionType::boundary){
            delete playerBeam;
        }
    }

    // Default Win condition
    if(centipedeVector.size() <= 0){
        std::stringstream os;
        os << std::fixed << std::setprecision(2) << sessionPoints;
        winText.setString("Game won. " + os.str() + " points added.\nLMB to continue." );
        displayWinScreen(winText);
        menuPtr->playerPoints += sessionPoints;
        menuPtr->currentGameType = NULL_GAME;
        return;
    }

    // Pacifist Win Condition
    if(centipedesKilled == 0 && mushroomVector.size() <= 0){
        sessionPoints += (NUM_CENTIPEDE * 40);
        sessionPoints *= 10;
        std::stringstream os;
        os << std::fixed << std::setprecision(2) << sessionPoints;
        pacifistWinText.setString("Game won Mahatma Ghandi Style.\n" + os.str() + " points added.\nLMB to continue." );
        displayWinScreen(pacifistWinText);
        menuPtr->playerPoints += sessionPoints;
        menuPtr->currentGameType = NULL_GAME;
        return;
    }

    if (menuPtr->menuMusic.getStatus() == sf::SoundSource::Stopped) { menuPtr->nextSong(); }
}

void CentipedeGameEngine::render(){
    // Clear Screen
    gameWindow->clear(sf::Color::Black);

    gameWindow->draw(menuPtr->muteButtonSprite);
    
    // render centipedes
    for(int i = 0; i < centipedeVector.size(); i++){
        if(displayFirstAnimation){
            centipedeVector[i].centipedeSprite.setTexture(centipedeTexture);
            if(animationCounter % 500 == 0){
                displayFirstAnimation = !(displayFirstAnimation);
            }
        } else {
            centipedeVector[i].centipedeSprite.setTexture(centipedeTexture2);
            if(animationCounter % 500 == 0){
                displayFirstAnimation = !(displayFirstAnimation);
            }
        }
        gameWindow->draw(centipedeVector[i].centipedeSprite);
    }

    // render mushrooms
    for(int j = 0; j < mushroomVector.size(); j++){
        gameWindow->draw(mushroomVector[j].mushroomSprite);
    }

    // render player
    gameWindow->draw(player1->playerSprite);

    // render beams
    if(isBeamPresent){
        gameWindow->draw(playerBeam->beamSprite);
    }

    if(isCheaterBeamPresent) {
        gameWindow->draw(cheaterBeam->beamSprite);
    }
    
    // Display screem
    gameWindow->display();

    // Increment Animation Counter
    animationCounter++;
}

void CentipedeGameEngine::displayWinScreen(sf::Text &text){
    gameWindow->clear(sf::Color::Black);
    gameWindow->draw(text);
    gameWindow->display();
    while(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (animationCounter % 500 == 0) {
            text.rotate(0.001);
            gameWindow->draw(text);
            gameWindow->display();
            animationCounter++;
        }
    }
}