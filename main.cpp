//g++ -c main.cpp -I"C:/SFML-2.5.1/include"
//g++ main.o -o main -L"C:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include "GameEngine.cpp"
#include "Centipede.cpp"
#include "Mushroom.cpp"
#include "Player.cpp"
#include "Beam.cpp"
#include "MenuScreen.cpp"
#include "Dungeon.cpp"

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

            if (menu->currentGameType == centipedeGame) { //CEMTIPEDE GAME
                //Initialize centipede game driver class
                GameEngine* gameEngine = new GameEngine(menu);

                //Main game loop
                while(menu->currentGameType == centipedeGame) {

                    //Update game data
                    gameEngine->update();

                    //Render game graphics
                    gameEngine->render();
                }

                delete gameEngine;
            }

            if (menu->currentGameType == dungeonGame) { //Dungeon
                //Initialize Dungeon game driver class
                Dungeon* dungeon = new Dungeon(menu);

                //Main game loop
                while(menu->currentGameType == dungeonGame) {

                    //Update game data
                    dungeon->update();

                    //Render game graphics
                    dungeon->render();
                }

                delete dungeon;
            }

        }
    }

    delete menu;
    delete mainWindow;

    std::cout << "Game quits.\n";
    return 0;
}