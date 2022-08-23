#include "SoftBody.h"



/**********************************************************
                    NODE STRUCT
**********************************************************/

Node::Node(float R) {
    image = sf::CircleShape(R);
    image.setOrigin(R, R);
    image.setFillColor(generateColor());
}

Node* Node::setPosition(float x, float y) {
    position(x, y);
    image.setPosition(x, y);
    return this;
}

float Node::dist(Node B) {
    return this->position.dist(B.position);
}


void Node::applyForce() {
    force(0.f, 0.f);
    if (!springs.empty()) {
        for (int i = 0; i < springs.size(); ++i) {
            // std::cout << (this == springs[i]->A) << std::endl;
            if (this == springs[i]->A) {
                std::cout << springs[i]->force() << std::endl;
                force += PhysVector2<float>(springs[i]->force(), springs[i]->B->position - springs[i]->A->position);
            } else {
                std::cout << springs[i]->force() << std::endl;
                force += PhysVector2<float>(springs[i]->force(), springs[i]->A->position - springs[i]->B->position);
            }
        }
    }
    // std::cout << force << std::endl;
}


void Node::update() {
    applyForce();
    velocity += force * SoftBody::DELTA_T;
    position += velocity * SoftBody::DELTA_T;
    // image.move((velocity * SoftBody::DELTA_T).toSF());
    image.setPosition(position.toSF());
}


/**********************************************************
                    SPRING STRUCT
**********************************************************/

Spring::Spring(Node* A, Node* B, float stiffness) {
    this->A = A;
    this->B = B;
    this->stiffness = stiffness;
    this->rest_length = A->dist(*B);
    this->A->springs.push_back(this);
    this->B->springs.push_back(this);
    line[0] = sf::Vertex(A->position.toSF());
    line[1] = sf::Vertex(B->position.toSF());

}


float Spring::force() {
    PhysVector2<float> temp = PhysVector2<float>(B->position - A->position);
    return ((temp.mag() - rest_length) * stiffness + (temp.normalize() * (B->velocity - A->velocity)) * damping);
}
