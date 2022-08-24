#ifndef SOFTBODY_H
#define SOFTBODY_H

#include "headerFiles.h"
#include "MenuScreen.h"

struct Node;
struct Spring;

class SoftBody {

public:

    std::vector< std::vector<Node*> > nodes;
    std::vector<Spring*> springs;
    std::vector<Node*> border;

    // sf::VertexArray* solidSoftBody;
    sf::ConvexShape* solidSoftBody;

    bool showSolid;


    // Node* buildNode(float x, float y, float R = 20.f);
    SoftBody* buildSpring(Node* A, Node* B, float damping = 0.5f, float stiffness = 1.f);
    SoftBody* buildRect(const float x, const float y, const int row, const int col, float node_dist = 15.f, float radius = 5.f, float damping = 0.5f, float stiffness = 1.f);

    void checkCollision(Node* node);

    void update(float elapsed, PhysVector2<float>& f_ext, const float& grav);


};

struct Node {
    PhysVector2<float> position;
    PhysVector2<float> velocity;
    PhysVector2<float> force; // Almost equivalent to acceleration
    float mass = 1.f;
    sf::CircleShape image;

    Node(float x = 0.f, float y = 0.f, float R = 5.f);

    Node* setPosition(float x, float y);

    float dist(Node B);

    // void applyForce();

    void update(float elapsed, PhysVector2<float>& f_ext, const float& grav);
};


struct Spring {
    Node* nodes[2];
    float stiffness;
    float rest_length;
    float damping;

    sf::Vertex line[2];

    Spring(Node* A, Node* B, float damping = 0.5f, float stiffness = 1.f);

    void applyForce(int node);

    void update();
};

#endif
