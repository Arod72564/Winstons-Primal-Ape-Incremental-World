#include "MusicMenu.h"

MusicMenu::MusicMenu(MenuScreen* menu){
    initVol = menu->musicVolume;
    initMenu();
    menuPtr = menu;

}

MusicMenu::~MusicMenu(){
}

void MusicMenu::initMenu(){
    //Text
    if (!font.loadFromFile("fonts/ARLRDBD.TTF")) {
        menuPtr->menuScreen->close();
    }

    currentMusicName.setFont(font);
    musicVolText.setFont(font);

    //Textures
    if (!bg1.loadFromFile("images/MusicMenu/bg1.png")) {
        menuPtr->menuScreen->close();
    }

    if (!bg2.loadFromFile("images/MusicMenu/bg2.png")) {
        menuPtr->menuScreen->close();
    }

    if (!bg3.loadFromFile("images/MusicMenu/bg3.png")) {
        menuPtr->menuScreen->close();
    }

    if (!fader.loadFromFile("images/MusicMenu/faderTrack.png")) {
        menuPtr->menuScreen->close();
    }

    if (!faderKnob.loadFromFile("images/MusicMenu/faderKnob.png")) {
        menuPtr->menuScreen->close();
    }

    //Sprites

    bgSprite.setTexture(bg1);
    bgSprite.setPosition(0,0);

    faderSprite.setTexture(fader);
    faderSprite.setPosition(100, 200);

    faderKnobSprite.setTexture(faderKnob);
    faderKnobSprite.setOrigin(faderKnobSprite.getGlobalBounds().width / 2, faderKnobSprite.getGlobalBounds().height / 2);
    faderKnobSprite.setPosition(faderSprite.getPosition().x + faderSprite.getGlobalBounds().width / 2,  (-3.0f * initVol) + 500.0f);


    //muteSprite.setTexture(menuPtr->muteButtonTexture);
    //muteSprite.setPosition((6 * menuPtr->menuScreen->getSize().x) / 8, (1 * menuPtr->menuScreen->getSize().y) / 2);

}

void MusicMenu::update(){


    while (menuPtr->menuScreen->pollEvent(ev)) {
        switch ( ev.type) {
            case sf::Event::Closed:
                menuPtr->currentGameType = NULL_GAME;
                break;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && faderSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) {
                    is_volume_changing = true;
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && muteSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) {
                    menuPtr->is_MenuMusic_Paused = !(menuPtr->is_MenuMusic_Paused);
                    if(menuPtr->is_MenuMusic_Paused) {
                        menuPtr->menuMusic.play();
                    } else {
                        menuPtr->menuMusic.pause();
                    }
                    
                }
                break;

            case sf::Event::MouseButtonReleased:
                is_volume_changing = false;
                break;

            case sf::Event::MouseMoved:
                if (is_volume_changing) { 
                    float y_pos = clamp(float(ev.mouseMove.y), faderSprite.getPosition().y, faderSprite.getPosition().y + faderSprite.getGlobalBounds().height);
                    faderKnobSprite.setPosition(faderKnobSprite.getPosition().x, y_pos);

                    menuPtr->musicVolume = (((y_pos - 500) / 3) * -1); //we want out of 100 for volume, and divide by 3 as fader track is 300 pixels 
                    menuPtr->menuMusic.setVolume(menuPtr->musicVolume);

                    musicVolText.setPosition(faderKnobSprite.getPosition().x, faderKnobSprite.getPosition().y - 20);

                    std::stringstream os;
                    os << std::fixed << std::setprecision(0) << menuPtr->musicVolume;
                    musicVolText.setString(os.str());

                    
                }
                break;

            default:
                break;
        };
    }
    
    //std::cout << faderKnobSprite.getPosition().x << ", " << faderKnobSprite.getPosition().y << std::endl;
}

void MusicMenu::render(){

    menuPtr->menuScreen->clear(sf::Color::Black);

    menuPtr->menuScreen->draw(bgSprite);
    menuPtr->menuScreen->draw(faderSprite);
    menuPtr->menuScreen->draw(faderKnobSprite);
    //menuPtr->menuScreen->draw(muteSprite);

    if (is_volume_changing) {
        menuPtr->menuScreen->draw(musicVolText);
    }
    

    menuPtr->menuScreen->display();

}