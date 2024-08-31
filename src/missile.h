#ifndef __MISSILE_H__
#define __MISSILE_H__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <random>

#include "player.h"
#include "stdbool.h"
#include "config.h"
#include "mobs.h"


using namespace sf;

class Missile{
    public:
        Missile(float x = 0, float y = 0);
        ~Missile(){};
        void ActivMissile();
        void DesactivMissile();
        void Forward1();
        void Backward1(float mult);
        void Deviation1();
        Sprite getSprite();
        void setSprite(Sprite spriteMissile);
        void InitSprite(Sprite spriteMissile);
        float getY(){return _y;};
        float getX(){return _x;};
        void setX(float x){_x = x;}
        void setY(float y){_y = y;}
        bool getInmap(){return _inmap;};
    private:
        float _x;
        float _y;
        Sprite _spriteMissile;
        bool _inmap;
};

class Missiles{
    public:
        Missiles(int nmax = 1, int _mode = 0);
        ~Missiles();
        void ForwardAll();
        void BackwardAll(float mult);
        void DeviationAll();
        Sprite getSprite(int n);
        Missile* getMissile(int n);
        void setPlayer(Player* player);
        void setMob(Mob* Mob);
        void NewMissile(Sprite spriteMissile);
        int lenght(){return _n;};
        void reset(int mode = 0);
    private:
        int _nmax;
        int _n;
        int _mode;
        Missile* _missiles;
        Player* _player;
        Mob* _mob;
};

inline Missile::Missile(float x, float y){
    _x = x;
    _y = y;
    _inmap = false;
}

inline Sprite Missile::getSprite(){
    return _spriteMissile;
}

inline void Missile::setSprite(Sprite spriteMissile){
    _spriteMissile = spriteMissile;
}

inline void Missile::InitSprite(Sprite spriteMissile){
    _spriteMissile = spriteMissile;
    _spriteMissile.setPosition(_x, _y);
}

inline void Missile::Forward1(){
    _y -= SPEED_MISSILE;
    _spriteMissile.move(0, -SPEED_MISSILE);
    if (_y < 0) _inmap = false;
}

inline void Missile::Backward1(float mult){
    _y += SPEED_MISSILE*mult;
    _spriteMissile.move(0, +SPEED_MISSILE*mult);
    if (_y > GameConfig::windowSize.y) _inmap = false;    
}

inline Missiles::Missiles(int nmax, int mode){
    _nmax = nmax;
    _n = 0;
    _mode = mode;
    _missiles = new Missile[nmax];
}

inline Missiles::~Missiles(){
    delete[] _missiles;
}

inline void Missiles::setPlayer(Player *player){
    _player = player;
}

inline void Missiles::setMob(Mob *mob){
    _mob = mob;
}

inline Sprite Missiles::getSprite(int n){
    return _missiles[n].getSprite();
}

inline void Missile::ActivMissile(){
    _inmap = true;
}

inline void Missile::DesactivMissile(){
    _inmap = false;
}

inline Missile* Missiles::getMissile(int n){
    return &_missiles[n];
}

#endif