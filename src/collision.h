#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <SFML/Graphics.hpp>
#include <stdbool.h>

#include "config.h"
#include "player.h"
#include "mobs.h"
#include "missile.h"

using namespace sf;

bool Collision(Sprite sprite1,Sprite sprite2);
bool CollisionPlayerMob(Player player, Mob mob);
bool CollisionPlayerMobs(Player player, Mobs mobs);
bool CollisionMobMissile(Mob mob, Missile missile);
bool CollisionPlayerMissile(Player player, Missile missile);

#endif