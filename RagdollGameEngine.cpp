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
    temp->buildRect(200.f, 200.f, 4, 4, 15.f, 5.f, 1.5f, 3.5f);
    // temp->nodes.at(0).at(0)->setPosition(min, min);
    // temp->nodes.at(0).at(9)->setPosition(max, min);
    // temp->nodes.at(9).at(0)->setPosition(min, max);
    // temp->nodes.at(9).at(9)->setPosition(max, max);
    temp->nodes.at(0).at(0)->image.move(-240.f, -240.f);
    temp->nodes.at(0).at(0)->setPosition(temp->nodes.at(0).at(0)->image.getPosition().x, temp->nodes.at(0).at(0)->image.getPosition().y);
    temp->showSolid = true;
    softbody_vector.push_back(temp);

    SoftBody* bar = new SoftBody();
    bar->buildRect(400.f, 200.f, 4, 4, 15.f, 5.f, 1.5f, 3.5f);
    bar->nodes.at(0).at(0)->image.move(-240.f, -240.f);
    bar->nodes.at(0).at(0)->setPosition(bar->nodes.at(0).at(0)->image.getPosition().x, bar->nodes.at(0).at(0)->image.getPosition().y);

    softbody_vector.push_back(bar);


}

void RagdollGameEngine::update() {
    f_ext = drag;
    if(!softbody_vector.empty()) {
        float temp_time = clock.restart().asSeconds();
        for(SoftBody* softbody : softbody_vector) {
            // if (temp_time < DT) softbody->update(DT, f_ext, GRAV);
            // else softbody->update(temp_time, f_ext, GRAV);

            // For testing
            // if (temp_time < DT) softbody->update(DT, f_ext, 0.f);
            // else softbody->update(temp_time, f_ext, 0.f);

            softbody->update(DT, f_ext, GRAV);
            // std::cout << temp_time << std::endl;
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
            if (softbody->showSolid) {
                menuPtr->menuScreen->draw(*(softbody->solidSoftBody));
            } else {
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
            // menuPtr->menuScreen->draw(*(softbody->solidSoftBody), softbody->solidSoftBody->getVertexCount(), sf::LineStrip);

        }
    }

    menuPtr->menuScreen->display();
}
