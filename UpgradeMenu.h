#ifndef UPGRADE_MENU_H
#define UPGRADE_MENU_H

#include "headerFiles.h"
#include "MenuScreen.h"

class UpgradeMenu {
    public:
        MenuScreen* menuPtr;
        std::stringstream os;

        sf::View* gameView;
        sf::Event ev;

        sf::Text centipedeMultiplierText;
        sf::Text centipedeMultiplierCostText;

        UpgradeMenu(MenuScreen* menu);
        virtual ~UpgradeMenu();
        void initMenu();
        void render();
        void update();
};

#endif