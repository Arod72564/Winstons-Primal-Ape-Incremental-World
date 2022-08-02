#include "Dungeon.h"    

Dungeon::Dungeon(){

}

Dungeon::Dungeon(MenuScreen* menu){
    menuPtr = menu;
    initRooms();
}

Dungeon::~Dungeon(){

}

/**
 * TODO: SET POSITION OF EACH SPRITE IN EACH LEVEL
*/
void Dungeon::initRooms(){
    // /**
    //  * Push all rooms to roomVec in reverse order
    //  * to preserve correct order relative to vector indices
    // */


    std:: cout << "Initializing rooms...";

    //Textures used in each level
    if(!moveTexture1.loadFromFile("images/Dungeon/MoveLocked.png")) menuPtr->menuScreen->close();
    if(!moveTexture2.loadFromFile("images/Dungeon/Move.png")) menuPtr->menuScreen->close();
    if(!ansTexture.loadFromFile("images/Dungeon/answerPrompt.png")) menuPtr->menuScreen->close();
    if(!puzzleClue.loadFromFile("images/Dungeon/PuzzleClue.png")) menuPtr->menuScreen->close();
    if(!clue1.loadFromFile("images/Dungeon/Clue1.png")) menuPtr->menuScreen->close();
    if(!clue2.loadFromFile("images/Dungeon/Clue2.png")) menuPtr->menuScreen->close();
    if(!clue3.loadFromFile("images/Dungeon/Clue3.png")) menuPtr->menuScreen->close();
    if(!clue4.loadFromFile("images/Dungeon/Clue1_Unlocked.png")) menuPtr->menuScreen->close();
    if(!clue5.loadFromFile("images/Dungeon/Clue2_Unlocked.png")) menuPtr->menuScreen->close();
    if(!clue6.loadFromFile("images/Dungeon/Clue3_Unlocked.png")) menuPtr->menuScreen->close();

    //Variable used as index to current room
    roomCount = 0;

    //Front door
    DungeonRoom room_0;
    roomVec.push_back(room_0);
    roomVec[0].spriteVec.resize(7);
    roomVec[0].textureVec.resize(4);
    roomVec[0].clueSpriteVec.resize(7);
    roomVec[0].roomId = 0;
    roomVec[0].roomAnswer = "slander";
    roomVec[0].isPuzzleSolved = false;

        //Background
    if(!roomVec[0].backgroundTexture.loadFromFile("images/Dungeon/Room0/Room_0.png")){
        std::cout << "Room 0 background failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    roomVec[0].backgroundSprite.setTexture(roomVec[0].backgroundTexture);
    roomVec[0].backgroundSprite.setPosition(0,0);

        //Puzzle
    if(!roomVec[0].textureVec[0].loadFromFile("images/Dungeon/Room0/Puzzle0.png")) {
        std::cout << "R0.0 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    roomVec[0].spriteVec[0].setTexture(roomVec[0].textureVec[0]);
    roomVec[0].spriteVec[0].setPosition(0, 0);

        //Clue1
    if(!roomVec[0].textureVec[1].loadFromFile("images/Dungeon/Room0/Puzzle0_clue1.png")) {
        std::cout << "R0.1 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    roomVec[0].spriteVec[1].setTexture(roomVec[0].textureVec[1]);
    roomVec[0].spriteVec[1].setPosition(0, 0);

        //Clue2
    if(!roomVec[0].textureVec[2].loadFromFile("images/Dungeon/Room0/Puzzle0_clue2.png")) {
        std::cout << "R0.2 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    roomVec[0].spriteVec[2].setTexture(roomVec[0].textureVec[2]);
    roomVec[0].spriteVec[2].setPosition(0, 0);

        //Clue3
    if(!roomVec[0].textureVec[3].loadFromFile("images/Dungeon/Room0/Puzzle0_clue3.png")) {
        std::cout << "R0.3 Texture failed to load.\n";
        this->menuPtr->menuScreen->close();
    }
    roomVec[0].spriteVec[3].setTexture(roomVec[0].textureVec[3]);
    roomVec[0].spriteVec[3].setPosition(0, 0);

        //Forward
    roomVec[0].spriteVec[4].setTexture(moveTexture1);
    roomVec[0].spriteVec[4].setPosition(0, 0); 

        //Back
    roomVec[0].spriteVec[5].setTexture(moveTexture2);
    roomVec[0].spriteVec[5].setPosition(200, 0); 

        //Answer Prompt
    roomVec[0].spriteVec[6].setTexture(ansTexture);
    roomVec[0].spriteVec[6].setPosition(0, 0); 

        //ClueVector
    roomVec[0].clueSpriteVec[0].setTexture(clue1);
    roomVec[0].clueSpriteVec[0].setPosition(0, 100);

    roomVec[0].clueSpriteVec[1].setTexture(clue2);
    roomVec[0].clueSpriteVec[1].setPosition(0, 200); 

    roomVec[0].clueSpriteVec[2].setTexture(clue3);
    roomVec[0].clueSpriteVec[2].setPosition(0, 300);

    roomVec[0].clueSpriteVec[3].setTexture(clue4);
    roomVec[0].clueSpriteVec[3].setPosition(0, 400); 

    roomVec[0].clueSpriteVec[4].setTexture(clue5);
    roomVec[0].clueSpriteVec[4].setPosition(0, 500); 

    roomVec[0].clueSpriteVec[5].setTexture(clue6);
    roomVec[0].clueSpriteVec[5].setPosition(0, 600); 

        //Puzzle sprite
    roomVec[0].clueSpriteVec[6].setTexture(puzzleClue);
    roomVec[0].clueSpriteVec[6].setPosition(0, 700); 




    //First Room
    // DungeonRoom room_1;
    // roomVec.push_back(room_1);
    // roomVec[1].roomId = 0;
    // roomVec[1].roomAnswer = "slander";
    // roomVec[1].isPuzzleSolved = false;

    //     //Background
    // if(!roomVec[1].backgroundTexture.loadFromFile("images/Dungeon/Room1/Room_1.png")){
    //     std::cout << "Room 1 background failed to load.\n";
    //     this->menuPtr->menuScreen->close();
    // }
    // roomVec[1].backgroundSprite.setTexture(roomVec[1].backgroundTexture);
    // roomVec[1].backgroundSprite.setPosition(0,0);

    //     //Puzzle
    // if(!roomVec[1].textureVec[0].loadFromFile("images/Dungeon/Room1/Puzzle1.png")) {
    //     std::cout << "R1.0 Texture failed to load.\n";
    //     this->menuPtr->menuScreen->close();
    // }
    // roomVec[1].spriteVec[0].setTexture(roomVec[1].textureVec[0]);
    // roomVec[1].spriteVec[0].setPosition(0, 0);

    //     //Clue1
    // if(!roomVec[1].textureVec[1].loadFromFile("images/Dungeon/Room1/Puzzle1_clue1.png")) {
    //     std::cout << "R1.1 Texture failed to load.\n";
    //     this->menuPtr->menuScreen->close();
    // }
    // roomVec[1].spriteVec[1].setTexture(roomVec[1].textureVec[1]);
    // roomVec[1].spriteVec[1].setPosition(0, 0);

    //     //Clue2
    // if(!roomVec[1].textureVec[2].loadFromFile("images/Dungeon/Room1/Puzzle1_clue1.png")) {
    //     std::cout << "R1.2 Texture failed to load.\n";
    //     this->menuPtr->menuScreen->close();
    // }
    // roomVec[1].spriteVec[2].setTexture(roomVec[1].textureVec[2]);
    // roomVec[1].spriteVec[2].setPosition(0, 0);

    //     //Clue3
    // if(!roomVec[1].textureVec[3].loadFromFile("images/Dungeon/Room1/Puzzle1_clue1.png")) {
    //     std::cout << "R1.3 Texture failed to load.\n";
    //     this->menuPtr->menuScreen->close();
    // }
    // roomVec[1].spriteVec[3].setTexture(roomVec[1].textureVec[3]);
    // roomVec[1].spriteVec[3].setPosition(0, 0);

    //     //Forward
    // roomVec[1].spriteVec[4].setTexture(moveTexture1);
    // roomVec[1].spriteVec[4].setPosition(0, 0); 

    //     //Back
    // roomVec[1].spriteVec[5].setTexture(moveTexture2);
    // roomVec[1].spriteVec[5].setPosition(0, 50); 

    //     //Answer Prompt
    // roomVec[1].spriteVec[6].setTexture(ansTexture);
    // roomVec[1].spriteVec[6].setPosition(0, 0); 

    //     //ClueVector
    // roomVec[1].clueSpriteVec[0].setTexture(clue1);
    // roomVec[1].clueSpriteVec[0].setPosition(0, 100); 

    // roomVec[1].clueSpriteVec[1].setTexture(clue2);
    // roomVec[1].clueSpriteVec[1].setPosition(0, 150); 

    // roomVec[1].clueSpriteVec[2].setTexture(clue3);
    // roomVec[1].clueSpriteVec[2].setPosition(0, 200); 

    // roomVec[1].clueSpriteVec[3].setTexture(clue4);
    // roomVec[1].clueSpriteVec[3].setPosition(0, 250); 

    // roomVec[1].clueSpriteVec[4].setTexture(clue5);
    // roomVec[1].clueSpriteVec[4].setPosition(0, 300); 

    // roomVec[1].clueSpriteVec[5].setTexture(clue6);
    // roomVec[1].clueSpriteVec[5].setPosition(0, 350); 

    //     //Puzzle sprite
    // roomVec[1].clueSpriteVec[6].setTexture(puzzleClue);
    // roomVec[1].clueSpriteVec[6].setPosition(0, 400); 
    


    std::cout << "\tRooms initialized.\n";
}

void Dungeon::update(){

    sf::Vector2f mousePosition = menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen));

    while(menuPtr->menuScreen->pollEvent(ev)){
        switch(ev.type){
            case sf::Event::Closed:
                this->menuPtr->currentGameType = NULL_GAME;
                break;

            case sf::Event::MouseButtonPressed:

                if(roomVec[roomCount].clueSpriteVec[6].getGlobalBounds().contains(mousePosition) ) { //Puzzle
                    //Display Puzzle
                    displayPuzzlePrompt( roomVec[roomCount].spriteVec[0] );
                } else if (roomVec[roomCount].clueSpriteVec[0].getGlobalBounds().contains(mousePosition)) { //Clue 1
                    //Display Clue 1
                    displayPuzzlePrompt( roomVec[roomCount].spriteVec[1]);
                } else if (roomVec[roomCount].clueSpriteVec[1].getGlobalBounds().contains(mousePosition)) { //Clue 2
                    //Display Clue 2
                    displayPuzzlePrompt( roomVec[roomCount].spriteVec[2]);
                } else if (roomVec[roomCount].clueSpriteVec[2].getGlobalBounds().contains(mousePosition)) { //Clue 3
                    //Display Clue 3
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[3]);
                } else if (roomVec[roomCount].spriteVec[4].getGlobalBounds().contains(mousePosition)) { //Forward arrow
                    //Move forward a room
                    if(roomVec[roomCount].isPuzzleSolved){
                        roomCount = clamp(roomCount+1, 0, int( roomVec.size() - 1 ));
                    } else {
                        std::cout << "You cannot move forward without solving the puzzle first.\n";
                        displayAnswerPrompt(roomVec[roomCount].spriteVec[6], roomVec[roomCount].roomAnswer, roomCount);
                    }
                } else if (roomVec[roomCount].spriteVec[5].getGlobalBounds().contains(mousePosition)) { //Back arrow
                    //Move backwards a room
                    roomCount = clamp(roomCount-1, 0, int( roomVec.size() - 1 ));
                } else if (roomVec[roomCount].clueSpriteVec[3].getGlobalBounds().contains(mousePosition)) { //Clue 1 unlocked
                    //Display Clue 1
                    displayPuzzlePrompt( roomVec[roomCount].spriteVec[1]);
                } else if (roomVec[roomCount].clueSpriteVec[4].getGlobalBounds().contains(mousePosition)) { //Clue 2 unlocked
                    //Display Clue 2
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[2]);
                } else if (roomVec[roomCount].clueSpriteVec[5].getGlobalBounds().contains(mousePosition)) { //Clue 3 unlocked
                    //Display Clue 3
                    displayPuzzlePrompt(roomVec[roomCount].spriteVec[3]);
                }

                break;
            default:
                break;
        };
    }
}

void Dungeon::render() {

    menuPtr->menuScreen->clear(sf::Color::Black);

    //Background and room sprites
    menuPtr->menuScreen->draw(roomVec[roomCount].backgroundSprite);

    for(int i = 4; i < roomVec[roomCount].spriteVec.size(); i++){
        if(i != 6)
            menuPtr->menuScreen->draw(roomVec[roomCount].spriteVec[i]);
    }

    for(int i = 0; i < roomVec[roomCount].clueSpriteVec.size(); i++){
        menuPtr->menuScreen->draw(roomVec[roomCount].clueSpriteVec[i]);
    }
    


    menuPtr->menuScreen->display();
}

void Dungeon::displayPuzzlePrompt(sf::Sprite puzzleSprite) {
    this->menuPtr->menuScreen->draw(puzzleSprite);
    this->menuPtr->menuScreen->display();
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    }
}

void Dungeon::displayAnswerPrompt(sf::Sprite answerSprite, std::string answerString, int roomCount) {
    std::string answer = ""; 

    this->menuPtr->menuScreen->draw(answerSprite);
    this->menuPtr->menuScreen->display();
    std::cout << "Type your answer and press enter: ";
    std::cin >> answer;
    if (answerString.compare(answer) == 0) {
        std::cout << "\nCorrect Answer.\n";
        roomVec[roomCount].isPuzzleSolved = true;

    } else {
        std::cout << "\nIncorrect Answer.\n";
    }

}