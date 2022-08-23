#ifndef SOFTBODY_H
#define SOFTBODY_H

#include "headerFiles.h"
#include "MenuScreen.h"

struct Node;
struct Spring;

class SoftBody {

public:
    static constexpr float DELTA_T = 0.1;
    static constexpr float G = 0.05;


};

struct Node {
    PhysVector2<float> position;
    PhysVector2<float> velocity;
    PhysVector2<float> force; // Almost equivalent to acceleration
    float mass = 1.f;
    sf::CircleShape image;

    std::vector<Spring*> springs;

    Node(float R = 20.f);

    Node* setPosition(float x, float y);

    float dist(Node B);

    void applyForce();

    void update();
};


struct Spring {
    Node* A;
    Node* B;
    float stiffness = 1.f;
    float rest_length;
    float damping = 0.f;

    sf::Vertex line[2];

    Spring(Node* A, Node* B, float stiffness = 1.f);

    float force();
};

#endif
