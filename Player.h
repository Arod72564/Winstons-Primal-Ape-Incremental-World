#ifndef PLAYER_H
#define PLAYER_H

#include "headerFiles.h"
#include "Centipede.h"

class Player {
    public:
        sf::Sprite playerSprite;
        bool isDead;

        Player(sf::Texture &playerTexture, float x, float y);
        virtual ~Player();
        void updateMovement(sf::Keyboard::Key key);
        void updateMovement(sf::Vector2f &mousePosition, sf::RenderWindow* gameWindow);
};

#endif