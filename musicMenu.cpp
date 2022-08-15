#include "MusicMenu.h"

MusicMenu::MusicMenu(MenuScreen menu){
    menuPtr = menu;

}

MusicMenu::~MusicMenu(){
    menuPtr->currentGameType = NULL_GAME;
}

void MusicMenu::initMenu(){
    //Text
    if (!font.loadFromFile("fonts/ARLRDBD.TTF")) {
        menuPtr->menuScreen->close();
    }

    currentMusicName.setFont(font);

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
    faderSprite.setPosition(100, 500);

    faderKnobSprite.setTexture(faderKnob);
    faderKnobSprite.setOrigin(faderKnobSprite.getGlobalBounds().width / 2, faderKnobSprite.getGlobalBounds().height / 2);
    faderKnobSprite.setPosition(faderSprite.getPosition().x + faderSprite.getGlobalBounds().width / 2, faderSprite.getPosition().y + faderSprite.getGlobalBounds().height + (menuPtr->musicVolume * 3));

}

void MusicMenu::update(){

}

void MusicMenu::render(){

    menuPtr->menuScreen->clear(sf::Color::Transparent);

    menuPtr->menuScreen->draw(bgSprite);
    menuPtr->menuScreen->draw(faderSprite);
    menuPtr->menuScreen->draw(faderKnobSprite);

    menuPtr->menuScreen->display();

}