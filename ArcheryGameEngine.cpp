#include "ArcheryGameEngine.h"

Arrow::Arrow(sf::Texture &texture) { this->arrowSprite.setTexture(texture); }

BeamCollisionType Arrow::updateMovement(bool &isArrowPresent, const double grav, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, Archer archer) {
    arrowSprite.move( std::real(arrow_velocity), std::imag(arrow_velocity) );
    arrowSprite.setRotation(std::arg(arrow_velocity)); // Might need to change the origin of the arrow to (0,0) here
    arrow_velocity -= std::complex<double>(0.0, grav);

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
    gameView = new sf::View(sf::Vector2f(0,0) , sf::Vector2f(menu->menuScreen->getSize().x,menu->menuScreen->getSize().y));
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
    // arrow1 = new Arrow();
    if (!arrowTexture.loadFromFile("images/Archery/ArrowTexture.png")) { // Need to add this image
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
                break;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Playing around with click and drag type archery game
                    sf::Vector2i initial_pos = sf::Mouse::getPosition(*menuPtr->menuScreen);
                    sf::Vector2i final_pos;
                    if (!is_arrow_present) {
                        // arrow1 = new Arrow();
                        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            final_pos = sf::Mouse::getPosition(*menuPtr->menuScreen);
                            arrow1->arrow_velocity.real(initial_pos.x - final_pos.x);
                            arrow1->arrow_velocity.imag(initial_pos.y - final_pos.y);
                            /*
                            temp_arrow.arrow_power = sqrt( pow(final_pos.y - initial_pos.y,2) + pow(final_pos.x - intial_pos.x, 2) ) % MAX_ARROW_POWER; // Determine arrow power from dragging of mouse after click
                            if ( abs(final_pos.x - initial_pos.x) > EPSILON ) { // I.e., if you are NOT dividing by 0; this might be extraneous but who knows
                                temp_arrow.arrow_rads = atan2( (final_pos.y - initial_pos.y) / (final_pos.x - intial_pos.x) )
                            } else {
                                temp_arrow.arrow_rads = ( (final_pos.y > initial_pos.y) ? -1 * M_PI_2 : M_PI_2 );
                            }
                            */
                        }
                        if (std::sqrt(std::norm(arrow1->arrow_velocity) > MAX_ARROW_POWER)) {
                            arrow1->arrow_velocity *= 1 / std::sqrt(std::norm(arrow1->arrow_velocity)) * MAX_ARROW_POWER;
                        }
                        is_arrow_present = true;
                    }
                }
                break;

        }
    }
}

void ArcheryGameEngine::render(){

    menuPtr->menuScreen->setView(*gameView);
    menuPtr->menuScreen->display();

}
