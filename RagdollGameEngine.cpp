#include "RagdollGameEngine.h"
#include "Softbody.h"

RagdollGameEngine::RagdollGameEngine(MenuScreen* menu) {
    menuPtr = menu;
    initGame();
}

void RagdollGameEngine::initGame() {
    Node* A = new Node();
    // A->position = PhysVector2<float>(400.f, 400.f);
    A->setPosition(400.f, 200.f);

    Node* B = new Node();
    // B->position = PhysVector2<float>(400.f, 600.f);
    B->setPosition(400.f, 400.f);

    node_vector.push_back(A);
    node_vector.push_back(B);

    Spring* spring = new Spring(A, B);
    spring->rest_length = A->dist(*B) / 2;
    spring_vector.push_back(spring);
}

void RagdollGameEngine::update() {
    if (!node_vector.empty()) {
        for (Node* node : node_vector) {
            node->update();
        }
    }
    // node_vector[1]->update();

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

    if(!spring_vector.empty()) {
        for (int i = 0; i < spring_vector.size(); ++i) {
            menuPtr->menuScreen->draw(spring_vector[i]->line, 2, sf::Lines);
        }
    }

    if(!node_vector.empty()) {
        for (int i = 0; i < node_vector.size(); ++i) {
            menuPtr->menuScreen->draw(node_vector[i]->image);
        }
    }

    menuPtr->menuScreen->display();
}
