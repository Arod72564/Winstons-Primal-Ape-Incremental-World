#include "Dungeon.h"    

Dungeon::Dungeon(){

}

Dungeon::Dungeon(MenuScreen* menu){
    menuPtr = menu;
    initRooms();
}

Dungeon::~Dungeon(){

}

void Dungeon::initRooms(){
    roomCount = 0;

    //Front door
    DungeonRoom room_0;
    room_0.roomId = 0;
        //Background
    if(!room_0.backgroundTexture.loadFromFile("images/Dungeon/Room_0.png")){
        std::cout << "Room 1 background failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_0.backgroundSprite.setTexture(room_0.backgroundTexture);
    room_0.backgroundSprite.setPosition(0,0);
        //Puzzle
        //Clue1
        //Clue2
        //Clue3
        //AnswerPrompt
        //Forward
    if(!room_0.textureVec[5].loadFromFile("images/Dungeon/MoveLocked.png")) {
        std::cout << "R0.5: Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_0.spriteVec[5].setTexture(room_0.textureVec[5]);
    
        //Back
    if(!room_0.textureVec[6].loadFromFile("images/Dungeon/Move.png")) {
        std::cout << "R0.6: Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    roomVec.push_back(room_0);

    //First Room
    DungeonRoom room_1;
    room_1.roomId = 1;
        //Background
    if(!room_1.backgroundTexture.loadFromFile("images/Dungeon/Room_1.png")){
        std::cout << "Room 2 background failed to load.\n";
    }
    room_1.backgroundSprite.setTexture(room_1.backgroundTexture);
    room_1.backgroundSprite.setPosition(0,0);
        //Puzzle
        //Clue1
        //Clue2
        //Clue3
        //AnswerPrompt
        //Forward
    if(!room_1.textureVec[5].loadFromFile("images/Dungeon/MoveLocked.png")) {
        std::cout << "R1.5: Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_1.spriteVec[5].setTexture(room_1.textureVec[5]);
    
        //Back
    if(!room_1.textureVec[6].loadFromFile("images/Dungeon/Move.png")) {
        std::cout << "R1.6: Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    roomVec.push_back(room_1);

}

void Dungeon::update(){

    sf::Vector2f mousePosition = menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen));

    while(menuPtr->menuScreen->pollEvent(ev)){
        switch(ev.type){
            case sf::Event::MouseButtonPressed:

                if(roomVec[roomCount].spriteVec[0].getGlobalBounds().contains(mousePosition)) { //Puzzle
                    //Display Puzzle
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[0]);
                } else if (roomVec[roomCount].spriteVec[1].getGlobalBounds().contains(mousePosition)) { //Clue 1
                    //Display Clue 1
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[1]);
                } else if (roomVec[roomCount].spriteVec[2].getGlobalBounds().contains(mousePosition)) { //Clue 2
                    //Display Clue 2
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[2]);
                } else if (roomVec[roomCount].spriteVec[3].getGlobalBounds().contains(mousePosition)) { //Clue 3
                    //Display Clue 3
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[3]);
                } else if (roomVec[roomCount].spriteVec[4].getGlobalBounds().contains(mousePosition)) { //Answer Prompt
                    //Display Answer Prompt
                     displayAnswerPrompt(roomVec[roomCount].spriteVec[4], roomVec[roomCount].roomAnswer);
                } else if (roomVec[roomCount].spriteVec[5].getGlobalBounds().contains(mousePosition)) { //Forward arrow
                    //Move forward a room
                    if(roomVec[roomCount].isPuzzleSolved){
                        roomCount = std::clamp(roomCount+1, 0, int( roomVec.size() ));
                    } else {
                        std::cout << "You cannot move forward without solving the puzzle first.\n";
                    }
                     
                } else if (roomVec[roomCount].spriteVec[6].getGlobalBounds().contains(mousePosition)) { //Back arrow
                    //Move backwards a room
                    roomCount = std::clamp(roomCount-1, 0, int( roomVec.size() ));
                }

                break;
        };
    }
}

void Dungeon::render() {

    menuPtr->menuScreen->clear(sf::Color::Black);

    //Background and room sprites
    menuPtr->menuScreen->draw(roomVec[roomCount].backgroundSprite);
    if(!roomVec[roomCount].spriteVec.empty()){
        for(int i = 0; i < roomVec[roomCount].spriteVec.size(); i++){
            menuPtr->menuScreen->draw(roomVec[roomCount].spriteVec[i]);
        }
    }


    menuPtr->menuScreen->display();
}

void Dungeon::displayPuzzlePrompt(sf::Sprite puzzleSprite) {
    this->menuPtr->menuScreen->draw(puzzleSprite);
    this->menuPtr->menuScreen->display();
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    }
}

void Dungeon::displayAnswerPrompt(sf::Sprite answerSprite, std::string answerString) {
    std::string answer = ""; 

    this->menuPtr->menuScreen->draw(answerSprite);
    this->menuPtr->menuScreen->display();
    std::cout << "Enter your answer: ";
    std::cin >> answer;
    if (answerString.compare(answer) == 0) {
        std::cout << "\nCorrect Answer.\n";
    } else {
        std::cout << "\nIncorrect Answer.\n";
    }

}