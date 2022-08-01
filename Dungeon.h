#ifndef DUNGEON_H
#define DUNGEON_H

#include "HeaderFiles.h"
#include "MenuScreen.h"

struct DungeonRoom {
    int roomId;
    bool isPuzzleSolved;
    std::string roomAnswer;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<sf::Texture> textureVec;
    std::vector<sf::Sprite> spriteVec;
    std::vector<sf::Sprite> clueSpriteVec;
};

class Dungeon {
    public:
        MenuScreen* menuPtr;
        std::vector<struct DungeonRoom> roomVec;
        sf::Event ev;
        int roomCount;



        Dungeon(MenuScreen* menuPtr);
        Dungeon();
        virtual ~Dungeon();
        void initRooms();
        void update();
        void render();
        void displayPuzzlePrompt(sf::Sprite puzzleSprite);
        void displayAnswerPrompt(sf::Sprite answerSprite, std::string answerString);
        
};

#endif