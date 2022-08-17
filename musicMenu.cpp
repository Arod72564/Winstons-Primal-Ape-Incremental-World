#include "MusicMenu.h"

MusicMenu::MusicMenu(MenuScreen* menu){
    initVol = menu->musicVolume;
    menuPtr = menu;
    initMenu();
    

}

MusicMenu::~MusicMenu(){
}

void MusicMenu::initMenu(){


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

    if (!seekButton.loadFromFile("images/MusicMenu/seekForward.png")) {
        menuPtr->menuScreen->close();
    }

    if (!radio.loadFromFile("images/MusicMenu/Radio.png")) {
        menuPtr->menuScreen->close();
    }

    if (!radioScreen.loadFromFile("images/MusicMenu/RadioScreen.png")) {
        menuPtr->menuScreen->close();
    }

    if (!mute.loadFromFile("images/MusicMenu/Mute.png")) {
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

    radioSprite.setTexture(radio);
    radioSprite.setPosition(200, 200);
    radioSprite.setScale(.7,.7);

    seekBackward.setTexture(seekButton);
    seekBackward.setOrigin(seekBackward.getGlobalBounds().width / 2, seekBackward.getGlobalBounds().height / 2);
    seekBackward.setPosition( .15 * radioSprite.getGlobalBounds().width + radioSprite.getPosition().x , radioSprite.getPosition().y + radioSprite.getGlobalBounds().height + 30);
    seekBackward.setScale(.2,.2);
    seekBackward.rotate(180);

    seekForward.setTexture(seekButton);
    seekForward.setOrigin(seekForward.getGlobalBounds().width / 2, seekForward.getGlobalBounds().height / 2);
    seekForward.setPosition(.85 * radioSprite.getGlobalBounds().width + radioSprite.getPosition().x , radioSprite.getPosition().y + radioSprite.getGlobalBounds().height + 30);
    seekForward.setScale(.2,.2);

    muteButtonSprite.setTexture(mute);
    muteButtonSprite.setOrigin(muteButtonSprite.getGlobalBounds().width / 2, muteButtonSprite.getGlobalBounds().height / 2);
    muteButtonSprite.setPosition(.5 * radioSprite.getGlobalBounds().width + radioSprite.getPosition().x , radioSprite.getPosition().y + radioSprite.getGlobalBounds().height + 30);

    radioScreenSprite.setTexture(radioScreen);
    radioScreenSprite.setPosition(200, 200);
    radioScreenSprite.setScale(.7,.7);

    //muteSprite.setTexture(menuPtr->muteButtonTexture);
    //muteSprite.setPosition((6 * menuPtr->menuScreen->getSize().x) / 8, (1 * menuPtr->menuScreen->getSize().y) / 2);

    //Text
    menuPtr->currentMusicName.setFont(menuPtr->menuFont2);
    menuPtr->currentMusicName.setPosition((.1 * radioSprite.getGlobalBounds().width) + radioSprite.getPosition().x, radioSprite.getPosition().y + (radioSprite.getGlobalBounds().height / 2));
    menuPtr->currentMusicName.setScale(.65, .65);
    menuPtr->currentMusicName.setString(menuPtr->musicNameVec[abs(menuPtr->currentMusicIndex % int(menuPtr->musicNameVec.size()))]);

    musicVolText.setFont(menuPtr->menuFont2);
}

void MusicMenu::update(){


    while (menuPtr->menuScreen->pollEvent(ev)) {
        switch ( ev.type) {
            case sf::Event::Closed:
                menuPtr->currentGameType = NULL_GAME;
                break;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (faderSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) { //Click on fader knob
                        is_volume_changing = true;
                    } else if (muteButtonSprite.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) { //Click on pause
                        
                        if(menuPtr->is_MenuMusic_Paused) {
                            menuPtr->menuMusic.play();
                        } else {
                            menuPtr->menuMusic.pause();
                        }
                        menuPtr->is_MenuMusic_Paused = !(menuPtr->is_MenuMusic_Paused);
                    } else if (seekBackward.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) {
                        menuPtr->menuMusic.stop();
                        menuPtr->currentMusicIndex--;

                        menuPtr->menuMusic.openFromFile(menuPtr->musicNameVec[abs(menuPtr->currentMusicIndex % int(menuPtr->musicNameVec.size()))]);
                        menuPtr->currentMusicName.setString(menuPtr->musicNameVec[abs(menuPtr->currentMusicIndex % int(menuPtr->musicNameVec.size()))]);

                        menuPtr->menuMusic.setVolume(menuPtr->musicVolume);
                        menuPtr->menuMusic.play();
                        menuPtr->is_MenuMusic_Paused = false;


                    } else if (seekForward.getGlobalBounds().contains(menuPtr->menuScreen->mapPixelToCoords(sf::Mouse::getPosition(*menuPtr->menuScreen)))) {
                        menuPtr->menuMusic.stop();
                        menuPtr->currentMusicIndex++;

                        
                        menuPtr->menuMusic.openFromFile(menuPtr->musicNameVec[abs(menuPtr->currentMusicIndex % int(menuPtr->musicNameVec.size()))]);
                        menuPtr->currentMusicName.setString(menuPtr->musicNameVec[abs(menuPtr->currentMusicIndex % int(menuPtr->musicNameVec.size()))]);

                        menuPtr->menuMusic.setVolume(menuPtr->musicVolume);
                        menuPtr->menuMusic.play();
                        menuPtr->is_MenuMusic_Paused = false;
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
                    os << std::fixed << std::setprecision(0) << abs(menuPtr->musicVolume);
                    musicVolText.setString(os.str());

                    
                }
                break;

            default:
                break;
        };
    }
    
    if (menuPtr->menuMusic.getStatus() == sf::SoundSource::Stopped) { menuPtr->nextSong(); }
}

void MusicMenu::render(){

    menuPtr->menuScreen->clear(sf::Color::Black);

    menuPtr->menuScreen->draw(bgSprite);
    menuPtr->menuScreen->draw(faderSprite);
    menuPtr->menuScreen->draw(faderKnobSprite);

    menuPtr->menuScreen->draw(radioSprite);
    menuPtr->menuScreen->draw(menuPtr->currentMusicName);
    menuPtr->menuScreen->draw(radioScreenSprite);
    menuPtr->menuScreen->draw(seekForward);
    menuPtr->menuScreen->draw(muteButtonSprite);
    menuPtr->menuScreen->draw(seekBackward);

    if (is_volume_changing) {
        menuPtr->menuScreen->draw(musicVolText);
    }
    

    menuPtr->menuScreen->display();

}