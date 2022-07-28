#ifndef BEAM_H
#define BEAM_H

#include "headerFiles.h"
#include "Player.h"
#include "Mushroom.h"
#include "Centipede.h"

class Beam {
    public:
        Player *playerPtr;
        sf::Sprite beamSprite;

        Beam(sf::Texture &beamTexture, Player *player1, float x, float y);
        virtual ~Beam();
        BeamCollisionType updateMovement(bool &isBeamPresent, std::vector<Mushroom> mushroomVector, std::vector<Centipede> centipedeVector, int &beamCollisionindex);
};

#endif