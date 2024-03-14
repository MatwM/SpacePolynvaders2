#include "mobs.h"
#include <iostream>

Mob::Mob(float x, float y, int PV) {
    _x = x;
    _y = y; 
    _PV = PV; 
    _outscreen = false; 
    _estinit = false; 
    _sens = 0; 
    _Ycount = 0; 
    _spriteMob.setPosition(x,y);
}

void Mob::serpantin1(int Ymult, float Xmult) {
    if (!_estinit){ // Initialisation des variables
        _spriteMob.setPosition(_x, _y);
        _espacementInitial = ESPACE_COLONE; // Conserve l'espacement initial entre les colonnes
        _estinit = true;
    }
    if (!_outscreen){
        if (_sens == 0) {
            if (_x + _spriteMob.getLocalBounds().width < GameConfig::windowSize.x) {
                _x += SPEED_MOB*Xmult;
                _spriteMob.move(SPEED_MOB*Xmult, 0);
            } 
            else if (_y + _spriteMob.getLocalBounds().height < GameConfig::windowSize.y){
                _x = GameConfig::windowSize.x - _spriteMob.getLocalBounds().width;
                _spriteMob.setPosition(_x, _y);
                _y += ESPACE_LIGNE * Ymult;
                _spriteMob.move(0, ESPACE_LIGNE * Ymult);
                _sens = 1;
            }
            else _outscreen = true;
        } else {
            if (_x > 0) {
                _x -= SPEED_MOB*Xmult;
                _spriteMob.move(-SPEED_MOB*Xmult, 0);
            } 
            else if (_y + _spriteMob.getLocalBounds().height < GameConfig::windowSize.y){
                _x = 0;
                _spriteMob.setPosition(_x, _y);
                _y += ESPACE_LIGNE * Ymult;
                _spriteMob.move(0, ESPACE_LIGNE * Ymult);
                _sens = 0;
            }
            else _outscreen = true;
        }
    }
}


Mobs::Mobs(int n) {
    _n = n;
    _mobs = new Mob[n + 1];
    int rows = n / NOMBRE_COLONE; // Calcul du nombre de lignes nécessaires
    _nbRows = rows;
    int index = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < NOMBRE_COLONE; col++) {
            float x = (ESPACE_COLONE) * col;
            float y = (ESPACE_LIGNE) * row;
            _mobs[index] = Mob(x, y, 1);
            index++;
        }
    }
    // Pour le reste des mobs qui pourraient ne pas former une ligne complète
    for (int col = 0; col < n % NOMBRE_COLONE; col++) {
        float x = (ESPACE_COLONE) * col;
        float y = (ESPACE_LIGNE) * rows;
        _mobs[index] = Mob(x, y, 1);
        index++;
    }
}

void Mobs::serpantinAll(){
    for (int i = 0; i < _n; i++) {
        _mobs[i].serpantin1(_nbRows,1);
    }
}

void Mobs::reset() {
    // Réinitialiser le nombre de mobs
    _n = NOMBRE_MECHANT;

    // Réinitialiser chaque mob individuellement
    int rows = _n / NOMBRE_COLONE; // Calcul du nombre de lignes nécessaires
    _nbRows = rows+1;
    int index = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < NOMBRE_COLONE; col++) {
            float x = (ESPACE_COLONE) * col;
            float y = (ESPACE_LIGNE) * row;
            _mobs[index] = Mob(x, y, 1);
            index++;
            _mobs[index].revive();
        }
    }
    // Pour le reste des mobs qui pourraient ne pas former une ligne complète
    for (int col = 0; col < _n % NOMBRE_COLONE; col++) {
        float x = (ESPACE_COLONE) * col;
        float y = (ESPACE_LIGNE) * rows;
        _mobs[index] = Mob(x, y, 1);
        index++;
        _mobs[index].revive();
    }
}

void Mob::reset(float x,float y,int PV){
    _x = x;
    _y = y;
    _PV = PV;
    _outscreen = false; 
    _estinit = false; 
    _sens = 0; 
    _Ycount = 0; 
    _spriteMob.setPosition(x,y);
}