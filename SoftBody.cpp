#include "SoftBody.h"
#include "RagdollGameEngine.h"


/**********************************************************
                    SOFTBODY CLASS
**********************************************************/

// Node* SoftBody::buildNode(float x, float y, float R) {
//     Node* A = new Node(x, y, R);
//     nodes.push_back(A);
//     return A;
// }

SoftBody* SoftBody::buildSpring(Node* A, Node* B, float damping, float stiffness) {
    Spring* spring = new Spring(A, B, damping, stiffness);
    springs.push_back(spring);
    return this;
}

SoftBody* SoftBody::buildRect(const float x, const float y, const int row, const int col, float node_dist, float radius, float damping, float stiffness) {
    for (int i = 0; i < row; ++i) {
        nodes.push_back(std::vector<Node*>());
        for (int j = 0; j < col; ++j) {
            nodes.at(i).push_back( new Node(x + j * node_dist, y + i * node_dist, radius) );
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (j + 1 < col) {
                buildSpring( nodes.at(i).at(j), nodes.at(i).at(j+1), damping, stiffness );
            }
            if (i + 1 < row) {
                buildSpring( nodes.at(i).at(j), nodes.at(i+1).at(j), damping, stiffness );
            }
            if (i + 1 < row && j + 1 < col) {
                buildSpring( nodes.at(i).at(j), nodes.at(i+1).at(j+1), damping, stiffness );
            }
            if (i + 1 < row && j - 1 >= 0) {
                buildSpring( nodes.at(i).at(j), nodes.at(i+1).at(j-1), damping, stiffness );
            }
        }
    }


    return this;
}

void SoftBody::checkCollision(Node* node) {
    // if (!springs.empty()) {
    //     for (Spring* spring : springs) {
    //         if (spring->nodes[0]->dist( *(spring->nodes[1]) ) == 0.f) {
    //             continue;
    //         } else if (spring->nodes[0]->dist( *(spring->nodes[1]) ) < spring->nodes[0]->image.getRadius() * 2.f) {
    //             spring->nodes[0]->image.setFillColor(sf::Color::Blue);
    //             spring->nodes[1]->image.setFillColor(sf::Color::Red);
    //             PhysVector2<float> normal_vector = (spring->nodes[0]->position - spring->nodes[1]->position).normalize();
    //             spring->nodes[0]->velocity = spring->nodes[0]->velocity - normal_vector * ((spring->nodes[0]->velocity * normal_vector) * 2);
    //             spring->nodes[1]->velocity = spring->nodes[1]->velocity + normal_vector * ((spring->nodes[1]->velocity * (normal_vector * -1.f)) * 2);
    //         }
    //     }
    // }

    // if (!nodes.empty()) {
    //     for (std::vector<Node*> vector : nodes) {
    //         if (!vector.empty()) {
    //             for (Node* node : vector) {
    //                 for (std::vector<Node*> another_vector : nodes) {
    //                     for (Node* another_node : another_vector) {
    //                         if (node->dist(*another_node) == 0.f) continue;
    //                         else if (node->dist(*another_node) < node->image.getRadius() * 2.f) {
    //                             node->image.setFillColor(sf::Color::Blue);
    //                             another_node->image.setFillColor(sf::Color::Red);
    //                             PhysVector2<float> normal_vector = (node->position - another_node->position).normalize();
    //                             std::cout << "Before: " << node->velocity << std::endl;
    //                             node->velocity = node->velocity - normal_vector * ((node->velocity * normal_vector) * 2);
    //                             std::cout << "After: " << node->velocity << std::endl;
    //                             another_node->velocity = another_node->velocity + normal_vector * ((another_node->velocity * (normal_vector * -1.f)) * 2);
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    if (!nodes.empty()) {
        for (std::vector<Node*> vector : nodes) {
            if (!vector.empty()) {
                for (Node* another_node : vector) {
                    if (node->dist(*another_node) == 0.f) continue;
                    else if (node->dist(*another_node) < node->image.getRadius() * 2.f) {
                        // node->image.setFillColor(sf::Color::Blue);
                        // another_node->image.setFillColor(sf::Color::Red);
                        PhysVector2<float> normal_vector = (node->position - another_node->position).normalize();

                        float offset_dist = (2.f * node->image.getRadius() - node->dist(*another_node)) / 2.f;

                        node->position += normal_vector * offset_dist;
                        node->image.move((normal_vector * offset_dist).toSF());

                        another_node->position += normal_vector * (offset_dist * -1.f);
                        another_node->image.move((normal_vector * (offset_dist * -1.f)).toSF());
                        // std::cout << "Before: " << node->velocity << std::endl;
                        node->velocity = node->velocity - normal_vector * ((node->velocity * normal_vector) * 2);
                        // std::cout << "After: " << node->velocity << std::endl;
                        another_node->velocity = another_node->velocity + normal_vector * ((another_node->velocity * (normal_vector * -1.f)) * 2);
                    }
                }
            }
        }
    }

    // if (!nodes.empty()) {
    //     for (int num1 = 0; num1 < nodes.size(); num1++) {
    //
    //         if (!nodes.at(num1).empty()) {
    //
    //             for (int num2 = 0; num2 < nodes.at(num1).size(); num2++) {
    //
    //                 for (int num1_prime = 0; num1_prime < nodes.size(); num1_prime++) {
    //
    //                     for (int num2_prime = 0; num2_prime < nodes.at(num1_prime).size(); num2_prime++) {
    //
    //                         if (nodes.at(num1).at(num2)->dist(*(nodes.at(num1_prime).at(num2_prime)) ) == 0.f) continue;
    //
    //                         else if ( nodes.at(num1).at(num2)->dist( *(nodes.at(num1_prime).at(num2_prime)) ) < nodes.at(num1).at(num2)->image.getRadius() * 2.f ) {
    //                             nodes.at(num1).at(num2)->image.setFillColor(sf::Color::Blue);
    //                             nodes.at(num1_prime).at(num2_prime)->image.setFillColor(sf::Color::Red);
    //                             // nodes.at(num1).at(num2)->velocity(0.f, 100.f);
    //                             PhysVector2<float> normal_vector = ( nodes.at(num1).at(num2)->position - nodes.at(num1_prime).at(num2_prime)->position ).normalize();
    //                             nodes.at(num1).at(num2)->velocity = nodes.at(num1).at(num2)->velocity - normal_vector * ( (nodes.at(num1).at(num2)->velocity * normal_vector) * 2.f );
    //                             nodes.at(num1_prime).at(num2_prime)->velocity = nodes.at(num1_prime).at(num2_prime)->velocity + normal_vector * (( nodes.at(num1_prime).at(num2_prime)->velocity * (normal_vector * -1.f) ) * 2.f );
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
}

void SoftBody::update(float elapsed, PhysVector2<float>& f_ext) {

    if (!nodes.empty()) {
        for(std::vector<Node*> node_vector : nodes) {
            if(!node_vector.empty()) {
                for(Node* node : node_vector) {
                    checkCollision(node);
                    // std::cout << "After checkCollision: " << node->velocity << std::endl;
                    node->update(elapsed, f_ext);
                }
            }
        }
    }

    if(!springs.empty()) {
        for (Spring* spring : springs) {
            spring->applyForce(0);
            spring->applyForce(1);
            spring->update();
        }
    }
    // checkCollision();
}

/**********************************************************
                    NODE STRUCT
**********************************************************/

Node::Node(float x, float y, float R) {
    image = sf::CircleShape(R);
    image.setOrigin(R, R);
    image.setFillColor(generateColor());
    setPosition(x, y);
}

Node* Node::setPosition(float x, float y) {
    position(x, y);
    image.setPosition(x, y);
    return this;
}

float Node::dist(Node B) {
    return this->position.dist(B.position);
}


// void Node::applyForce() {
//     force(0.f, 0.f);
//     if (!springs.empty()) {
//         for (int i = 0; i < springs.size(); ++i) {
//             if (this == springs[i]->A) {
//                 std::cout << springs[i]->force() << std::endl;
//                 force += PhysVector2<float>(springs[i]->force(), springs[i]->B->position - springs[i]->A->position);
//             } else {
//                 std::cout << springs[i]->force() << std::endl;
//                 force += PhysVector2<float>(springs[i]->force(), springs[i]->A->position - springs[i]->B->position);
//             }
//         }
//     }
// }


void Node::update(float elapsed, PhysVector2<float>& f_ext) {
    force += f_ext;
    velocity += force / mass * elapsed;
    position += velocity * elapsed;
    image.setPosition(position.toSF());
    force(0.f, 0.f);
}


/**********************************************************
                    SPRING STRUCT
**********************************************************/

Spring::Spring(Node* A, Node* B, float damping, float stiffness) {
    nodes[0] = A;
    nodes[1] = B;
    this->stiffness = stiffness;
    this->damping = damping;
    this->rest_length = A->dist(*B);
    line[0] = sf::Vertex(A->position.toSF());
    line[1] = sf::Vertex(B->position.toSF());

}


void Spring::applyForce(int node) {
    PhysVector2<float> temp = PhysVector2<float>(nodes[(node + 1) % 2]->position - nodes[node]->position);
    float force_mag = (temp.mag() - rest_length) * stiffness + (temp.normalize() * (nodes[(node + 1) % 2]->velocity - nodes[node]->velocity)) * damping;
    nodes[node]->force += PhysVector2<float>(force_mag, temp);
}

void Spring::update() {
    line[0] = sf::Vertex(nodes[0]->position.toSF());
    line[1] = sf::Vertex(nodes[1]->position.toSF());
}
