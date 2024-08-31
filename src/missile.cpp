#include "missile.h"

void Missiles::NewMissile(Sprite spriteMissile){
    int index = 0;
    while (index < _nmax && _missiles[index].getInmap()){
        index++;
    }
    if (index < _nmax){
        if (!_mode){
        Player localPlayer = *_player;
        _missiles[index].setX(localPlayer.getX() + localPlayer.getWidth() / 2 * ZOOM_PLAYER);
        _missiles[index].setY(localPlayer.getY());
        _missiles[index].InitSprite(spriteMissile);
        _missiles[index].ActivMissile();
        }
        else {
        Mob localMob = *_mob;
        _missiles[index].setX(localMob.getX() + localMob.getSprite().getGlobalBounds().width / 2);
        _missiles[index].setY(localMob.getY() + 150);
        _missiles[index].InitSprite(spriteMissile);
        _missiles[index].ActivMissile();
        }
    }
    else {
        //std::cerr << "Cannot add more missiles, maximum capacity reached!" << std::endl;
    }
}

void Missiles::ForwardAll(){
    for (int i = 0; i < _nmax; i++) {
        if (_missiles[i].getInmap() == true){
            _missiles[i].Forward1();
            if (_missiles[i].getInmap() == false){
                _n --;
            }
        }
    }
}

void Missiles::BackwardAll(float mult){
    for (int i = 0; i < _nmax; i++) {
        if (_missiles[i].getInmap() == true){
            _missiles[i].Backward1(mult);
            if (_missiles[i].getInmap() == false){
                _n --;
            }
        }
    }
}

void Missile::Deviation1(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-4*SPEED_MISSILE, 4*SPEED_MISSILE);
    int randomNumber = dis(gen);
        _x = randomNumber;
        _spriteMissile.move(randomNumber,0);
}

void Missiles::DeviationAll(){
    for (int i = 0; i < _nmax; i++) {
        if (_missiles[i].getInmap() == true){
            _missiles[i].Deviation1();
            if (_missiles[i].getInmap() == false){
                _n --;
            }
        }
    }
}

void Missiles::reset(int mode) {
    // Réinitialiser le nombre de missiles
    _n = 0;
    _mode = mode;
    // Réinitialiser l'état de tous les missiles
    for (int i = 0; i < _nmax; i++) {
        _missiles[i].DesactivMissile();
    }
}