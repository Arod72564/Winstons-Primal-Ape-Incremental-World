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

#define DELTA_T             0.075
#define GRAV                25

#define _USE_MATH_DEFINES

enum BeamCollisionType {centipede, mushroom, boundary, nan_};
enum ArrowCollisionType {archer_head, archer_torso, archer_legs, platform, background, none};
enum GameDifficulty { EASY, NORMAL, HARD, IMPOSSIBLE };
enum GameTypes {NULL_GAME, centipedeGame, dungeonGame, archeryGame, ragdollGame, music, games, upgrades};

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

    PhysVector2() {
        x = 0;
        y = 0;
    }

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

    // Builds a PhysVector2 with magnitude r that points in the direction of v
    PhysVector2(const T& r, PhysVector2<T> v) {
        v = v.normalize() * r;
        x = v.x;
        y = v.y;
    }

    PhysVector2(sf::Vector2f v) {
        x = v.x;
        y = v.y;
    }

    static PhysVector2<T> polar(const T& r, const T& theta) {
        std::complex<T> temp = std::polar(r, theta);
        return PhysVector2<T>(temp.real(), temp.imag());
    }

    float mag() { return std::abs(std::complex<T>(x, y)); }
    float dir() { return std::arg(std::complex<T>(x, y)); }

    // Overloading ()
    PhysVector2<T>& operator()(const T& x_, const T& y_) {
        this->x = x_;
        this->y = y_;
        return *this;
    }

    void operator()(sf::Vector2f v) {
        x =  v.x;
        y = v.y;
        //return *this;
    }
    
 
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
    PhysVector2<T> operator/(const T& scalar) { return *this * (1 / scalar); }
    PhysVector2<T>& operator/=(const T &scalar) {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }

    // Normalize a vector
    PhysVector2<T> normalize() {
        if (mag() == 0.f) {
            return *this;
        } else {
            return *this / mag();
        }
        // return *this / mag();
    }

    sf::Vector2<T> toSF() { return sf::Vector2<T>(x, y); }

    T dist(PhysVector2<T>& v) {
        return (*this - v).mag();
    }

    friend std::ostream& operator<<(std::ostream& os, const PhysVector2<T>& v) {
        os << v.x << ", " << v.y;
        return os;
    }
};

#endif
