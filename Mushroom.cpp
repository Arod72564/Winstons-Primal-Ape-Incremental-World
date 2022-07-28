#include "Mushroom.h"

Mushroom::Mushroom(sf::Texture &mushroomTexture, float x, float y){
    this->health = 4;
    this->mushroomSprite.setTexture(mushroomTexture);
    this->mushroomSprite.setPosition(x,y);
}

Mushroom::Mushroom(sf::Texture &mushroomTexture, float x, float y, bool t){
    this->health = 4;
    this->mushroomSprite.setTexture(mushroomTexture);
    this->mushroomSprite.setPosition(x,y);
    this->mushroomSprite.setOrigin(this->mushroomSprite.getLocalBounds().width / 2, this->mushroomSprite.getLocalBounds().height / 2);
}

Mushroom::~Mushroom(){

}

void Mushroom::damageMushroom(sf::Texture &mushroomTexture4,sf::Texture &mushroomTexture3,sf::Texture &mushroomTexture2,sf::Texture &mushroomTexture1){
    this->health--;
    switch(this->health){
        case 4:
            this->mushroomSprite.setTexture(mushroomTexture4);
            break;

        case 3:
            this->mushroomSprite.setTexture(mushroomTexture3);
            break;

        case 2:
            this->mushroomSprite.setTexture(mushroomTexture2);
            break;

        case 1:
            this->mushroomSprite.setTexture(mushroomTexture1);
            break;

        default:
            break;
    }
}