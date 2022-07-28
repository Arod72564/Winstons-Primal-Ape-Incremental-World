#include "Player.h"

Player::Player(sf::Texture &playerTexture, float x, float y){
    this->isDead = false;
    this->playerSprite.setTexture(playerTexture);
    this->playerSprite.setPosition(x,y);
}

Player::~Player(){

}

void Player::updateMovement(sf::Keyboard::Key key){
    if(key == sf::Keyboard::Up){
        this->playerSprite.move(0,-10);
        if(this->playerSprite.getGlobalBounds().top < WINDOW_HEIGHT-150){
            this->playerSprite.move(0,10);
        }
    } else if (key == sf::Keyboard::Down){
        this->playerSprite.move(0,10);
        if(this->playerSprite.getGlobalBounds().top + this->playerSprite.getLocalBounds().height > WINDOW_HEIGHT){
            this->playerSprite.move(0,-10);
        }
    } else if (key == sf::Keyboard::Left) {
        this->playerSprite.move(-10,0);
        if(this->playerSprite.getGlobalBounds().left < 0){
            this->playerSprite.move(10,0);
        }
    } else if (key == sf::Keyboard::Right) {
        this->playerSprite.move(10,0);
        if(this->playerSprite.getGlobalBounds().left + this->playerSprite.getLocalBounds().width > WINDOW_WIDTH){
            this->playerSprite.move(-10,0);
        }
    }
}

void Player::updateMovement(sf::Vector2f &mousePosition, sf::RenderWindow* gameWindow){
    this->playerSprite.setPosition(mousePosition.x, mousePosition.y);

    if(this->playerSprite.getGlobalBounds().top < gameWindow->getSize().y - 150){
        this->playerSprite.setPosition(this->playerSprite.getPosition().x, gameWindow->getSize().y - 150 + this->playerSprite.getLocalBounds().height / 2);

    }
    if (this->playerSprite.getGlobalBounds().top + this->playerSprite.getLocalBounds().height > gameWindow->getSize().y) {
        this->playerSprite.setPosition(this->playerSprite.getPosition().x, gameWindow->getSize().y - this->playerSprite.getLocalBounds().height / 2);

    }
    if (this->playerSprite.getGlobalBounds().left < 0) {
        this->playerSprite.setPosition(this->playerSprite.getLocalBounds().width / 2, this->playerSprite.getPosition().y);

    }
    if (this->playerSprite.getGlobalBounds().left + this->playerSprite.getLocalBounds().width > gameWindow->getSize().x) {
        this->playerSprite.setPosition(gameWindow->getSize().x - this->playerSprite.getLocalBounds().width / 2, this->playerSprite.getPosition().y);
    }
}