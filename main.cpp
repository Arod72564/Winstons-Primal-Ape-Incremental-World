//g++ -c main.cpp -I"C:/SFML-2.5.1/include"
//g++ main.o -o main -L"C:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include "CentipedeGameEngine.cpp"
#include "Centipede.cpp"
#include "Mushroom.cpp"
#include "Player.cpp"
#include "Beam.cpp"
#include "MenuScreen.cpp"
#include "DungeonGameEngine.cpp"
#include "ArcheryGameEngine.cpp"
#include "RagdollGameEngine.cpp"
#include "SoftBody.cpp"
#include "SplashScreen.cpp"
#include "MusicMenu.cpp"
#include "GameMenu.cpp"
#include "UpgradeMenu.cpp"

int main() {
    sf::VideoMode videoMode;
    videoMode.height = 800;
    videoMode.width = 800;
    sf::RenderWindow* mainWindow = new sf::RenderWindow(videoMode, "Winstons Primal Ape Incremental World", sf::Style::Titlebar | sf::Style::Close);
    mainWindow->setFramerateLimit(120);

    //Initialize spalsh screen
    SplashScreen* splashScreen = new SplashScreen(mainWindow);
    while (splashScreen->is_splash_displayed) {
        splashScreen->update();
        splashScreen->render();

        if (!mainWindow->isOpen()) {
            delete splashScreen;
            delete mainWindow;
            return 0;
        }
    }
    delete splashScreen;


    // Initialize Menu screen
    MenuScreen* menu = new MenuScreen(mainWindow);

    while(menu->menuScreen->isOpen()) {

        if (menu->currentGameType == NULL_GAME) { //MAIN MENU
            menu->update();
            menu->render();


            if (menu->currentGameType == upgrades) { //UPGRADE MENU
                UpgradeMenu* upgradeMenu = new UpgradeMenu(menu);

                while (menu->currentGameType == upgrades) {

                    upgradeMenu->update();

                    upgradeMenu->render();
                }

                delete upgradeMenu;
            }

            if (menu->currentGameType == games) { //GAME SELECTION
                GameMenu* gameMenu = new GameMenu(menu);

                while (menu->currentGameType == games) {

                    gameMenu->update();

                    gameMenu->render();
                }

                delete gameMenu;
            }

            if (menu->currentGameType == centipedeGame) { //CENTIPEDE GAME
                //Initialize centipede game driver class
                CentipedeGameEngine* centipedeGameEngine = new CentipedeGameEngine(menu);

                //Main game loop
                while(menu->currentGameType == centipedeGame) {

                    //Update game data
                    centipedeGameEngine->update();

                    //Render game graphics
                    centipedeGameEngine->render();
                }

                delete centipedeGameEngine;
            }

            if (menu->currentGameType == dungeonGame) { //DUNGEON PUZZLE GAME
                //Initialize DungeonGameEngine game driver class
                DungeonGameEngine* dungeonGameEngine = new DungeonGameEngine(menu);

                //Main game loop
                while(menu->currentGameType == dungeonGame) {

                    //Update game data
                    dungeonGameEngine->update();

                    //Render game graphics
                    dungeonGameEngine->render();
                }

                delete dungeonGameEngine;
            }

            if (menu->currentGameType == archeryGame) { //ARCHERY GAME
                //Initialize ArcheryGameEngine game driver class
                ArcheryGameEngine* archeryGameEngine = new ArcheryGameEngine(menu);

                //Main game loop
                while(menu->currentGameType == archeryGame) {

                    //Update game data
                    archeryGameEngine->update();

                    //Render game graphics
                    archeryGameEngine->render();
                }

                delete archeryGameEngine;
            }

            if (menu->currentGameType == ragdollGame) { //RAGDOLL GAME
                //Initialize RagdollGameEngine game driver class
                RagdollGameEngine* ragdollGameEngine = new RagdollGameEngine(menu);

                //Main game loop
                while(menu->currentGameType == ragdollGame) {

                    //Update game data
                    ragdollGameEngine->update();

                    //Render game graphics
                    ragdollGameEngine->render();
                }

                delete ragdollGameEngine;
            }

            if (menu->currentGameType == music) { // MUSIC MENU
                MusicMenu* musicMenu = new MusicMenu(menu);

                while (menu->currentGameType == music) {

                    musicMenu->update();

                    musicMenu->render();
                }

                delete musicMenu;
            }

            if (menu->menuMusic.getStatus() == sf::SoundSource::Stopped) { menu->nextSong(); }
        }
    }

    delete menu;
    delete mainWindow;

    std::cout << "Game quits.\n";
    return 0;
}
