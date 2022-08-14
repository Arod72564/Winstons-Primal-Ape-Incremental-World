#include "ArcheryGameEngine.h"

Arrow::Arrow(sf::Texture &texture, float x, float y, std::complex<float> velocity) {
    arrowSprite.setTexture(texture);
    arrowSprite.setPosition(x, y);
    arrow_velocity = velocity;
}

BeamCollisionType Arrow::updateMovement(bool &isArrowPresent, const std::complex<float> drag, const float grav, sf::Sprite bgSprite, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, Archer enemy) {
    arrowSprite.move( std::real(arrow_velocity), std::imag(arrow_velocity) );
    arrowSprite.setRotation(std::arg(arrow_velocity) * 180 / M_PI); // Might need to change the origin of the arrow to (0,0) here
    arrow_velocity += std::complex<float>(std::real(drag), std::imag(drag) + grav);

    if ( !bgSprite.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) ) {
        isArrowPresent = !isArrowPresent;
        return BeamCollisionType::boundary;
    } else if ( enemy.archerSprite.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) ) {
        isArrowPresent = !isArrowPresent;
        return BeamCollisionType::centipede;
    } else if (plat1.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) || plat2.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) || plat3.getGlobalBounds().intersects(arrowSprite.getGlobalBounds())) {
        isArrowPresent = !isArrowPresent;
        return BeamCollisionType::mushroom;
    }
    return BeamCollisionType::nan_;
}

ArcheryGameEngine::ArcheryGameEngine(MenuScreen* menu){
    menuPtr = menu;
    gameView = new sf::View(sf::Vector2f(menu->menuScreen->getSize().x/2,menu->menuScreen->getSize().y/2) , sf::Vector2f(menu->menuScreen->getSize().x,menu->menuScreen->getSize().y));
    initGame();
}

ArcheryGameEngine::~ArcheryGameEngine(){
    delete gameView;
}

void ArcheryGameEngine::initGame(){

    //Background
    if (!backgroundTexture.loadFromFile("images/Archery/Background.png")) {
        menuPtr->menuScreen->close();
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setOrigin(backgroundSprite.getGlobalBounds().width / 2, backgroundSprite.getGlobalBounds().height / 2);
    backgroundSprite.setPosition(menuPtr->menuScreen->getSize().x / 2, menuPtr->menuScreen->getSize().y / 2);

    //Archers
    // Archer player1;
    if (!archer1.archerTexture.loadFromFile("images/Archery/PlayerRight.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.archerArmTexture.loadFromFile("images/Archery/PlayerRightArm.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.archerTorsoTexture.loadFromFile("images/Archery/PlayerRightTorso.png")) {
        menuPtr->menuScreen->close();
    }

    archer1.archerSprite.setTexture(archer1.archerTexture);
    archer1.archerArmSprite.setTexture(archer1.archerArmTexture);
    archer1.archerTorsoSprite.setTexture(archer1.archerTorsoTexture);
    archer1.archerTorsoSprite.setPosition(50, 700);
    archer1.archerArmSprite.setOrigin(archer1.archerArmSprite.getGlobalBounds().width / 2, archer1.archerArmSprite.getGlobalBounds().height / 2);
    archer1.archerArmSprite.setPosition(archer1.archerTorsoSprite.getPosition().x + (archer1.archerTorsoSprite.getGlobalBounds().width / 2), archer1.archerTorsoSprite.getPosition().y + (archer1.archerTorsoSprite.getGlobalBounds().height / 2) - 15);
    //archer1.archerSprite.setPosition(50, 700);

    // Archer player2;
    if (!archer2.archerTexture.loadFromFile("images/Archery/PlayerLeft.png")) {
        menuPtr->menuScreen->close();
    }
    archer2.archerSprite.setTexture(archer2.archerTexture);
    archer2.archerSprite.setPosition(archer1.archerTorsoSprite.getPosition().x + PLAYER_DIST, archer1.archerTorsoSprite.getPosition().y);

    //Arrows
    if (!arrowTexture.loadFromFile("images/Archery/temp_arrow.png")) { // Need to add this image
        menuPtr->menuScreen->close();
    }

    //Platforms
    if (!platformTexture.loadFromFile("images/Archery/Platform.png")) {
        menuPtr->menuScreen->close();
    }

    platform1.setTexture(platformTexture);
    platform1.setPosition(archer1.archerTorsoSprite.getPosition().x, archer1.archerTorsoSprite.getPosition().y + 0.9 * archer1.archerTorsoSprite.getGlobalBounds().height);

    platform2.setTexture(platformTexture);
    platform2.setPosition(archer2.archerSprite.getPosition().x, archer2.archerSprite.getPosition().y + 0.9 * archer2.archerSprite.getGlobalBounds().height);

    platform3.setTexture(platformTexture);




}

void ArcheryGameEngine::update(){

    sf::Vector2f mousePosition = menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen));

    if (is_arrow_present) {
        collisionType = arrow1->updateMovement(is_arrow_present, drag, g, backgroundSprite, platform1, platform2, platform3, archer2);
        switch (collisionType) {
            case boundary:
                delete arrow1;
                collisionType = nan_;
                break;
            case centipede:
                delete arrow1;
                collisionType = nan_;
                break;
            case mushroom:
                delete arrow1;
                collisionType - nan_;
            default:
                break;
        }
    } else {
        while (menuPtr->menuScreen->pollEvent(ev)) {
            switch (ev.type) {

                case sf::Event::EventType::Closed:
                    menuPtr->currentGameType = NULL_GAME;
                    break;

                case sf::Event::MouseButtonReleased:
                    std::cout << "Mouse button released\n";
                    // Maybe we have an isArrowMoving boolean here to let the computer know that we have released the arrow.
                    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_mouse_first_pressed && !is_arrow_present) { // Works when the bow is drawn; i.e., when LMB is STILL being pressed
                        arrow1 = new Arrow(arrowTexture, archer1.archerArmSprite.getPosition().x, archer1.archerArmSprite.getPosition().y, v);
                        arrow1->arrowSprite.setOrigin(arrow1->arrowSprite.getGlobalBounds().width / 2, arrow1->arrowSprite.getGlobalBounds().height / 2);
                        arrow1->arrowSprite.setScale(0.07, 0.04);
                        std::cout << arrow1->arrow_velocity << " = (" << std::abs(arrow1->arrow_velocity) << ", " << std::arg(arrow1->arrow_velocity) * 180 / M_PI << ")" << std::endl;
                        is_mouse_first_pressed = false;
                        is_arrow_present = true;
                        drawline = false;
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_mouse_first_pressed && !is_arrow_present) {
                        // Playing around with click and drag type archery game
                        initial_mouse_pos = sf::Mouse::getPosition(*menuPtr->menuScreen);
                        // Initial - final is calculated to account for the fact that the velocity vector v = -1 * drawn_vector
                        line[0] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x, initial_mouse_pos.y ) );
                        line[1] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x, initial_mouse_pos.y ) );
                        is_mouse_first_pressed = true;
                        drawline = true;
                    }
                    break;

                case sf::Event::MouseMoved:
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) { calculateLine(arrow1); }
                    archer1.archerArmSprite.setRotation(std::arg(v) * 180 / M_PI);
                    // std::cout << ev.mouseMove.x << ", " << ev.mouseMove.y << std::endl;
            }
        }
    }





}

void ArcheryGameEngine::render(){

    menuPtr->menuScreen->setView(*gameView);
    menuPtr->menuScreen->clear(sf::Color::White);
    menuPtr->menuScreen->draw(backgroundSprite);
    menuPtr->menuScreen->draw(platform1);
    menuPtr->menuScreen->draw(platform2);

    if (drawline) {
        menuPtr->menuScreen->draw(line, 2, sf::Lines);
    }
    
    //menuPtr->menuScreen->draw(archer1.archerSprite);

    menuPtr->menuScreen->draw(archer1.archerArmSprite);
    menuPtr->menuScreen->draw(archer1.archerTorsoSprite);

    menuPtr->menuScreen->draw(archer2.archerSprite);

    if (is_arrow_present) {
        menuPtr->menuScreen->draw(arrow1->arrowSprite);
    }

    menuPtr->menuScreen->display();

}

void ArcheryGameEngine::calculateLine(Arrow* const arrow) {
    std::complex<double> temp_complex(initial_mouse_pos.x - ev.mouseMove.x, initial_mouse_pos.y - ev.mouseMove.y); // Makes a vector at the origin the same size of the vector correpsonding to intial mouse & mouse movement

    if ( std::abs( temp_complex )  > LINE_LENGTH ) { // Resizing the drawn line to LINE_LENGTH if it's too big
        temp_complex *= 1 / std::abs(temp_complex) * LINE_LENGTH;
        line[1] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x - std::real(temp_complex), initial_mouse_pos.y - std::imag(temp_complex)) );
    } else {
        line[1] = sf::Vertex( sf::Vector2f( ev.mouseMove.x, ev.mouseMove.y ) );
    }
    v = temp_complex * ((1.0 / LINE_LENGTH) * MAX_ARROW_POWER); // v_f = (v_i / |v_i|) * (|v_i| / LINE_LENGTH * MAX_ARROW_POWER)
}
