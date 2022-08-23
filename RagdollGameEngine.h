#ifndef RAGDOLLGAMEENGINE_H
#define RAGDOLLGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"
#include "Softbody.h"

class RagdollGameEngine {

public:
    static constexpr float DELTA_T = 0.1f;
    static constexpr float G = 0.05;

    MenuScreen* menuPtr;
    // std::vector<Node*> node_vector;
    // std::vector<Spring*> spring_vector;
    std::vector<SoftBody*> softbody_vector;

    sf::Event ev;

    RagdollGameEngine(MenuScreen* menu);


    void initGame();
    void update();
    void render();
};



#endif
