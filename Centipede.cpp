#include "Centipede.h"

Centipede::Centipede(){

}

Centipede::Centipede(sf::Texture &centipedeTexture, float x, float y){
    this->centipedeSprite.setTexture(centipedeTexture);
    this->centipedeSprite.setPosition(x,y);
    this->centipedeSprite.setOrigin((this->centipedeSprite.getGlobalBounds().width / 2), (this->centipedeSprite.getGlobalBounds().height / 2));
    this->isMovingRight = true;
    this->isMovingDown = false;
    this->downDoggie = 0;
}

Centipede::~Centipede(){

}

void Centipede::updateMovement(std::vector<Mushroom> mushroomVector, std::vector<Centipede> centipedeVector, sf::RenderWindow* gameWindow){

    //handle centipede collision
    // move down when collision is triggered
    if (this->isMovingDown){
        if(this->downDoggie < 50){

            this->centipedeSprite.move(0, 0.1);

            for(int i = 0; i < mushroomVector.size(); i++){ //stop downward movement if another collision is triggered
                if(this->centipedeSprite.getGlobalBounds().intersects(mushroomVector[i].mushroomSprite.getGlobalBounds())){
                    this->centipedeSprite.move(0, -0.1);
                    this->downDoggie = 51;
                }
            }
            this->downDoggie += 0.1;

        } else {
            this->isMovingDown = false;
            this->downDoggie = 0.0;
            this->rotate(90);
            this->isMovingRight = !(this->isMovingRight);     
        }

    } else {

        //move left or right
        move();
        
        if(this->centipedeSprite.getPosition().x < 25){ //collision with left of game window
            this->centipedeSprite.setPosition(25, this->centipedeSprite.getPosition().y);
            this->rotate(90);
            moveDown();
            this->isMovingDown = true;

        } else if ((this->centipedeSprite.getPosition().x + (this->centipedeSprite.getGlobalBounds().width/2)) > WINDOW_WIDTH){ //collision with right of game window
            this->centipedeSprite.setPosition(WINDOW_WIDTH - this->centipedeSprite.getGlobalBounds().width/2, this->centipedeSprite.getPosition().y);
            this->rotate(90);
            moveDown();
            this->isMovingDown = true;
            

        } else if (this->centipedeSprite.getPosition().y < 0) { //collision with top of game window
            this->centipedeSprite.setPosition(this->centipedeSprite.getPosition().x, 0);

        } else if ((this->centipedeSprite.getPosition().y + this->centipedeSprite.getGlobalBounds().height) > gameWindow->getSize().y) { //collision with bottom of game window
            this->centipedeSprite.setPosition(this->centipedeSprite.getPosition().x, 25);
        } else {

            for(int i = 0; i < mushroomVector.size(); i++){ //mushroom collision
                if(this->centipedeSprite.getGlobalBounds().intersects(mushroomVector[i].mushroomSprite.getGlobalBounds())){
                    if(this->isMovingRight){
                        this->centipedeSprite.setPosition(mushroomVector[i].mushroomSprite.getGlobalBounds().left-25.1, this->centipedeSprite.getPosition().y);
                        this->rotate(90);
                        moveDown();
                        this->isMovingDown = true;
                    } else {
                        this->centipedeSprite.setPosition(mushroomVector[i].mushroomSprite.getGlobalBounds().left + mushroomVector[i].mushroomSprite.getLocalBounds().width + 25.1, centipedeSprite.getPosition().y);
                        this->rotate(90);
                        moveDown();
                        this->isMovingDown = true;
                    }
                }
            }
        }
    }
}

void Centipede::move(){
    if(this->isMovingRight){
        this->centipedeSprite.move(0.1,0);
    } else {
        this->centipedeSprite.move(-0.1,0);
    }  
}

void Centipede::moveDown(){
    this->centipedeSprite.move(0, 0.1);
}

void Centipede::rotate(float x){
    if(this->isMovingRight){
        this->centipedeSprite.rotate(x);
    } else {
        this->centipedeSprite.rotate(-x);
    }
}

void Centipede::loadTexture(sf::Texture &centipedeTexture){
    this->centipedeSprite.setTexture(centipedeTexture);
}