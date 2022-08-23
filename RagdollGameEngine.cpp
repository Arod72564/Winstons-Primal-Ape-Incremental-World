#include "RagdollGameEngine.h"
// #include "SoftBody.h"

RagdollGameEngine::RagdollGameEngine(MenuScreen* menu) {
    menuPtr = menu;
    initGame();
}


void RagdollGameEngine::initGame() {
    SoftBody* temp = new SoftBody();
    temp->buildRect(100.f, 100.f, 5, 5, 15.f, 1.f, 5.f);
    temp->nodes.at(4).at(4)->setPosition(600.f, 600.f);

    // for (Spring* spring : temp->springs) {
    //     std::cout << spring->damping << " " << spring->stiffness << std::endl;
    // }


    softbody_vector.push_back(temp);

    SoftBody* bar = new SoftBody();
    Node* A = new Node(400.f, 200.f);
    Node* B = new Node(400.f, 400.f);
    Spring* spring = new Spring(A, B, 0.f);
    spring->rest_length = A->dist(*B) / 2;
    // std::cout << spring->damping << " " << spring->stiffness << std::endl;

    bar->nodes.push_back(std::vector<Node*>());
    bar->nodes.at(0).push_back(A);
    bar->nodes.at(0).push_back(B);
    bar->springs.push_back(spring);

    softbody_vector.push_back(bar);


}

void RagdollGameEngine::update() {

    if(!softbody_vector.empty()) {
        for(SoftBody* softbody : softbody_vector) {
            softbody->update();
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

            if(!softbody->springs.empty()) {
                for (Spring* spring : softbody->springs) {
                    menuPtr->menuScreen->draw(spring->line, 2, sf::Lines);
                }
            }

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
