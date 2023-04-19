#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/spaceship.h"

SpaceShip* create_spaceship(int life, int shoot_cooldown, void (*update_shoot)(struct _Game*, struct _Entity*)) {
    SpaceShip* ship = malloc(sizeof(SpaceShip));
    (&ship->life)->hp = life;
    (&ship->life)->max_hp = life; 
    (&ship->life)->shield = 0; 

    (&ship->shooter)->last_shoot_time = MLV_get_time();
    (&ship->shooter)->update_shoot = update_shoot;
    (&ship->shooter)->cooldown = shoot_cooldown;
    
    return ship;
}

void update_spaceship(Game *game, Entity* entity) {

    if(entity->type == PLAYER) {
        Player *player = (Player*)entity->parent;
        /*printf("TEST %d\n", player->ship->life.hp);*/
        Shooter *shooter = &player->ship->shooter;
        
        if(MLV_get_time() - shooter->last_shoot_time > shooter->cooldown) {
            printf("SHOOT\n");
            shooter->update_shoot(game, entity);
            shooter->last_shoot_time = MLV_get_time();
        }

    }
}

void free_spaceship(SpaceShip* spaceship) {
    free(spaceship);
}