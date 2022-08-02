#include "Player.h"

Player::Player(sf::Texture &playerTexture, float x, float y) {
    isDead = false;
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(x,y);
}

Player::~Player() {

}

void Player::updateMovement(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Up) {
        playerSprite.move(0,-10);
        if (playerSprite.getGlobalBounds().top < WINDOW_HEIGHT-150) {
            playerSprite.move(0,10);
        }
    } else if (key == sf::Keyboard::Down) {
        playerSprite.move(0,10);
        if (playerSprite.getGlobalBounds().top + playerSprite.getLocalBounds().height > WINDOW_HEIGHT) {
            playerSprite.move(0,-10);
        }
    } else if (key == sf::Keyboard::Left) {
        playerSprite.move(-10,0);
        if (playerSprite.getGlobalBounds().left < 0) {
            playerSprite.move(10,0);
        }
    } else if (key == sf::Keyboard::Right) {
        playerSprite.move(10,0);
        if (playerSprite.getGlobalBounds().left + playerSprite.getLocalBounds().width > WINDOW_WIDTH) {
            playerSprite.move(-10,0);
        }
    }
}

void Player::updateMovement(sf::Vector2f &mousePosition, sf::RenderWindow* gameWindow) {
    playerSprite.setPosition(mousePosition.x, mousePosition.y);

    if (playerSprite.getGlobalBounds().top < gameWindow->getSize().y - 150) {
        playerSprite.setPosition(playerSprite.getPosition().x, gameWindow->getSize().y - 150 + playerSprite.getLocalBounds().height / 2);

    }
    if (playerSprite.getGlobalBounds().top + playerSprite.getLocalBounds().height > gameWindow->getSize().y) {
        playerSprite.setPosition(playerSprite.getPosition().x, gameWindow->getSize().y - playerSprite.getLocalBounds().height / 2);

    }
    if (playerSprite.getGlobalBounds().left < 0) {
        playerSprite.setPosition(playerSprite.getLocalBounds().width / 2, playerSprite.getPosition().y);

    }
    if (playerSprite.getGlobalBounds().left + playerSprite.getLocalBounds().width > gameWindow->getSize().x) {
        playerSprite.setPosition(gameWindow->getSize().x - playerSprite.getLocalBounds().width / 2, playerSprite.getPosition().y);
    }
}