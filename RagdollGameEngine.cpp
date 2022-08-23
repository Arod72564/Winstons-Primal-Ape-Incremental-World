#include "RagdollGameEngine.h"
#include "SoftBody.h"

RagdollGameEngine::RagdollGameEngine(MenuScreen* menu) {
    menuPtr = menu;
    initGame();
}


void RagdollGameEngine::initGame() {
    clock.restart();

    float min = 195.f;
    float max = 255.f;
    SoftBody* temp = new SoftBody();
    temp->buildRect(200.f, 200.f, 10, 10, 5.f, 2.f, 0.5f, 30.f);
    temp->nodes.at(0).at(0)->setPosition(min, min);
    temp->nodes.at(0).at(9)->setPosition(max, min);
    temp->nodes.at(9).at(0)->setPosition(min, max);
    temp->nodes.at(9).at(9)->setPosition(max, max);

    // for (Spring* spring : temp->springs) {
    //     std::cout << spring->damping << " " << spring->stiffness << std::endl;
    // }


    softbody_vector.push_back(temp);

    SoftBody* bar = new SoftBody();
    Node* A = new Node(400.f, 200.f);
    Node* B = new Node(400.f, 400.f);
    Spring* spring = new Spring(A, B, 1.f, 10.f);
    spring->rest_length = A->dist(*B) / 2;
    // std::cout << spring->damping << " " << spring->stiffness << std::endl;

    bar->nodes.push_back(std::vector<Node*>());
    bar->nodes.at(0).push_back(A);
    bar->nodes.at(0).push_back(B);
    bar->springs.push_back(spring);

    softbody_vector.push_back(bar);


}

void RagdollGameEngine::update() {
    f_ext = PhysVector2<float>(0.f, GRAV) + drag;
    if(!softbody_vector.empty()) {
        float temp_time = clock.restart().asSeconds();
        for(SoftBody* softbody : softbody_vector) {
            if (temp_time < DT) softbody->update(DT, f_ext);
            else softbody->update(temp_time, f_ext);
        }
    }

    while(menuPtr->menuScreen->pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::EventType::Closed:
                menuPtr->currentGameType = NULL_GAME;
                break;
        }
    }
}

void RagdollGameEngine::render() {
    menuPtr->menuScreen->clear();

    if(!softbody_vector.empty()) {
        for (SoftBody* softbody : softbody_vector) {

            // if(!softbody->springs.empty()) {
            //     for (Spring* spring : softbody->springs) {
            //         menuPtr->menuScreen->draw(spring->line, 2, sf::Lines);
            //     }
            // }

            if (!softbody->nodes.empty()) {
                for (std::vector<Node*> node_vector : softbody->nodes) {
                    for (Node* node : node_vector) {
                        menuPtr->menuScreen->draw(node->image);
                    }
                }
            }
        }
    }

    menuPtr->menuScreen->display();
}
