#include "ArcheryGameEngine.h"

void BloodSplat::createBloodSplat(const sf::Vector2f init_position, std::complex<float> intake_velocity, std::default_random_engine generator, std::normal_distribution<float> norm_dist, int parts) {
    particles.resize(parts);
    blood.resize(parts);
    NUM_OF_PARTS = parts;

    if (std::real(intake_velocity) < 0) {
        norm_dist = std::normal_distribution<float>(-0.4f, 0.4f);
    } else {
        norm_dist = std::normal_distribution<float>(0.4f, 0.4f);
    }

    intake_velocity /= 10;
    float temp_abs;
    for (int i = 0; i < particles.size() ; i++) {
        blood[i].position = init_position;
        blood[i].color = sf::Color::Red;

        particles[i].x = intake_velocity.real() + norm_dist(generator);
        particles[i].y = intake_velocity.imag() + norm_dist(generator);
        temp_abs = std::sqrt( std::pow(particles[i].x, 2) + std::pow(particles[i].y, 2) );
        if (temp_abs > MAX_SPEED) particles[i] *= 1 / temp_abs * MAX_SPEED;
    }

}

void BloodSplat::updateMovement() {
    for (int i = 0; i < particles.size(); i++) {
        particles[i].y += 0.01f;
        blood[i].position += particles[i];

    }
}

Arrow::Arrow(sf::Texture &texture, float x, float y, std::complex<float> velocity) {
    arrowSprite.setTexture(texture);
    arrowSprite.setPosition(x, y);
    arrow_velocity = velocity;
}

ArrowCollisionType Arrow::updateMovement(bool &isArrowPresent, MenuScreen* menuPtr, std::complex<float> drag, const float grav, sf::Sprite bgSprite, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, sf::Sprite self, sf::Sprite enemyHead, sf::Sprite enemyTorso, sf::Sprite enemyLegs) {
    arrowSprite.move( std::real(arrow_velocity), std::imag(arrow_velocity) );
    arrow_velocity += std::complex<float>(std::real(drag), std::imag(drag) + grav);
    arrowSprite.setRotation(std::arg(arrow_velocity) * 180 / M_PI);

    if ( !bgSprite.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) ) {
        isArrowPresent = !isArrowPresent;
        return ArrowCollisionType::background; //background boundary
    } else if ( enemyHead.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) ) {
        isArrowPresent = !isArrowPresent;
        arrowSprite.move( std::real(arrow_velocity), std::imag(arrow_velocity) );
        arrowSprite.setRotation(std::arg(arrow_velocity) * 180 / M_PI);
        // frame_time = 0;
        return ArrowCollisionType::archer_head; //archer
    } else if ( enemyTorso.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) ) {
        isArrowPresent = !isArrowPresent;
        arrowSprite.move( std::real(arrow_velocity), std::imag(arrow_velocity) );
        arrowSprite.setRotation(std::arg(arrow_velocity) * 180 / M_PI);
        // frame_time = 0;
        return ArrowCollisionType::archer_torso; //archer
    } else if ( enemyLegs.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) ) {
        isArrowPresent = !isArrowPresent;
        arrowSprite.move( std::real(arrow_velocity), std::imag(arrow_velocity) );
        arrowSprite.setRotation(std::arg(arrow_velocity) * 180 / M_PI);
        // frame_time = 0;
        return ArrowCollisionType::archer_legs; //archer
    }
     else if (plat1.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) || plat2.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) || plat3.getGlobalBounds().intersects(arrowSprite.getGlobalBounds())) {
        frame_time = 0;
        isArrowPresent = !isArrowPresent;
        return ArrowCollisionType::platform; //platform
    }
    return ArrowCollisionType::none;
}

ArcheryGameEngine::ArcheryGameEngine(MenuScreen* menu){
    menuPtr = menu;
    gameView = new sf::View(sf::Vector2f(menu->menuScreen->getSize().x/2,menu->menuScreen->getSize().y/2) , sf::Vector2f(menu->menuScreen->getSize().x,menu->menuScreen->getSize().y));
    initGame();
}

ArcheryGameEngine::~ArcheryGameEngine(){
    delete gameView;
    if (!archer1.arrow_vector.empty()) {
        for (int i = 0; i < archer1.arrow_vector.size(); ++i) {
            delete archer1.arrow_vector[i];
        }
    }

    if (!archer2.arrow_vector.empty()) {
        for (int i = 0; i < archer2.arrow_vector.size(); ++i) {
            delete archer2.arrow_vector[i];
        }
    }

}

void ArcheryGameEngine::initGame(){
    is_player_turn = true;
    // Initializing RNG
    std::srand(std::time(nullptr));

    drag = std::polar<float>( ((rand() % 301 + 100) / 10000.f), ((rand() % 361) * M_PI / 180 ));
    // drag = std::complex<float> (-0.005f,0.005f);
    // drag = std::polar<float>(0.02, M_PI);

    //Text
    if (!textFont.loadFromFile("fonts/ARLRDBD.TTF")) {

    }
    arrowDeg.setFont(textFont);
    arrowDeg.setScale(0.5f, 0.5f);
    arrowPower.setFont(textFont);
    arrowPower.setScale(0.5f, 0.5f);

    //Background
    if (!backgroundTexture.loadFromFile("images/Archery/Background.png")) {
        menuPtr->menuScreen->close();
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setOrigin(backgroundSprite.getGlobalBounds().width / 2, backgroundSprite.getGlobalBounds().height / 2);
    backgroundSprite.setScale(2.5,3);
    backgroundSprite.setPosition(menuPtr->menuScreen->getSize().x / 2, -250);

    //Archers
        // Archer player1;
    if (!archer1.archerTorsoTexture.loadFromFile("images/Archery/PlayerRightTorso2.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.archerArmTexture.loadFromFile("images/Archery/PlayerRightArm.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.archerHeadTexture.loadFromFile("images/Archery/PlayerRightHead.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.archerLegsTexture.loadFromFile("images/Archery/PlayerRightLegs.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.healthBar.loadFromFile("images/Archery/MissingHP.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.remainingHealth.loadFromFile("images/Archery/HP.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.archerHeadHitBox.loadFromFile("images/Archery/headCollisionBox.png")) {
        menuPtr->menuScreen->close();
    }


    archer1.archerHeadSprite.setTexture(archer1.archerHeadTexture);
    archer1.archerHeadSprite.setPosition(-1000, 700);

    archer1.archerHeadHitBoxSprite.setTexture(archer1.archerHeadHitBox);
    archer1.archerHeadHitBoxSprite.setColor(sf::Color::Red);
    archer1.archerHeadHitBoxSprite.setPosition(archer1.archerHeadSprite.getPosition().x + 3, archer1.archerHeadSprite.getPosition().y + 3);

    archer1.archerTorsoSprite.setTexture(archer1.archerTorsoTexture);
    archer1.archerTorsoSprite.setPosition(archer1.archerHeadSprite.getPosition().x, archer1.archerHeadSprite.getPosition().y + archer1.archerHeadSprite.getGlobalBounds().height);

    archer1.archerLegsSprite.setTexture(archer1.archerLegsTexture);
    archer1.archerLegsSprite.setPosition(archer1.archerTorsoSprite.getPosition().x - 4, archer1.archerTorsoSprite.getPosition().y + archer1.archerTorsoSprite.getGlobalBounds().height);

    archer1.archerArmSprite.setTexture(archer1.archerArmTexture);
    archer1.archerArmSprite.setOrigin(archer1.archerArmSprite.getGlobalBounds().width / 2, archer1.archerArmSprite.getGlobalBounds().height / 2);
    archer1.archerArmSprite.setPosition(archer1.archerTorsoSprite.getPosition().x + (archer1.archerTorsoSprite.getGlobalBounds().width / 2), archer1.archerTorsoSprite.getPosition().y + (archer1.archerTorsoSprite.getGlobalBounds().height / 2) - 15);

    archer1.healthBarSprite.setTexture(archer1.healthBar);
    archer1.healthBarSprite.setColor(sf::Color(255,0,0,150));
    archer1.healthBarSprite.setPosition(archer1.archerTorsoSprite.getPosition().x - (archer1.healthBarSprite.getGlobalBounds().width / 2) + 10, archer1.archerHeadSprite.getPosition().y - 30);

    archer1.remainingHealthSprite.setTexture(archer1.remainingHealth);
    archer1.remainingHealthSprite.setPosition(archer1.archerTorsoSprite.getPosition().x - (archer1.healthBarSprite.getGlobalBounds().width / 2) + 10, archer1.archerHeadSprite.getPosition().y - 30);

        // Archer player2;
    player_dist_deviation = (rand() % 200 - 100);

    if (!archer2.archerTorsoTexture.loadFromFile("images/Archery/PlayerLeftTorso.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer2.archerArmTexture.loadFromFile("images/Archery/PlayerLeftArm.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer2.archerHeadTexture.loadFromFile("images/Archery/PlayerLeftHead.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer2.archerLegsTexture.loadFromFile("images/Archery/PlayerLeftLegs.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer2.healthBar.loadFromFile("images/Archery/MissingHP.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer2.remainingHealth.loadFromFile("images/Archery/HP.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer2.archerHeadHitBox.loadFromFile("images/Archery/headCollisionBox.png")) {
        menuPtr->menuScreen->close();
    }

    archer2.archerHeadSprite.setTexture(archer2.archerHeadTexture);
    archer2.archerHeadSprite.setPosition(archer1.archerHeadSprite.getPosition().x + PLAYER_DIST + player_dist_deviation, archer1.archerHeadSprite.getPosition().y);

    archer2.archerHeadHitBoxSprite.setTexture(archer2.archerHeadHitBox);
    archer2.archerHeadHitBoxSprite.setPosition(archer2.archerHeadSprite.getPosition().x + 3, archer2.archerHeadSprite.getPosition().y + 3);

    archer2.archerTorsoSprite.setTexture(archer2.archerTorsoTexture);
    archer2.archerTorsoSprite.setPosition(archer2.archerHeadSprite.getPosition().x, archer2.archerHeadSprite.getPosition().y + archer2.archerHeadSprite.getGlobalBounds().height);

    archer2.archerLegsSprite.setTexture(archer2.archerLegsTexture);
    archer2.archerLegsSprite.setPosition(archer2.archerTorsoSprite.getPosition().x, archer2.archerTorsoSprite.getPosition().y + archer2.archerTorsoSprite.getGlobalBounds().height);

    archer2.archerArmSprite.setTexture(archer2.archerArmTexture);
    archer2.archerArmSprite.setOrigin(archer2.archerArmSprite.getGlobalBounds().width / 2, archer2.archerArmSprite.getGlobalBounds().height / 2);
    archer2.archerArmSprite.setPosition(archer2.archerTorsoSprite.getPosition().x + (archer2.archerTorsoSprite.getGlobalBounds().width / 2), archer2.archerTorsoSprite.getPosition().y + (archer2.archerTorsoSprite.getGlobalBounds().height / 2) - 15);

    archer2.healthBarSprite.setTexture(archer2.healthBar);
    archer2.healthBarSprite.setColor(sf::Color(255,0,0,150));
    archer2.healthBarSprite.setPosition(archer2.archerTorsoSprite.getPosition().x - (archer2.healthBarSprite.getGlobalBounds().width / 2) + 10, archer2.archerHeadSprite.getPosition().y - 30);

    archer2.remainingHealthSprite.setTexture(archer2.remainingHealth);
    archer2.remainingHealthSprite.setPosition(archer2.archerTorsoSprite.getPosition().x - (archer2.healthBarSprite.getGlobalBounds().width / 2) + 10, archer2.archerHeadSprite.getPosition().y - 30);


    //Platforms
    if (!platformTexture.loadFromFile("images/Archery/Platform.png")) {
        menuPtr->menuScreen->close();
    }

    platform1.setTexture(platformTexture);
    platform1.setPosition(archer1.archerLegsSprite.getPosition().x - 40, archer1.archerLegsSprite.getPosition().y + 0.9 * archer1.archerLegsSprite.getGlobalBounds().height);

    platform2.setTexture(platformTexture);
    platform2.setPosition(archer2.archerLegsSprite.getPosition().x - 40, archer2.archerLegsSprite.getPosition().y + 0.9 * archer2.archerLegsSprite.getGlobalBounds().height);

    platform3.setTexture(platformTexture);
    platform3.setPosition(archer1.archerTorsoSprite.getPosition().x + PLAYER_DIST / 2, 400);
    platform3.setRotation(-90);
    platform3.setScale(2.5, 1);

    //Arrows

    if (!arrowTexture.loadFromFile("images/Archery/temp_arrow2.png")) {
        menuPtr->menuScreen->close();
    } else if (!arrowTexture2.loadFromFile("images/Archery/temp_arrow3.png")) {
        menuPtr->menuScreen->close();
    } else if (!arrowTexture3.loadFromFile("images/Archery/temp_arrow.png")) {
        menuPtr->menuScreen->close();
    }

    //Wind Indicator and Compass
    wind_indicator.setTexture(arrowTexture3);
    wind_indicator.setOrigin(wind_indicator.getGlobalBounds().width / 2, wind_indicator.getGlobalBounds().height / 2);
    wind_indicator.setScale(0.1, 0.1);
    wind_indicator.setPosition(archer1.archerTorsoSprite.getPosition().x - 300, archer1.archerTorsoSprite.getPosition().y - 300);

    compass = sf::CircleShape(wind_indicator.getGlobalBounds().width / 2, 30);
    compass.setOrigin(wind_indicator.getGlobalBounds().width / 2, wind_indicator.getGlobalBounds().width / 2);
    compass.setPosition(wind_indicator.getPosition());
    compass.setFillColor(sf::Color(135,145,255,150));
    compass.setOutlineThickness(1.f);

    //Win/Lose Screen

    if (!loseScreenTexture.loadFromFile("images/Archery/LostScreen.png")) {
        menuPtr->menuScreen->close();
    } else if (!winScreenTexture.loadFromFile("images/Archery/WinScreen.png")) {
        menuPtr->menuScreen->close();
    }

    loseScreenSprite.setTexture(loseScreenTexture);
    loseScreenSprite.setPosition(0,0);

    winScreenSprite.setTexture(winScreenTexture);
    winScreenSprite.setPosition(0,0);

    //Set initial view to player 1
    gameView->setCenter( archer1.archerTorsoSprite.getPosition() );

    //bloodSplat.createBloodSplat(sf::Vector2f(400,400), std::complex<float>(0, g), generator, norm_dist);

}

void ArcheryGameEngine::update(){

    bloodSplat.updateMovement();

    sf::Vector2f mousePosition = menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen));

    wind_indicator.setPosition(menuPtr->menuScreen->mapPixelToCoords(sf::Vector2i(100, 100)));
    compass.setPosition(menuPtr->menuScreen->mapPixelToCoords(sf::Vector2i(100, 100)));

    if (platform3.getPosition().y < 0 - backgroundSprite.getGlobalBounds().height / 4 || platform3.getPosition().y + platform3.getGlobalBounds().height > backgroundSprite.getGlobalBounds().height / 4 + WINDOW_HEIGHT) {
        platform3_move *= -1;
    }

    platform3.move(0, platform3_move);

/********************************************** For continuously updating drag
    // if (turn_counter == 0) {
    //     float temp_deg_change = ((rand() % 21) - 10) * M_PI / 180.f;
    //     wind_deg_increment = temp_deg_change / WIND_CHANGE_FREQ;
    //     drag *= std::polar<float>( norm_dist(generator), 0.f );
    //     wind_indicator.setRotation( std::arg(drag) * 180 / M_PI );
    //     if (std::abs(drag) < 1e-5) drag *= 1 / std::abs(drag) * 0.002;
    // }
    // turn_counter = (turn_counter + 1) % WIND_CHANGE_FREQ;
    // drag *= std::polar<float>(1.f, wind_deg_increment);

******************************************************************************/

    if (turn_counter == 0) {
        drag *= std::polar<float>( norm_dist(generator), ((rand() % 21) - 10) * M_PI / 180.f );
        wind_indicator.setRotation( std::arg(drag) * 180 / M_PI );
        turn_counter = (turn_counter + 1) % WIND_CHANGE_FREQ;
        // std::cout << drag << std::endl;
    }

    if (is_arrow_present) {
        if (is_player_turn) {
            collisionType = arrow1->updateMovement(is_arrow_present, menuPtr, drag, g, backgroundSprite, platform1, platform2, platform3, archer1.archerTorsoSprite, archer2.archerHeadHitBoxSprite, archer2.archerTorsoSprite, archer2.archerLegsSprite);
        } else {
            collisionType = arrow1->updateMovement(is_arrow_present, menuPtr, drag, g, backgroundSprite, platform1, platform2, platform3, archer2.archerTorsoSprite, archer1.archerHeadHitBoxSprite, archer1.archerTorsoSprite, archer1.archerLegsSprite);
        }

        gameView->setCenter( arrow1->arrowSprite.getPosition() );

        if (collisionType == ArrowCollisionType::archer_head) {
            bloodSplat.createBloodSplat(arrow1->arrowSprite.getPosition(), arrow1->arrow_velocity, generator, norm_dist, 1E4);
            if (is_player_turn) {
                archer2.arrow_vector.push_back(arrow1);
                archer2.health -= 15;
                arrow1 = nullptr;
            } else {
                archer1.arrow_vector.push_back(arrow1);
                archer1.health -= 15;
                arrow1 = nullptr;
            }
        } else if (collisionType == ArrowCollisionType::archer_torso) {
            bloodSplat.createBloodSplat(arrow1->arrowSprite.getPosition(), arrow1->arrow_velocity, generator, norm_dist, 1E3);
            if (is_player_turn) {
                archer2.arrow_vector.push_back(arrow1);
                archer2.health -= 10;
                arrow1 = nullptr;
            } else {
                archer1.arrow_vector.push_back(arrow1);
                archer1.health -= 10;
                arrow1 = nullptr;
            }
        } else if (collisionType == ArrowCollisionType::archer_legs) {
            bloodSplat.createBloodSplat(arrow1->arrowSprite.getPosition(), arrow1->arrow_velocity, generator, norm_dist, 1E2);
            if (is_player_turn) {
                archer2.arrow_vector.push_back(arrow1);
                archer2.health-= 5;
                arrow1 = nullptr;
            } else {
                archer1.arrow_vector.push_back(arrow1);
                archer1.health-= 5;
                arrow1 = nullptr;
            }
        }

        if (collisionType != ArrowCollisionType::none) {
            delete arrow1;
            arrow1 = nullptr;
            collisionType = ArrowCollisionType::none;
            is_player_turn = !(is_player_turn);
            if (is_player_turn) {
                pan(archer1.archerTorsoSprite);
            } else {
                pan(archer2.archerTorsoSprite);
            }
            v = std::complex<float>(0.f,0.f);
            is_panning = true;
        }
    } else if (is_panning) {
        if(pan_counter < 100) {
            gameView->move(std::real(panSpeed), std::imag(panSpeed));
            pan_counter++;
        } else {
            is_panning = false;
        }
    } else if (!is_player_turn && archer1.health > 0 && archer2.health > 0) {
        arrow1 = new Arrow( arrowTexture, archer2.archerArmSprite.getPosition().x, archer2.archerArmSprite.getPosition().y, calculateEnemyV(GameDifficulty::HARD));
        arrow1->arrowSprite.setOrigin(arrow1->arrowSprite.getGlobalBounds().width / 2, arrow1->arrowSprite.getGlobalBounds().height / 2);
        arrow1->arrowSprite.setScale(0.07, 0.04);
        archer2.archerArmSprite.setRotation((std::arg(arrow1->arrow_velocity) * 180 / M_PI) - 180);
        is_arrow_present = true;
    }

    archer1.remainingHealthSprite.setScale((archer1.health / 100) , 1);
    archer2.remainingHealthSprite.setScale((archer2.health / 100) , 1);

    if (archer1.health > 0 && archer2.health > 0) {
        while (menuPtr->menuScreen->pollEvent(ev)) {
            is_a_turn = is_arrow_present || is_panning;
            switch (ev.type) {

                case sf::Event::EventType::Closed:
                    gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                    menuPtr->currentGameType = NULL_GAME;
                    break;

                case sf::Event::MouseButtonReleased:
                    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_mouse_first_pressed && !is_a_turn) {
                        arrow1 = new Arrow(arrowTexture2, archer1.archerArmSprite.getPosition().x, archer1.archerArmSprite.getPosition().y, v);
                        arrow1->arrowSprite.setOrigin(arrow1->arrowSprite.getGlobalBounds().width / 2, arrow1->arrowSprite.getGlobalBounds().height / 2);
                        arrow1->arrowSprite.setScale(0.07, 0.04);
                        turn_counter = (turn_counter + 1) % WIND_CHANGE_FREQ;
                        is_mouse_first_pressed = false;
                        is_arrow_present = true;
                        drawline = false;
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_mouse_first_pressed && !is_a_turn) {
                        // Playing around with click and drag type archery game
                        initial_mouse_pos = menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen));
                        v = std::complex<float>(0.f,0.f);
                        // Initial - final is calculated to account for the fact that the velocity vector v = -1 * drawn_vector
                        float temp = std::arg(v) * 180 / M_PI;
                        arrowDeg.setString(std::to_string(temp));
                        arrowDeg.setPosition(initial_mouse_pos.x, initial_mouse_pos.y - 20);

                        line[0] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x, initial_mouse_pos.y) );
                        line[1] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x, initial_mouse_pos.y) );
                        is_mouse_first_pressed = true;
                        drawline = true;
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuPtr->muteButtonSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) {
                        if(menuPtr->is_MenuMusic_Paused){
                            menuPtr->menuMusic.play();
                        } else {
                            menuPtr->menuMusic.pause();
                        }
                        menuPtr->is_MenuMusic_Paused = !(menuPtr->is_MenuMusic_Paused);
                        }
                    break;

                case sf::Event::MouseMoved:
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_mouse_first_pressed && !is_a_turn) {
                        final_mouse_pos = menuPtr->menuScreen->mapPixelToCoords(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y));
                        calculateLine(arrow1);
                        archer1.archerArmSprite.setRotation(std::arg(v) * 180 / M_PI);
                    }
            }
        }
    } else {
        while (menuPtr->menuScreen->pollEvent(ev)) {
            switch (ev.type) {
            case sf::Event::Closed:
            case sf::Event::MouseButtonPressed:
            case sf::Event::KeyPressed:
                gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                menuPtr->currentGameType = NULL_GAME;
                break;
            
            default:
                break;
            }
        }
    }

        if (archer1.health <= 0) {
            loseScreenSprite.setPosition(menuPtr->menuScreen->mapPixelToCoords(sf::Vector2i(0, 0)));
        } else if (archer2.health <= 0) {
            winScreenSprite.setPosition(menuPtr->menuScreen->mapPixelToCoords(sf::Vector2i(0, 0)));
        }

    if (menuPtr->menuMusic.getStatus() == sf::SoundSource::Stopped) { menuPtr->nextSong(); }
}

void ArcheryGameEngine::render(){

    menuPtr->menuScreen->setView(*gameView);
    menuPtr->menuScreen->clear(sf::Color::Black);

    menuPtr->menuScreen->draw(backgroundSprite);

    menuPtr->menuScreen->draw(platform1);
    menuPtr->menuScreen->draw(platform2);
    menuPtr->menuScreen->draw(platform3);

    menuPtr->menuScreen->draw(compass);
    menuPtr->menuScreen->draw(wind_indicator);

    if (drawline) {
        menuPtr->menuScreen->draw(line, 2, sf::Lines);
        menuPtr->menuScreen->draw(arrowPower);
        menuPtr->menuScreen->draw(arrowDeg);
    }

    if(!archer1.arrow_vector.empty()) {
        for (int i = 0; i < archer1.arrow_vector.size(); ++i) menuPtr->menuScreen->draw(archer1.arrow_vector[i]->arrowSprite);
    }

    if(!archer2.arrow_vector.empty()) {
        for (int i = 0; i < archer2.arrow_vector.size(); ++i) menuPtr->menuScreen->draw(archer2.arrow_vector[i]->arrowSprite);
    }

    menuPtr->menuScreen->draw(bloodSplat.blood);

    menuPtr->menuScreen->draw(archer1.archerArmSprite);
    menuPtr->menuScreen->draw(archer1.archerHeadSprite);
    menuPtr->menuScreen->draw(archer1.archerHeadHitBoxSprite);
    menuPtr->menuScreen->draw(archer1.archerTorsoSprite);
    menuPtr->menuScreen->draw(archer1.archerLegsSprite);
    menuPtr->menuScreen->draw(archer1.healthBarSprite);

    if (archer1.health > 0) { 
        menuPtr->menuScreen->draw(archer1.healthBarSprite);
        menuPtr->menuScreen->draw(archer1.remainingHealthSprite);    
    } else {
        menuPtr->menuScreen->draw(archer1.healthBarSprite);
    }
    

    menuPtr->menuScreen->draw(archer2.archerArmSprite);
    menuPtr->menuScreen->draw(archer2.archerHeadSprite);
    menuPtr->menuScreen->draw(archer2.archerHeadHitBoxSprite);
    menuPtr->menuScreen->draw(archer2.archerTorsoSprite);
    menuPtr->menuScreen->draw(archer2.archerLegsSprite);
    menuPtr->menuScreen->draw(archer2.healthBarSprite);

    if (archer2.health > 0) { 
        menuPtr->menuScreen->draw(archer2.healthBarSprite);
        menuPtr->menuScreen->draw(archer2.remainingHealthSprite);    
    } else {
        menuPtr->menuScreen->draw(archer2.healthBarSprite);
    }
    
    if (is_arrow_present) menuPtr->menuScreen->draw(arrow1->arrowSprite);

    if (archer1.health <= 0) {
        menuPtr->menuScreen->draw(loseScreenSprite);
    } else if (archer2.health <= 0) {
        menuPtr->menuScreen->draw(winScreenSprite);
    }

    menuPtr->menuScreen->display();
}

std::complex<float> ArcheryGameEngine::calculateEnemyV(GameDifficulty game_diff) {
    const float G = std::imag(drag) + g;
    float init_angle;
    float velocity;
    float sweet_spot_angle = std::atan2(G, std::real(drag)) + M_PI;
    const float domain_offset = 0.15f;
    float vel_offset;
    // int total_player_dist = archer2.archerTorsoSprite.getPosition().x - archer1.archerTorsoSprite.getPosition().x;
    int total_player_dist = PLAYER_DIST + player_dist_deviation - archer2.archerTorsoSprite.getGlobalBounds().width / 2;
    if (G > 0) {
        if (std::real(drag) > 0) {
            std::uniform_real_distribution<float> distribution(M_PI + domain_offset, sweet_spot_angle - domain_offset);
            init_angle = distribution(generator);
            // init_angle = (M_PI + sweet_spot_angle) / 2;
        } else {
            std::uniform_real_distribution<float> distribution(M_PI + domain_offset, 3.f * M_PI_2 - domain_offset);
            init_angle = distribution(generator);
            // init_angle = (M_PI + 3.f * M_PI_2) / 2;
        }
    } else {
        if (std::real(drag) > 0) {
            std::uniform_real_distribution<float> distribution(sweet_spot_angle + domain_offset, M_PI - domain_offset);
            init_angle = distribution(generator);
            // init_angle = ( sweet_spot_angle + M_PI ) / 2;
        } else {
            std::uniform_real_distribution<float> distribution(M_PI_2 + domain_offset, M_PI - domain_offset);
            init_angle = distribution(generator);
            // init_angle = (M_PI_2 + M_PI) / 2;
        }
    }

    if (game_diff == EASY) {
        std::uniform_real_distribution<float> vel_distribution(-2.f, 2.f);
        vel_offset = vel_distribution(generator);
    }
    else if (game_diff == NORMAL) {
        std::normal_distribution<float> vel_distribution(0.f, 0.3f);
        vel_offset = vel_distribution(generator);
    }
    else if (game_diff == HARD) {
        std::normal_distribution<float> vel_distribution(0.f, 0.1f);
        vel_offset = vel_distribution(generator);
    }
    else {
        std::uniform_real_distribution<float> vel_distribution(0.f, 0.f);
        vel_offset = vel_distribution(generator);
    }

    velocity = std::sqrt(( total_player_dist * G * G) / (G * std::sin(2 * init_angle) - 2 * std::real(drag) * std::sin(init_angle) * std::sin(init_angle)) ) + vel_offset;
    return std::polar<float>(velocity , init_angle);
}


void ArcheryGameEngine::calculateLine(Arrow* const arrow) {
    std::complex<double> temp_complex(initial_mouse_pos.x - final_mouse_pos.x, initial_mouse_pos.y - final_mouse_pos.y); // Makes a vector at the origin the same size of the vector correpsonding to intial mouse & mouse movement

    if ( std::abs( temp_complex )  > LINE_LENGTH ) { // Resizing the drawn line to LINE_LENGTH if it's too big
        temp_complex *= 1 / std::abs(temp_complex) * LINE_LENGTH;
        line[1] = sf::Vertex( sf::Vector2f( initial_mouse_pos.x - std::real(temp_complex), initial_mouse_pos.y - std::imag(temp_complex)) );
    } else {
        line[1] = sf::Vertex( sf::Vector2f( final_mouse_pos.x, final_mouse_pos.y) );
    }

    float temp = (std::abs( temp_complex ) / LINE_LENGTH) * 100;

    os << std::fixed << std::setprecision(2) << temp;
    arrowPower.setString(os.str());
    std::stringstream().swap(os);
    arrowPower.setPosition(line[1].position.x, line[1].position.y + 20);

    os << std::fixed << std::setprecision(2) << std::arg(std::conj(v)) * 180 / M_PI;
    arrowDeg.setString(os.str());
    std::stringstream().swap(os);

    v = temp_complex * ((1.0 / LINE_LENGTH) * MAX_ARROW_POWER); // v_f = (v_i / |v_i|) * (|v_i| / LINE_LENGTH * MAX_ARROW_POWER)
}

void ArcheryGameEngine::pan(sf::Sprite target) {
    pan_counter = 0;

    panSpeed = std::complex<float> (target.getPosition().x - gameView->getCenter().x, target.getPosition().y - gameView->getCenter().y);

    panSpeed /= 100.f;
}