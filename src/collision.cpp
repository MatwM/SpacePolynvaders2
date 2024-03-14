#include "collision.h"

bool Collision(Sprite sprite1, Sprite sprite2){
    if(sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()))
        return true;
    else
        return false;
}


bool CollisionPlayerMob(Player player, Mob mob){
    if (Collision(player.getSprite(), mob.getSprite())){
        return true;
    }
    else
        return false;
}

bool CollisionPlayerMobs(Player player, Mobs mobs){
    for (int i = 0; i < mobs.length(); i++) {
        if ((*mobs.getMob(i)).exists() && CollisionPlayerMob(player, *(mobs.getMob(i)))) {
            return true;
        }
    }
    return false;
}

bool CollisionMobMissile(Mob mob, Missile missile){
    if (Collision(missile.getSprite(), mob.getSprite())){
        return true;
    }
    else
        return false;
}

bool CollisionPlayerMissile(Player player, Missile missile){
    if (Collision(missile.getSprite(), player.getSprite())){
        return true;
    }
    else
        return false;
}
