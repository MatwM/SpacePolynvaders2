#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Graphics.hpp>
#include <stdbool.h>
#include "config.h"

using namespace sf;

class Player{
    public:
        Player(float x = 0, float y = 0, int PV = 1);
        ~Player(){};
        void setSprite(Sprite spritePlayer);
        void MoveX(int dx);
        void MoveY(int dy);
        Sprite getSprite();
        float getX();
        float getY();
        void setPV(int PV){_PV = PV;};
        int getPV(){return _PV;}
        float getWidth(){return _width;};
        float getHeight(){return _height;};
        void setSpritePos(float x, float y);
        void hit(int damage);
        void reset();
    private:
        float _x;
        float _y;
        float _width;
        float _height;
        int _PV;
        Sprite _spritePlayer;
};

void player_move(Player *player);

inline Player::Player(float x, float y, int PV) {
    _x = x;
    _y = y;
    _PV = PV;
}

inline void Player::setSprite(Sprite spritePlayer) {
    _spritePlayer = spritePlayer;
    _width = _spritePlayer.getLocalBounds().width;
    _height = _spritePlayer.getLocalBounds().height;
}

inline Sprite Player::getSprite() {
    return _spritePlayer;
}

inline float Player::getX() {
    return _x;
}

inline float Player::getY() {
    return _y;
}

inline void Player::setSpritePos(float x, float y){
    _spritePlayer.setPosition(x, y);
}

inline void Player::hit(int damage){
    _PV -= damage;
}

#endif