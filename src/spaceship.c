#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/game.h"
#include "../include/movement.h"
#include "../include/spaceship.h"

SpaceShip* create_spaceship(int life, int shoot_cooldown, int invincibility_duration,  SHOOT_FUNC update_shoot) {
    SpaceShip* ship = malloc(sizeof(SpaceShip));
    (&ship->life)->hp = life;
    (&ship->life)->max_hp = life; 
    (&ship->life)->shield = 0; 
    (&ship->life)->last_damage_time = 0; 
    (&ship->life)->invincibility_duration = invincibility_duration; 

    (&ship->shooter)->last_shoot_time = 0;
    (&ship->shooter)->update_shoot = update_shoot;
    (&ship->shooter)->cooldown = shoot_cooldown;

    return ship;
}

void update_spaceship(Game *game, Entity* entity) {
    Shooter *shooter;
    if(entity->type == PLAYER)      shooter = &((Player*)entity->parent)->ship->shooter; 
    else if(entity->type == ENNEMY) shooter = &((Ennemy*)entity->parent)->ship->shooter;
    else return;

    if(MLV_get_time() - shooter->last_shoot_time > shooter->cooldown) {
        if(shooter->update_shoot(game, entity)) {
            shooter->last_shoot_time = MLV_get_time();
        }
    }    
}

void free_spaceship(SpaceShip* spaceship) {
    free(spaceship);
}

int deals_damage(Game *game, Entity *entity, int damage) {
    Life *life;
    if(entity->type == ENNEMY)      life = &((Ennemy*)entity->parent)->ship->life;
    else if(entity->type == PLAYER) life = &((Player*)entity->parent)->ship->life;
    else return 0;

    if(MLV_get_time() - life->last_damage_time < life->invincibility_duration) return 0;
    
    life->last_damage_time = MLV_get_time();
    life->hp -= damage;
    push_entity(game, entity);

    if(life->hp <= 0) {
        life->hp = 0;
        remove_entity(game, entity);
        return 1;
    } 

    return 0;
}