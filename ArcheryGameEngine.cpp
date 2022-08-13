#include "ArcheryGameEngine.h"

// Arrow::Arrow(sf::Texture &texture) { this->arrowSprite.setTexture(texture); }

BeamCollisionType Arrow::updateMovement(bool &isArrowPresent, const double drag, const double grav, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, Archer archer) {
    arrowSprite.move( std::real(arrow_velocity), std::imag(arrow_velocity) );
    arrowSprite.setRotation(std::arg(arrow_velocity)); // Might need to change the origin of the arrow to (0,0) here
    arrow_velocity -= std::complex<float>(drag, grav);

    if (arrowSprite.getGlobalBounds().height > archer.archerSprite.getGlobalBounds().height) { // Hits bottom/floor/ground
        isArrowPresent = !isArrowPresent;
        return BeamCollisionType::boundary;
    } else if (arrowSprite.getGlobalBounds().intersects(plat1.getGlobalBounds()) || arrowSprite.getGlobalBounds().intersects(plat2.getGlobalBounds()) || arrowSprite.getGlobalBounds().intersects(plat3.getGlobalBounds())) {
        isArrowPresent = !isArrowPresent;
        return BeamCollisionType::mushroom;
    } else if (arrowSprite.getGlobalBounds().intersects(archer.archerSprite.getGlobalBounds())) {
        isArrowPresent = !isArrowPresent;
        return BeamCollisionType::centipede;
    }
    return BeamCollisionType::nan_;
}

ArcheryGameEngine::ArcheryGameEngine(MenuScreen* menu){
    menuPtr = menu;
    gameView = new sf::View(sf::Vector2f(menu->menuScreen->getSize().x/2,menu->menuScreen->getSize().y/2) , sf::Vector2f(menu->menuScreen->getSize().x,menu->menuScreen->getSize().y));
    initGame();
}

ArcheryGameEngine::~ArcheryGameEngine(){

}

void ArcheryGameEngine::initGame(){

    //Background
    if (!backgroundTexture.loadFromFile("images/Archery/Background.png")) {
        menuPtr->menuScreen->close();
    }
    backgroundSprite.setTexture(backgroundTexture);

    //Archers
    Archer player1;
    if (!player1.archerTexture.loadFromFile("images/Archery/PlayerRight.png")) {
        menuPtr->menuScreen->close();
    }
    player1.archerSprite.setTexture(player1.archerTexture);

    Archer player2;
    if (!player2.archerTexture.loadFromFile("images/Archery/PlayerLeft.png")) {
        menuPtr->menuScreen->close();
    }
    player2.archerSprite.setTexture(player2.archerTexture);

    //Arrows
    arrow1 = new Arrow();
    if (!arrowTexture.loadFromFile("images/Archery/temp_arrow.png")) { // Need to add this image
        menuPtr->menuScreen->close();
    }
    //Platforms
    if (!platformTexture.loadFromFile("images/Archery/Platform.png")) {
        menuPtr->menuScreen->close();
    }

    platform1.setTexture(platformTexture);

    platform2.setTexture(platformTexture);

    platform3.setTexture(platformTexture);




}

void ArcheryGameEngine::update(){

    sf::Vector2f mousePosition = menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen));

    while (menuPtr->menuScreen->pollEvent(ev)) {
        switch (ev.type) {

            case sf::Event::EventType::Closed:
                menuPtr->currentGameType = NULL_GAME;
                break;

            case sf::Event::MouseButtonReleased:
                // Maybe we have an isArrowMoving boolean here to let the computer know that we have released the arrow.
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_mouse_first_pressed) { // Works when the bow is drawn; i.e., when LMB is STILL being pressed
                    // stuff
                    std::cout << arrow1->arrow_velocity << " = (" << std::abs(arrow1->arrow_velocity) << ", " << std::arg(arrow1->arrow_velocity) * 180 / M_PI << ")" << std::endl;
                    is_mouse_first_pressed = false;
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Playing around with click and drag type archery game
                    initial_mouse_pos = sf::Mouse::getPosition(*menuPtr->menuScreen);
                    // Initial - final is calculated to account for the fact that the velocity vector v = -1 * drawn_vector
                    line[0] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x, initial_mouse_pos.y ) );
                    line[1] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x, initial_mouse_pos.y ) );
                    is_mouse_first_pressed = true;
                }
                break;

            case sf::Event::MouseMoved:
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    std::complex<double> temp_complex(initial_mouse_pos.x - ev.mouseMove.x, initial_mouse_pos.y - ev.mouseMove.y); // Makes a vector at the origin the same size of the vector correpsonding to intial mouse & mouse movement

                    if ( std::abs( temp_complex )  > LINE_LENGTH ) { // Resizing the drawn line to LINE_LENGTH if it's too big
                        temp_complex *= 1 / std::abs(temp_complex) * LINE_LENGTH;
                        line[1] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x - std::real(temp_complex), initial_mouse_pos.y - std::imag(temp_complex)) );
                    } else {
                        line[1] = sf::Vertex( sf::Vector2f( ev.mouseMove.x, ev.mouseMove.y ) );
                    }
                    arrow1->arrow_velocity = temp_complex * ((1.0 / LINE_LENGTH) * MAX_ARROW_POWER); // v_f = (v_i / |v_i|) * (|v_i| / LINE_LENGTH * MAX_ARROW_POWER)
                }
        }
    }
}

void ArcheryGameEngine::render(){

    menuPtr->menuScreen->setView(*gameView);
    menuPtr->menuScreen->clear();
    menuPtr->menuScreen->draw(line, 2, sf::Lines);

    menuPtr->menuScreen->display();

}
