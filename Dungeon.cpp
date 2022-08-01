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

    //Constant textures
    sf::Texture moveTexture1;
    if(!moveTexture1.loadFromFile("images/Dungeon/MoveLocked.png")) menuPtr->menuScreen->close();
    sf::Texture moveTexture2;
    if(!moveTexture2.loadFromFile("images/Dungeon/Move.png")) menuPtr->menuScreen->close();
    sf::Texture ansTexture;
    if(!ansTexture.loadFromFile("images/Dungeon.answerPrompt.png")) menuPtr->menuScreen->close();
    sf::Texture puzzleClue;
    if(!puzzleClue.loadFromFile("images/DungeonPuzzleClue.png")) menuPtr->menuScreen->close();
    sf::Texture clue1;
    if(!clue1.loadFromFile("images/Dungeon/Clue1.png")) menuPtr->menuScreen->close();
    sf::Texture clue2;
    if(!clue2.loadFromFile("images/Dungeon/Clue2.png")) menuPtr->menuScreen->close();
    sf::Texture clue3;
    if(!clue3.loadFromFile("images/Dungeon/Clue3.png")) menuPtr->menuScreen->close();
    sf::Texture clue4;
    if(!clue4.loadFromFile("images/Dungeon/Clue1_Unlocked.png")) menuPtr->menuScreen->close();
    sf::Texture clue5;
    if(!clue5.loadFromFile("images/Dungeon/Clue2_Unlocked.png")) menuPtr->menuScreen->close();
    sf::Texture clue6;
    if(!clue6.loadFromFile("images/Dungeon/Clue3_Unlocked.png")) menuPtr->menuScreen->close();

    //Variable used as index to current room
    roomCount = 0;

    //Front door
    DungeonRoom room_0;
    room_0.roomId = 0;
    room_0.roomAnswer = "slander";
    room_0.isPuzzleSolved = false;

    for(int i = 0; i < 6; i ++){
        room_0.textureVec.push_back(sf::Texture());
        room_0.spriteVec.push_back(sf::Sprite());
        room_0.clueSpriteVec.push_back(sf::Sprite());
    }

        //Background
    if(!room_0.backgroundTexture.loadFromFile("images/Dungeon/Room0/Room_0.png")){
        std::cout << "Room 0 background failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_0.backgroundSprite.setTexture(room_0.backgroundTexture);
    room_0.backgroundSprite.setPosition(0,0);

        //Puzzle
    if(!room_0.textureVec[0].loadFromFile("images/Dungeon/Room0/Puzzle0.png")) {
        std::cout << "R0.0 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_0.spriteVec[0].setTexture(room_0.textureVec[0]);

        //Clue1
    if(!room_0.textureVec[1].loadFromFile("images/Dungeon/Room0/Puzzle0_clue1.png")) {
        std::cout << "R0.1 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_0.spriteVec[1].setTexture(room_0.textureVec[1]);

        //Clue2
    if(!room_0.textureVec[2].loadFromFile("images/Dungeon/Room0/Puzzle0_clue1.png")) {
        std::cout << "R0.2 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_0.spriteVec[2].setTexture(room_0.textureVec[2]);

        //Clue3
    if(!room_0.textureVec[3].loadFromFile("images/Dungeon/Room0/Puzzle0_clue1.png")) {
        std::cout << "R0.3 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_0.spriteVec[3].setTexture(room_0.textureVec[3]);

        //Forward
    room_0.spriteVec[4].setTexture(moveTexture1);

        //Back
    room_0.spriteVec[5].setTexture(moveTexture2);

        //Answer Prompt
    room_0.spriteVec[6].setTexture(ansTexture);

        //ClueVector
    room_0.clueSpriteVec[0].setTexture(clue1);

    room_0.clueSpriteVec[1].setTexture(clue2);

    room_0.clueSpriteVec[2].setTexture(clue3);

    room_0.clueSpriteVec[3].setTexture(clue4);

    room_0.clueSpriteVec[4].setTexture(clue5);

    room_0.clueSpriteVec[5].setTexture(clue6);

        //Puzzle sprite
    room_0.clueSpriteVec[6].setTexture(puzzleClue);




    //First Room
    DungeonRoom room_1;
    room_1.roomId = 1;
    room_1.roomAnswer = "poopingonbiggay";
    room_1.isPuzzleSolved = false;

    for(int i = 0; i < 6; i ++){
        room_1.textureVec.push_back(sf::Texture());
        room_1.spriteVec.push_back(sf::Sprite());
        room_1.clueSpriteVec.push_back(sf::Sprite());
    }

        //Background
    if(!room_1.backgroundTexture.loadFromFile("images/Dungeon/Room1/Room_1.png")){
        std::cout << "Room 1 background failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_1.backgroundSprite.setTexture(room_1.backgroundTexture);
    room_1.backgroundSprite.setPosition(0,0);

        //Puzzle
    if(!room_1.textureVec[0].loadFromFile("images/Dungeon/Room1/Puzzle1.png")) {
        std::cout << "R1.0 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_1.spriteVec[0].setTexture(room_1.textureVec[0]);

        //Clue1
    if(!room_1.textureVec[1].loadFromFile("images/Dungeon/Room1/Puzzle1_clue1.png")) {
        std::cout << "R1.1 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_1.spriteVec[1].setTexture(room_1.textureVec[1]);

        //Clue2
    if(!room_1.textureVec[2].loadFromFile("images/Dungeon/Room1/Puzzle1_clue1.png")) {
        std::cout << "R1.2 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_1.spriteVec[2].setTexture(room_1.textureVec[2]);

        //Clue3
    if(!room_1.textureVec[3].loadFromFile("images/Dungeon/Room1/Puzzle1_clue1.png")) {
        std::cout << "R1.3 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    room_1.spriteVec[3].setTexture(room_1.textureVec[3]);

        //Forward
    room_1.spriteVec[4].setTexture(moveTexture1);

        //Back
    room_1.spriteVec[5].setTexture(moveTexture2);

        //Answer Prompt
    room_1.spriteVec[6].setTexture(ansTexture);

        //ClueVector
    room_1.clueSpriteVec[0].setTexture(clue1);

    room_1.clueSpriteVec[1].setTexture(clue2);

    room_1.clueSpriteVec[2].setTexture(clue3);

    room_1.clueSpriteVec[3].setTexture(clue4);

    room_1.clueSpriteVec[4].setTexture(clue5);

    room_1.clueSpriteVec[5].setTexture(clue6);

        //Puzzle sprite
    room_1.clueSpriteVec[6].setTexture(puzzleClue);
    



    /**
     * Push all rooms to roomVec in reverse order
     * to preserve correct order relative to vector indices
    */
    roomVec.push_back(room_1);
    roomVec.push_back(room_0);

}

void Dungeon::update(){

    sf::Vector2f mousePosition = menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen));

    while(menuPtr->menuScreen->pollEvent(ev)){
        switch(ev.type){
            case sf::Event::MouseButtonPressed:

                if(roomVec[roomCount].clueSpriteVec[6].getGlobalBounds().contains(mousePosition)) { //Puzzle
                    //Display Puzzle
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[0]);
                } else if (roomVec[roomCount].clueSpriteVec[0].getGlobalBounds().contains(mousePosition)) { //Clue 1
                    //Display Clue 1
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[1]);
                } else if (roomVec[roomCount].clueSpriteVec[1].getGlobalBounds().contains(mousePosition)) { //Clue 2
                    //Display Clue 2
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[2]);
                } else if (roomVec[roomCount].clueSpriteVec[2].getGlobalBounds().contains(mousePosition)) { //Clue 3
                    //Display Clue 3
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[3]);
                } else if (roomVec[roomCount].spriteVec[4].getGlobalBounds().contains(mousePosition)) { //Forward arrow
                    //Move forward a room
                    if(roomVec[roomCount].isPuzzleSolved){
                        roomCount = clamp(roomCount+1, 0, int( roomVec.size() - 1 ));
                    } else {
                        std::cout << "You cannot move forward without solving the puzzle first.\n";
                        displayAnswerPrompt(roomVec[roomCount].spriteVec[6], roomVec[roomCount].roomAnswer);
                    }
                } else if (roomVec[roomCount].spriteVec[5].getGlobalBounds().contains(mousePosition)) { //Back arrow
                    //Move backwards a room
                    roomCount = clamp(roomCount-1, 0, int( roomVec.size() - 1 ));
                } else if (roomVec[roomCount].clueSpriteVec[3].getGlobalBounds().contains(mousePosition)) { //Clue 1 unlocked
                    //Display Clue 1
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[1]);
                } else if (roomVec[roomCount].clueSpriteVec[4].getGlobalBounds().contains(mousePosition)) { //Clue 2 unlocked
                    //Display Clue 2
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[2]);
                } else if (roomVec[roomCount].clueSpriteVec[5].getGlobalBounds().contains(mousePosition)) { //Clue 3 unlocked
                    //Display Clue 3
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[3]);
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
    std::cout << "Type your answer and press enter: ";
    std::cin >> answer;
    if (answerString.compare(answer) == 0) {
        std::cout << "\nCorrect Answer.\n";
    } else {
        std::cout << "\nIncorrect Answer.\n";
    }

}