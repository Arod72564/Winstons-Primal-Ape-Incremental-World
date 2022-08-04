//g++ -c main.cpp -I"C:/SFML-2.5.1/include"
//g++ main.o -o main -L"C:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include "CentipedeGameEngine.cpp"
#include "Centipede.cpp"
#include "Mushroom.cpp"
#include "Player.cpp"
#include "Beam.cpp"
#include "MenuScreen.cpp"
#include "DungeonGameEngine.cpp"

int main() {
    sf::VideoMode videoMode;
    videoMode.height = 800;
    videoMode.width = 800;
    sf::RenderWindow* mainWindow = new sf::RenderWindow(videoMode, "Winstons Primal Ape Incremental World", sf::Style::Titlebar | sf::Style::Close);

    // Initialize Menu screen
    MenuScreen* menu = new MenuScreen(mainWindow);

    while(menu->menuScreen->isOpen()) {
        
        if (menu->currentGameType == NULL_GAME) { //MAIN MENU
            menu->update();
            menu->render();

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

        }
    }

    delete menu;
    delete mainWindow;

    std::cout << "Game quits.\n";
    return 0;
}