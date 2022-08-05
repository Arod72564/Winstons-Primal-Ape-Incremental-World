#include "Beam.h"

Beam::Beam(sf::Texture &beamTexture, Player *player1, float x, float y) {
    beamSprite.setTexture(beamTexture);
    beamSprite.setOrigin( (beamSprite.getLocalBounds().width / 2), beamSprite.getLocalBounds().height);
    playerPtr = player1;
    beamSprite.setPosition(x,y);
}

Beam::~Beam() {

}

BeamCollisionType Beam::updateMovement(bool &isBeamPresent, std::vector<Mushroom> mushroomVector, std::vector<Centipede> centipedeVector, int &beamCollisionindex) {
    beamSprite.move(0, -0.8);

    if (beamSprite.getGlobalBounds().top < 0) { //hits top
        
        isBeamPresent = !(isBeamPresent);
        return BeamCollisionType::boundary;
    }
    
    for (int i = 0; i < centipedeVector.size(); i++) { 
        if (beamSprite.getGlobalBounds().intersects(centipedeVector[i].centipedeSprite.getGlobalBounds())) {
            
            //kill appropraite centipede body
            beamCollisionindex = i;
            isBeamPresent = !(isBeamPresent);
            return BeamCollisionType::centipede;
        }
    }

    for (int i = 0; i < mushroomVector.size(); i++) {
        if (beamSprite.getGlobalBounds().intersects(mushroomVector[i].mushroomSprite.getGlobalBounds())) {
            
            //damage appropriate mushroom
            beamCollisionindex = i;
            isBeamPresent = !(isBeamPresent);
            return BeamCollisionType::mushroom;
        }
    }

    return BeamCollisionType::nan_;
}