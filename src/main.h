#ifndef __MAIN_H__
#define __MAIN_H__

// Les librairies importées
#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>


using namespace sf;

// Mes files créés
#include "config.h"
#include "mobs.h"
#include "missile.h"
#include "player.h"
#include "collision.h"
#include "screen.h"

bool GameOver = false;

void processEvents(RenderWindow& window, bool& isMenuOpen);













#endif 