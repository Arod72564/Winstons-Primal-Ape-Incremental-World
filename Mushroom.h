#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "headerFiles.h"

class Mushroom{
    public:
        int health;
        bool isDestroyed;
        sf::Sprite mushroomSprite;

        Mushroom(sf::Texture &mushroomTexture, float x, float y);
        Mushroom(sf::Texture &mushroomTexture, float x, float y, bool t);
        virtual ~Mushroom();
        void damageMushroom(sf::Texture &mushroomTexture4,sf::Texture &mushroomTexture3,sf::Texture &mushroomTexture2,sf::Texture &mushroomTexture1);

};

#endif