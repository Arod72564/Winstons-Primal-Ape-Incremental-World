#ifndef DUNGEONGAMEENGINE_H
#define DUNGEONGAMEENGINE_H

#include "HeaderFiles.h"
#include "MenuScreen.h"

struct DungeonRoom {
    int roomId;
    bool isPuzzleSolved;
    bool isClue1Hidden;
    bool isClue2Hidden;
    bool isClue3Hidden;
    bool isClue1Opened;
    bool isClue2Opened;
    bool isClue3Opened;
    std::string roomAnswer;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<sf::Texture> textureVec;
    std::vector<sf::Sprite> spriteVec; //display screens, move, and answer sprites
    std::vector<sf::Sprite> clueSpriteVec; //clickable clues
    std::vector<sf::Sprite> hiddenSpotVec;
};

class DungeonGameEngine {
    public:
        MenuScreen* menuPtr;
        std::vector<struct DungeonRoom> roomVec;
        sf::Texture moveTexture1;
        sf::Texture moveTexture2;
        sf::Texture ansTexture;
        sf::Texture puzzleClue;
        sf::Texture hiddenSpot;
        sf::Texture clue1;
        sf::Texture clue2;
        sf::Texture clue3;
        sf::Texture clue4;
        sf::Texture clue5;
        sf::Texture clue6;

        int roomCount;

        DungeonGameEngine(MenuScreen* menuPtr);
        DungeonGameEngine();
        virtual ~DungeonGameEngine();
        void initRooms();
        void update();
        void render();
        void displayPuzzlePrompt(sf::Sprite puzzleSprite);
        void displayAnswerPrompt(sf::Sprite answerSprite, std::string answerString, int roomCount);
        
};

#endif