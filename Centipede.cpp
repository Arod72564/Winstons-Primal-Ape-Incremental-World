#include "Centipede.h"

Centipede::Centipede() {

}

Centipede::Centipede(sf::Texture &centipedeTexture, float x, float y) {
    centipedeSprite.setTexture(centipedeTexture);
    centipedeSprite.setPosition(x,y);
    centipedeSprite.setOrigin( (centipedeSprite.getGlobalBounds().width / 2), (centipedeSprite.getGlobalBounds().height / 2));
    isMovingRight = true;
    isMovingDown = false;
    downDoggie = 0;
}

Centipede::~Centipede() {

}

void Centipede::updateMovement(std::vector<Mushroom> mushroomVector, std::vector<Centipede> centipedeVector, sf::RenderWindow* gameWindow) {

    //handle centipede collision
    // move down when collision is triggered
    if (isMovingDown) {
        if (downDoggie < 50) {

            centipedeSprite.move(0, CENTIPEDE_SPEED);

            for (int i = 0; i < mushroomVector.size(); i++) { //stop downward movement if another collision is triggered
                if (centipedeSprite.getGlobalBounds().intersects(mushroomVector[i].mushroomSprite.getGlobalBounds())) {
                    centipedeSprite.move(0, -CENTIPEDE_SPEED);
                    downDoggie = 51;
                }
            }
            downDoggie += 1;

        } else {
            isMovingDown = false;
            downDoggie = 0.0;
            rotate(90);
            isMovingRight = !(isMovingRight);     
        }

    } else {

        //move left or right
        move();
        
        if (centipedeSprite.getPosition().x < 25) { //collision with left of game window
            centipedeSprite.setPosition(25, centipedeSprite.getPosition().y);
            rotate(90);
            moveDown();
            isMovingDown = true;

        } else if ( (centipedeSprite.getPosition().x + (centipedeSprite.getGlobalBounds().width/2)) > WINDOW_WIDTH) { //collision with right of game window
            centipedeSprite.setPosition(WINDOW_WIDTH - centipedeSprite.getGlobalBounds().width/2, centipedeSprite.getPosition().y);
            rotate(90);
            moveDown();
            isMovingDown = true;
            

        } else if (centipedeSprite.getPosition().y < 0) { //collision with top of game window
            centipedeSprite.setPosition(centipedeSprite.getPosition().x, 0);

        } else if ( (centipedeSprite.getPosition().y + centipedeSprite.getGlobalBounds().height) > gameWindow->getSize().y) { //collision with bottom of game window
            centipedeSprite.setPosition(centipedeSprite.getPosition().x, 25);
        } else {

            for (int i = 0; i < mushroomVector.size(); i++) { //mushroom collision
                if (centipedeSprite.getGlobalBounds().intersects(mushroomVector[i].mushroomSprite.getGlobalBounds())) {
                    if (isMovingDown) {
                        isMovingDown = false;
                        downDoggie = 0.0;
                        rotate(90);
                        isMovingRight = !(isMovingRight);     
                    } else if (isMovingRight) {
                        centipedeSprite.setPosition(mushroomVector[i].mushroomSprite.getGlobalBounds().left-25.1, centipedeSprite.getPosition().y);
                        rotate(90);
                        moveDown();
                        isMovingDown = true;
                    } else {
                        centipedeSprite.setPosition(mushroomVector[i].mushroomSprite.getGlobalBounds().left + mushroomVector[i].mushroomSprite.getLocalBounds().width + 25.1, centipedeSprite.getPosition().y);
                        rotate(90);
                        moveDown();
                        isMovingDown = true;
                    }
                }
            }
        }
    }
}

void Centipede::move() {
    if (isMovingRight) {
        centipedeSprite.move(CENTIPEDE_SPEED,0);
    } else {
        centipedeSprite.move(CENTIPEDE_SPEED * -1,0);
    }  
}

void Centipede::moveDown() {
    centipedeSprite.move(0, 1);
}

void Centipede::rotate(float x) {
    if (isMovingRight) {
        centipedeSprite.rotate(x);
    } else {
        centipedeSprite.rotate(-x);
    }
}

void Centipede::loadTexture(sf::Texture &centipedeTexture) {
    centipedeSprite.setTexture(centipedeTexture);
}