#ifndef __MOBS_H__
#define __MOBS_H__

#include <SFML/Graphics.hpp>
#include <stdbool.h>
#include <iostream>
#include "config.h"

using namespace sf;

class Mob{
    public:
        Mob(float x = 0, float y = 0, int PV = 1);
        ~Mob(){};
        void serpantin1(int Ymult, float Xmult);
        void setSprite(Sprite spriteMob);
        Sprite getSprite();
        int getX();
        int getY();
        void reset(float x, float y, int PV);
        int getPV(){return _PV;}
        void hit(int damage);
        bool exists();
        bool outscreen(){return _outscreen;};
        void killed();
        void revive();
    private:
        float _x;
        float _y;
        int _PV;
        Sprite _spriteMob;
        bool _outscreen;
        int _sens;
        int _Ycount;
        bool _estinit;
        int _espacementInitial;
};

class Mobs{
    public:
        Mobs(int n = 0);
        ~Mobs();
        void serpantinAll();
        void setSprites(Sprite spriteMobs);
        int length(){return _n;};
        void dead();
        Sprite getSprites(int n);
        int getNbRows(){return _nbRows;};
        Mob* getMob(int i){return &_mobs[i];};
        void reset();
    private:
        int _n;
        Mob* _mobs;
        int _nbRows;
};

inline void Mob::setSprite(Sprite spriteMob){
    _spriteMob = spriteMob;
}

inline Sprite Mob::getSprite(){
    return _spriteMob;
}

inline int Mob::getX(){
    return _x;
}

inline int Mob::getY(){
    return _y;
}

inline void Mob::hit(int damage) {
    _PV -= damage;
}

inline Mobs::~Mobs(){
    delete[] _mobs;
}

inline void Mobs::setSprites(Sprite spriteMobs){
    for (int i = 0; i < _n; i++){
        _mobs[i].setSprite(spriteMobs);
    }
}

inline Sprite Mobs::getSprites(int n){
    return _mobs[n].getSprite();
}

inline bool Mob::exists(){
    bool exists = (_PV > 0 && not(_outscreen));
    return exists;
}

inline void Mob::killed(){
    _outscreen = true;
}

inline void Mob::revive(){
    _outscreen = false;
}
inline void Mobs::dead(){
    _n --;
}

#endif