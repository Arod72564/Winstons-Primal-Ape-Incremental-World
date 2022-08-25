#include "RagdollGameEngine.h"
#include "SoftBody.h"

RagdollGameEngine::RagdollGameEngine(MenuScreen* menu) {
    menuPtr = menu;
    initGame();
}

RagdollGameEngine::~RagdollGameEngine() {
    if (!softbody_vector.empty()) {
        for (SoftBody* softbody : softbody_vector) {
            delete softbody;
        }
    }

}

void RagdollGameEngine::initGame() {
    clock.restart();

    float min = 195.f;
    float max = 255.f;
    SoftBody* temp = new SoftBody();
    temp->buildRect(200.f, 200.f, 5, 5, 15.f, 5.f, 2.5f, 140.5f);
    // temp->nodes.at(0).at(0)->setPosition(min, min);
    // temp->nodes.at(0).at(9)->setPosition(max, min);
    // temp->nodes.at(9).at(0)->setPosition(min, max);
    // temp->nodes.at(9).at(9)->setPosition(max, max);
    // temp->nodes.at(4).at(4)->image.move(100.f, 100.f);
    // temp->nodes.at(4).at(4)->setPosition(temp->nodes.at(4).at(4)->image.getPosition().x, temp->nodes.at(4).at(4)->image.getPosition().y);
    softbody_vector.push_back(temp);
}

void RagdollGameEngine::update() {

    while(menuPtr->menuScreen->pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::EventType::Closed:
                menuPtr->currentGameType = NULL_GAME;
                break;

            case sf::Event::EventType::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    for (SoftBody* softBody : softbody_vector) {
                        softBody->showSolid = !(softBody->showSolid);
                    }
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    std::cout << "LMB Pressed" << std::endl;
                    
                    initialClickPoint(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)));

                    for (SoftBody* softBody : softbody_vector) {
                        if (softBody->solidSoftBody->getGlobalBounds().contains(initialClickPoint.toSF())) { //check if you are clicked on softbody
                            clickedSoftbody = softBody;
                            for (std::vector<Node *> nodes :  clickedSoftbody->nodes) {
                                for (Node* node : nodes) {
                                    if (node->image.getGlobalBounds().contains(initialClickPoint.toSF())) {
                                        clickedNode = node;
                                    }
                                }
                            }
                        //check if you clicked on a node
                        isMouseFirstClicked = true;
                        softBody->isClicked = true;

                        if(clickedNode != nullptr) {
                            line[0] = sf::Vertex(menuPtr->menuScreen->mapPixelToCoords(sf::Vector2i(clickedNode->position.toSF())));
                            line[1] = sf::Vertex(menuPtr->menuScreen->mapPixelToCoords(sf::Vector2i(clickedNode->position.toSF())));
                            isLineDrawn = true;
                            std::cout << "Line Started at node" << std::endl;
                        }
                        
                        
                        
                            
                        }
                    }
                }
                
                break;

            case sf::Event::MouseButtonReleased:
                if(isMouseFirstClicked) {
                    //Stop dragging
                    isMouseFirstClicked = false;
                    clickedSoftbody->isClicked = false;
                    clickedNode = nullptr;
                    clickedSoftbody = nullptr;
                    isLineDrawn = false;
                    std::cout << "Mouse Released" << std::endl;
                }

                break;

            // case sf::Event::MouseMoved:
            //     if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickedSoftbody != nullptr) {
            //         line[0] = sf::Vertex(clickedSoftbody->solidSoftBody->getPosition());
            //         line[1] = sf::Vertex(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)));

            //         PhysVector2<float> temp = PhysVector2<float>(line[1].position.x - line[0].position.x, line[1].position.y - line[0].position.y);
                    
            //         if (temp.mag() >  maxDragForce) {
            //             temp = temp.normalize() * maxDragForce;
            //         }

            //         f_mouse = temp;

            //     }

            //     break;
        }
    }

    if (isLineDrawn && clickedSoftbody != nullptr && clickedNode != nullptr) {
        line[0] = sf::Vertex(menuPtr->menuScreen->mapPixelToCoords(sf::Vector2i(clickedNode->position.toSF())));
        line[1] = sf::Vertex(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)));

        PhysVector2<float> temp = PhysVector2<float>(line[1].position.x - line[0].position.x, line[1].position.y - line[0].position.y);
        
        if (temp.mag() >  maxDragForce) {
            temp = temp.normalize() * maxDragForce;
        }

        f_mouse = temp - clickedSoftbody->CoM->velocity * clickedSoftbody->softBodyDamping;
        std::cout << "Line Updated, solid soft body at " << clickedSoftbody->CoM->position.x << ", " << clickedSoftbody->CoM->position.y << std::endl;
    }


    f_ext = drag;

    if(!softbody_vector.empty()) {
        float temp_time = clock.restart().asSeconds();
        for(SoftBody* softbody : softbody_vector) {
            // if (temp_time < DT) softbody->update(DT, f_ext, GRAV);
            // else softbody->update(temp_time, f_ext, GRAV);

            // For testing
            if (softbody->isClicked) {
                softbody->update(DT, f_ext, GRAV, clickedNode, f_mouse);
            } else {
                softbody->update(DT, f_ext, GRAV);
            }
        }
    }

    f_ext(0,0);
    f_mouse(0,0);
}

void RagdollGameEngine::render() {
    menuPtr->menuScreen->clear();

    if(isLineDrawn){
        menuPtr->menuScreen->draw(line, 2, sf::Lines);
    }

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
