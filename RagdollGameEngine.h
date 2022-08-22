#ifndef RAGDOLLGAMEENGINE_H
#define RAGDOLLGAMEENGINE_H

#include "headerFiles.h"
#include "MenuScreen.h"

class RagdollGameEngine {

struct Node;
struct Spring;

public:

    struct Node {
        PhysVector2<float> position;
        PhysVector2<float> velocity;
        PhysVector2<float> force;
        float mass;
    };


    struct Spring {
        Node* A;
        Node* B;
        float stiffness;
        float rest_length;
        float damping;

        float force() {
            PhysVector2<float> temp = PhysVector2<float>(B->position - A->position);
            return ((temp.mag() - rest_length) * stiffness + (temp.normalize() * (B->velocity - A->velocity)) * damping);
        }
    };
};



#endif
