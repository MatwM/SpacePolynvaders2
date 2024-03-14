#include "player.h"

void Player::MoveX(int dx){
    if (_x+dx*SPEED_PLAYER > 0 && _x+dx*SPEED_PLAYER < GameConfig::windowSize.x -_width*ZOOM_PLAYER){
        _x += dx*SPEED_PLAYER;
        _spritePlayer.move(dx*SPEED_PLAYER, 0);
    }
}

void Player::MoveY(int dy){
    if (_y+dy*SPEED_PLAYER/2.5 > 0 && _y+dy*SPEED_PLAYER/2.5 < GameConfig::windowSize.y -_height*ZOOM_PLAYER){
        _y += dy*SPEED_PLAYER/2.5;
        _spritePlayer.move(0, dy*SPEED_PLAYER/2.5);
    }
}
void Player::reset() {
    // Réinitialiser les PV du joueur
    _PV = PLAYER_PV;

    // Réinitialiser la position du joueur
    _x = GameConfig::windowSize.x / 2 - 128/2;
    _y = GameConfig::windowSize.y - 128*2;

    // Réinitialiser la position du sprite du joueur
    _spritePlayer.setPosition(_x, _y);
}

void player_move(Player *player){
    float dx = 0, dy = 0;
    if (Keyboard::isKeyPressed(Keyboard::Up)) dy=-1;
    else if (Keyboard::isKeyPressed(Keyboard::Down)) dy=1;
    if (Keyboard::isKeyPressed(Keyboard::Left)) dx=-1;
    else if (Keyboard::isKeyPressed(Keyboard::Right)) dx=1;
    if (dx != 0) {
        (*player).MoveX(dx);
    }
    if (dy != 0) {
        (*player).MoveY(dy);
    }
}
