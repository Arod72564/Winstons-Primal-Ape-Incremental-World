#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "headerFiles.h"
#include "Mushroom.h"

class Centipede{
    public:
        //sf::Vector2f centipedePos;
        sf::Sprite centipedeSprite;
        bool isMovingRight;
        bool isMovingDown;
        float downDoggie;
        
        Centipede();
        Centipede(sf::Texture &centipedeTexture, float x, float y);
        virtual ~Centipede();
        void updateMovement(std::vector<Mushroom> mushroomVector, std::vector<Centipede> centipedeVector, sf::RenderWindow* gameWindow);
        void move();
        void moveDown();
        void rotate(float x);
        void loadTexture(sf::Texture &centipedeTexture);
};

#endif