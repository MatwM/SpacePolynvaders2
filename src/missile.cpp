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
