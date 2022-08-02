#include "Mushroom.h"

Mushroom::Mushroom(sf::Texture &mushroomTexture, float x, float y){
    health = 4;
    mushroomSprite.setTexture(mushroomTexture);
    mushroomSprite.setPosition(x,y);
}

Mushroom::Mushroom(sf::Texture &mushroomTexture, float x, float y, bool t){
    health = 4;
    mushroomSprite.setTexture(mushroomTexture);
    mushroomSprite.setPosition(x,y);
    mushroomSprite.setOrigin(mushroomSprite.getLocalBounds().width / 2, mushroomSprite.getLocalBounds().height / 2);
}

Mushroom::~Mushroom(){

}

void Mushroom::damageMushroom(sf::Texture &mushroomTexture4,sf::Texture &mushroomTexture3,sf::Texture &mushroomTexture2,sf::Texture &mushroomTexture1){
    health--;
    switch(health){
        case 4:
            mushroomSprite.setTexture(mushroomTexture4);
            break;

        case 3:
            mushroomSprite.setTexture(mushroomTexture3);
            break;

        case 2:
            mushroomSprite.setTexture(mushroomTexture2);
            break;

        case 1:
            mushroomSprite.setTexture(mushroomTexture1);
            break;

        default:
            break;
    }
}