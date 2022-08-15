#ifndef HEADERFILES_H
#define HEADERFILES_H

#define WINDOW_WIDTH        800
#define WINDOW_HEIGHT       1000

#define TILE_WIDTH_PIXELS   (WINDOW_WIDTH / 50)
#define TILE_LENGTH_PIXELS  (WINDOW_HEIGHT / 50)

#define HORIZONTAL_TILES    (WINDOW_WIDTH/50)
#define VERTICAL_TILES      (WINDOW_HEIGHT/50)

#define CENTIPEDE_SPEED 2
#define BEAM_SPEED 12

#define _USE_MATH_DEFINES

enum BeamCollisionType {centipede, mushroom, boundary, nan_};
enum GameTypes {NULL_GAME, centipedeGame, dungeonGame, archeryGame, musicMenu};

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits.h>
#include <iomanip>
#include <list>
#include <cmath>
#include <complex>

template<typename T> T clamp(T arg1, T arg2, T arg3) {
    if( arg1 < arg2) {
        return arg2;
    } else if (arg1 > arg3) {
        return arg3;
    } else {
        return arg1;
    }
}

#endif
