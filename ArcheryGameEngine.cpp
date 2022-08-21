#include "ArcheryGameEngine.h"

BloodSplat::BloodSplat(std::complex<float> intake_velocity) {
    intit_velocity = intake_velocity;

}

Arrow::Arrow(sf::Texture &texture, float x, float y, std::complex<float> velocity) {
    arrowSprite.setTexture(texture);
    arrowSprite.setPosition(x, y);
    arrow_velocity = velocity;
}

BeamCollisionType Arrow::updateMovement(bool &isArrowPresent, MenuScreen* menuPtr, std::complex<float> drag, const float grav, sf::Sprite bgSprite, sf::Sprite plat1, sf::Sprite plat2, sf::Sprite plat3, sf::Sprite self, sf::Sprite enemy) {
    // arrowSprite.move( std::real(arrow_velocity), std::imag(arrow_velocity) );
    float x_pos = std::real(arrow_velocity) * frame_time + 0.5f * std::real(drag)          * std::pow(frame_time, 2) + self.getPosition().x;
    float y_pos = std::imag(arrow_velocity) * frame_time + 0.5f * (std::imag(drag) + grav) * std::pow(frame_time, 2) + self.getPosition().y;

    std::complex<float> new_vel = arrow_velocity + std::complex<float>(std::real(drag) * frame_time, (std::imag(drag) + grav) * frame_time);
    // arrowSprite.setPosition( menuPtr->menuScreen->mapPixelToCoords( sf::Vector2i( x_pos, y_pos ) ) );
    arrowSprite.setPosition(x_pos, y_pos);
    arrowSprite.setRotation(std::arg(new_vel) * 180 / M_PI);
    frame_time++;
    // std::cout << frame_time << std::endl;
    // std::cout << self.archerSprite.getPosition().x << ", " << self.archerSprite.getPosition().y << std::endl;
    // std::cout << menuPtr->menuScreen->mapPixelToCoords( sf::Vector2i(self.archerSprite.getPosition().x, self.archerSprite.getPosition().y) ).x << ", " << menuPtr->menuScreen->mapPixelToCoords( sf::Vector2i(self.archerSprite.getPosition().x, self.archerSprite.getPosition().y) ).y << std::endl;
    // arrow_velocity += std::complex<float>(std::real(drag), std::imag(drag) + grav);

    if ( !bgSprite.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) ) {
        frame_time = 0;
        isArrowPresent = !isArrowPresent;
        return BeamCollisionType::boundary;
    } else if ( enemy.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) ) {
        ++frame_time;
        isArrowPresent = !isArrowPresent;
        x_pos = std::real(arrow_velocity) * frame_time + 0.5f * std::real(drag)          * std::pow(frame_time, 2) + self.getPosition().x;
        y_pos = std::imag(arrow_velocity) * frame_time + 0.5f * (std::imag(drag) + grav) * std::pow(frame_time, 2) + self.getPosition().y;
        std::complex<float> new_vel = arrow_velocity + std::complex<float>(std::real(drag) * frame_time, (std::imag(drag) + grav) * frame_time);
        arrowSprite.setPosition(x_pos, y_pos);
        arrowSprite.setRotation(std::arg(new_vel) * 180 / M_PI);
        frame_time = 0;
        return BeamCollisionType::centipede;
    } else if (plat1.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) || plat2.getGlobalBounds().intersects(arrowSprite.getGlobalBounds()) || plat3.getGlobalBounds().intersects(arrowSprite.getGlobalBounds())) {
        frame_time = 0;
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
    norm_dist = std::normal_distribution<float>(1.f, 0.1f);

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
    backgroundSprite.setPosition(menuPtr->menuScreen->getSize().x / 2, menuPtr->menuScreen->getSize().y / 2);
    backgroundSprite.setScale(2,2);

    //Archers
        // Archer player1;
    if (!archer1.archerArmTexture.loadFromFile("images/Archery/PlayerRightArm.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer1.archerTorsoTexture.loadFromFile("images/Archery/PlayerRightTorso.png")) {
        menuPtr->menuScreen->close();
    }

    archer1.archerArmSprite.setTexture(archer1.archerArmTexture);
    archer1.archerTorsoSprite.setTexture(archer1.archerTorsoTexture);
    archer1.archerTorsoSprite.setPosition(-1000, 700);
    archer1.archerArmSprite.setOrigin(archer1.archerArmSprite.getGlobalBounds().width / 2, archer1.archerArmSprite.getGlobalBounds().height / 2);
    archer1.archerArmSprite.setPosition(archer1.archerTorsoSprite.getPosition().x + (archer1.archerTorsoSprite.getGlobalBounds().width / 2), archer1.archerTorsoSprite.getPosition().y + (archer1.archerTorsoSprite.getGlobalBounds().height / 2) - 15);

        // Archer player2;
    player_dist_deviation = (rand() % 200 - 100);

    if (!archer2.archerTorsoTexture.loadFromFile("images/Archery/PlayerLeftTorso.png")) {
        menuPtr->menuScreen->close();
    } else if (!archer2.archerArmTexture.loadFromFile("images/Archery/PlayerLeftArm.png")) {
        menuPtr->menuScreen->close();
    }

    archer2.archerTorsoSprite.setTexture(archer2.archerTorsoTexture);
    archer2.archerTorsoSprite.setPosition(archer1.archerTorsoSprite.getPosition().x + PLAYER_DIST + player_dist_deviation, archer1.archerTorsoSprite.getPosition().y);

    archer2.archerArmSprite.setTexture(archer2.archerArmTexture);
    archer2.archerArmSprite.setOrigin(archer2.archerArmSprite.getGlobalBounds().width / 2, archer2.archerArmSprite.getGlobalBounds().height / 2);
    archer2.archerArmSprite.setPosition(archer2.archerTorsoSprite.getPosition().x + (archer2.archerTorsoSprite.getGlobalBounds().width / 2), archer2.archerTorsoSprite.getPosition().y + (archer2.archerTorsoSprite.getGlobalBounds().height / 2) - 15);

    //Arrows

    if (!arrowTexture.loadFromFile("images/Archery/temp_arrow2.png")) {
        menuPtr->menuScreen->close();
    } else if (!arrowTexture2.loadFromFile("images/Archery/temp_arrow3.png")) {
        menuPtr->menuScreen->close();
    } else if (!arrowTexture3.loadFromFile("images/Archery/temp_arrow.png")) {
        menuPtr->menuScreen->close();
    }

    //Platforms
    if (!platformTexture.loadFromFile("images/Archery/Platform.png")) {
        menuPtr->menuScreen->close();
    }

    platform1.setTexture(platformTexture);
    platform1.setPosition(archer1.archerTorsoSprite.getPosition().x - 40, archer1.archerTorsoSprite.getPosition().y + 0.9 * archer1.archerTorsoSprite.getGlobalBounds().height);

    platform2.setTexture(platformTexture);
    platform2.setPosition(archer2.archerTorsoSprite.getPosition().x, archer2.archerTorsoSprite.getPosition().y + 0.9 * archer2.archerTorsoSprite.getGlobalBounds().height);

    platform3.setTexture(platformTexture);
    platform3.setPosition(archer1.archerTorsoSprite.getPosition().x + PLAYER_DIST / 2, 400);
    platform3.setRotation(-90);
    platform3.setScale(2.5, 1);

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

    //Set initial view to player 1
    gameView->setCenter( archer1.archerTorsoSprite.getPosition() );

}

void ArcheryGameEngine::update(){

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
            collisionType = arrow1->updateMovement(is_arrow_present, menuPtr, drag, g, backgroundSprite, platform1, platform2, platform3, archer1.archerTorsoSprite, archer2.archerTorsoSprite);
        } else {
            collisionType = arrow1->updateMovement(is_arrow_present, menuPtr, drag, g, backgroundSprite, platform1, platform2, platform3, archer2.archerTorsoSprite, archer1.archerTorsoSprite);
        }

        gameView->setCenter( arrow1->arrowSprite.getPosition() );

        if (collisionType == BeamCollisionType::centipede) {
            if (is_player_turn) {
                archer2.arrow_vector.push_back(arrow1);
                arrow1 = nullptr;
            } else {
                archer1.arrow_vector.push_back(arrow1);
                arrow1 = nullptr;
            }
        }

        if (collisionType != BeamCollisionType::nan_) {
            delete arrow1;
            arrow1 = nullptr;
            collisionType = BeamCollisionType::nan_;
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
    } else if (!is_player_turn) {
        arrow1 = new Arrow( arrowTexture2, archer2.archerArmSprite.getPosition().x, archer2.archerArmSprite.getPosition().y, calculateEnemyV());
        arrow1->arrowSprite.setOrigin(arrow1->arrowSprite.getGlobalBounds().width / 2, arrow1->arrowSprite.getGlobalBounds().height / 2);
        arrow1->arrowSprite.setScale(0.07, 0.04);
        archer2.archerArmSprite.setRotation((std::arg(arrow1->arrow_velocity) * 180 / M_PI) - 180);
        is_arrow_present = true;
    }

    while (menuPtr->menuScreen->pollEvent(ev)) {
        is_a_turn = is_arrow_present || is_panning;
        switch (ev.type) {

            case sf::Event::EventType::Closed:
                gameView->setCenter(menuPtr->menuScreen->getSize().x/2, menuPtr->menuScreen->getSize().y/2);
                menuPtr->currentGameType = NULL_GAME;
                break;

            case sf::Event::MouseButtonReleased:
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_mouse_first_pressed && !is_a_turn) {
                    arrow1 = new Arrow(arrowTexture, archer1.archerArmSprite.getPosition().x, archer1.archerArmSprite.getPosition().y, v);
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

    menuPtr->menuScreen->draw(archer1.archerArmSprite);
    menuPtr->menuScreen->draw(archer1.archerTorsoSprite);
    menuPtr->menuScreen->draw(archer2.archerArmSprite);
    menuPtr->menuScreen->draw(archer2.archerTorsoSprite);

    if (is_arrow_present) menuPtr->menuScreen->draw(arrow1->arrowSprite);

    menuPtr->menuScreen->display();
}

std::complex<float> ArcheryGameEngine::calculateEnemyV() {
    const float G = std::imag(drag) + g;
    float init_angle;
    float velocity;
    float sweet_spot_angle = std::atan(G / std::real(drag)) + M_PI;
    // int total_player_dist = archer2.archerTorsoSprite.getPosition().x - archer1.archerTorsoSprite.getPosition().x;
    int total_player_dist = PLAYER_DIST + player_dist_deviation - archer2.archerTorsoSprite.getGlobalBounds().width / 2;
    if (G > 0) {
        if (std::real(drag) > 0) {
            init_angle = (M_PI + sweet_spot_angle) / 2;
        } else {
            init_angle = (M_PI + 3.f * M_PI_2) / 2;
        }
    } else {
        if (std::real(drag) > 0) {
            init_angle = ( sweet_spot_angle + M_PI ) / 2;
        } else {
            init_angle = (M_PI_2 + M_PI) / 2;
        }
    }
    velocity = std::sqrt(( total_player_dist * G * G) / (G * std::sin(2 * init_angle) - 2 * std::real(drag) * std::sin(init_angle) * std::sin(init_angle)) );
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
