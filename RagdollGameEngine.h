#ifndef RAGDOLLGAMEENGINE_H
#define RAGDOLLGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"
#include "Softbody.h"

class RagdollGameEngine {

public:
    static constexpr float DT = 0.025f;
    // static constexpr float G = 0.05;

    PhysVector2<float> f_ext;
    PhysVector2<float> drag;

    sf::Clock clock;

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
