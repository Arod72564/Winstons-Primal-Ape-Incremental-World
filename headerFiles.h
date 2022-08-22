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
enum ArrowCollisionType {archer_head, archer_torso, archer_legs, platform, background, none};
enum GameDifficulty { EASY, NORMAL, HARD, IMPOSSIBLE };
enum GameTypes {NULL_GAME, centipedeGame, dungeonGame, archeryGame, music, games, upgrades};

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
#include <random>

template<typename T> T clamp(T arg1, T arg2, T arg3) {
    if( arg1 < arg2) {
        return arg2;
    } else if (arg1 > arg3) {
        return arg3;
    } else {
        return arg1;
    }
}

sf::Color generateColor() {
    srand (time(NULL));

    return sf::Color(rand() % 255 + 1,rand() % 255 + 1,rand() % 255 + 1,255);
}

template<typename T> class PhysVector2 {
public:
    // std::complex<T> phys_vector;
    T x;
    T y;

    PhysVector2(const T& x_, const T& y_) {
        x = x_;
        y = y_;
    }

    PhysVector2(const PhysVector2<T>& v) {
        x = v.x;
        y = v.y;
    }

    PhysVector2(const std::complex<T>& complex) {
        x = complex.real();
        y = complex.imag();
    }

    PhysVector2(const T& r, const PhysVector2<T>& v) {
        v = v.normalize() * r;
        x = v.x;
        y = v.y;
    }

    static PhysVector2<T> polar(const T& r, const T& theta) {
        std::complex<T> temp = std::polar(r, theta);
        return PhysVector2<T>(temp.real(), temp.imag());
    }

    float mag() { return std::abs(std::complex<T>(x, y)); }
    float dir() { return std::arg(std::complex<T>(x, y)); }

    // Componentwise addition and subtraction
    PhysVector2<T> operator+(const PhysVector2<T>& rhs) { return PhysVector2(x + rhs.x, y + rhs.y); }
    PhysVector2<T> operator-(const PhysVector2<T>& rhs) { return PhysVector2(x - rhs.x, y - rhs.y); }
    PhysVector2<T>& operator+=(const PhysVector2<T>& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    PhysVector2<T>& operator-=(const PhysVector2<T>& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    // The dot product
    float operator*(const PhysVector2<T> &rhs) { return x * rhs.x + y * rhs.y; }

    // Scalar multiplication
    PhysVector2<T> operator*(const T &scalar) { return PhysVector2(x * scalar, y * scalar); }
    PhysVector2<T>& operator*=(const T &scalar) {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }
    // Scalar division
    PhysVector2<T> operator/(const T& scalar) { return this * (1 / scalar); }

    // Normalize a vector
    PhysVector2<T> normalize() { return this / mag(); }
};

#endif
