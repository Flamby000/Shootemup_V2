#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/game.h"
#include "../include/movement.h"
#include "../include/animation.h"
#include "../include/entity.h"
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

void free_spaceship(Game* game, SpaceShip* spaceship) {
    if((&spaceship->life)->shield) remove_entity(game, (&spaceship->life)->shield_entity);
    free(spaceship);
}

int enable_shield(Game *game, Entity *entity) {
    Life *life;
    if(     entity->type == PLAYER) life = &((Player*)entity->parent)->ship->life;
    else if(entity->type == ENNEMY) life = &((Ennemy*)entity->parent)->ship->life;
    else return 0;

    insert_entity(game, 
        life->shield_entity = create_entity(
            entity->x - entity->width * 0.1, entity->y - entity->height * 0.1,
            entity->width * 1.2, entity->height * 1.2,
            entity->speed->speed, entity->speed->update_speed,  
            init_animation_wrapper("resources/utils/shield-%d.png"),
            NULL, LABEL
        )
    );

    life->shield = 1;
    return 1;
}



int deals_damage(Game *game, Entity *entity, int damage) {
    Life *life;
    
    if(entity->type == ENNEMY)      life = &((Ennemy*)entity->parent)->ship->life;
    else if(entity->type == PLAYER) life = &((Player*)entity->parent)->ship->life;
    else return 0;

    if(MLV_get_time() - life->last_damage_time < life->invincibility_duration) return 0;

    if(life->shield) {
        life->shield = 0;
        remove_entity(game, life->shield_entity);
        return 1;
    }

    life->last_damage_time = MLV_get_time();
    life->hp -= damage;
    if(entity->type == PLAYER) push_entity(game, entity);

    if(life->hp <= 0) {
        life->hp = 0;
        remove_entity(game, entity);
        return 1;
    } 

    return 0;
}