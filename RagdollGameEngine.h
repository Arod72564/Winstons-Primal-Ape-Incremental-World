#ifndef RAGDOLLGAMEENGINE_H
#define RAGDOLLGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"
#include "Softbody.h"

class RagdollGameEngine {
    public:
        static constexpr float DT = 0.01f;
        // static constexpr float G = 0.05;
        const float maxDragForce = 50.0f;

        PhysVector2<float> f_ext;
        PhysVector2<float> f_mouse;
        PhysVector2<float> drag;

        PhysVector2<float> initialClickPoint;
        sf::Vertex line[2];

        sf::Clock clock;

        MenuScreen* menuPtr;
        // std::vector<Node*> node_vector;
        // std::vector<Spring*> spring_vector;
        std::vector<SoftBody*> softbody_vector;
        SoftBody* clickedSoftbody = nullptr;

        sf::Event ev;

        bool isMouseFirstClicked;
        bool isLineDrawn;

        RagdollGameEngine(MenuScreen* menu);


        void initGame();
        void update();
        void render();
};

#endif
