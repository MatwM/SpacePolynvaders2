#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdbool.h>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1980 * 7 / 8 // Division jusqu'à 2 sinon erreur d'arrondi: taille 0 --> Pas d'affichage
#define WINDOW_HEIGHT 1240 * 7 / 8
#define ESPACE_LIGNE 64
#define ESPACE_COLONE 64
#define LARGEUR_MOB 64
#define HAUTEUR_MOB 64
#define ZOOM_PLAYER 1.5
#define NOMBRE_MECHANT 60
#define SPEED_MOB 2
#define SPEED_PLAYER 3.5
#define SPEED_MISSILE 6
#define NOMBRE_COLONE 20
#define FRAME_RATE 244 // FPS
#define PLAYER_PV 3
#define BOSS_PV 80
#define NOMBRE_MISSILES 15
#define NOMBRE_MISSILES_BOSS 10
#define RELOAD_TIME 0.22
#define RELOAD_TIME_BOSS 2.1
#define LEVEL_MAX 2

extern bool GameOver;

class GameConfig {
public:
    static sf::Vector2u windowSize;
};

#endif