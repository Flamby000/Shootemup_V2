#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/missile.h"
#include "../include/player.h"
#include "../include/ennemy.h"
#include "../include/entity.h"



Entity* create_entity(int x, int y, int width, int height, 
                      int speed, void (*update_speed)(struct _Game*, struct _Entity*),
                      Animation* animation,
                      void* parent, EntityType type
                      ) {

    Entity* entity = malloc(sizeof(Entity));
    entity->x = x;
    entity->y = y;
    entity->width = width;
    entity->height = height;
    entity->rotation = 0;
    entity->sprite = animation;

    entity->speed = malloc(sizeof(Speed));
    entity->speed->speed_x = 0;
    entity->speed->speed_y = 0;
    entity->speed->speed = speed;  
    entity->speed->update_speed = update_speed;  

    entity->parent = parent;
    entity->type = type;
    
    return entity;
}    

void avoid_collide_border(Entity *entity) {
    if(entity->x <= 0) {
        entity->x = 0;
    } else if(entity->x + entity->width >= settings->win_width) {
        entity->x = settings->win_width - entity->width;
    }

    if(entity->y <= 0) {
        entity->y = 0;
    } else if(entity->y + entity->height >= settings->win_height) {
        entity->y = settings->win_height - entity->height;
    }      
}

void update_entity(Game* game, Entity *entity) {
    entity->speed->update_speed(game, entity);
    
    entity->x += entity->speed->speed_x;
    entity->y += entity->speed->speed_y;


    free_out_of_screen(game, entity);

}

void free_out_of_screen(Game *game, Entity *entity) {

    /* Free ennemy when reach bottom border*/
    if(entity->type == ENNEMY && entity->y > settings->win_height) {
            remove_entity(game, entity);
    }

    /*Free missiles when out of screen*/
    if(entity->type == MISSILE && (
        entity->y  > settings->win_height || 
        entity->y + entity->height < 0 ||
        entity->x > settings->win_width ||
        entity->x + entity->width < 0)
    ) {
        remove_entity(game, entity);
    }
}

void free_entity(Entity *entity) {

    if(entity->type == MISSILE) free_missile((Missile*)entity->parent);
    if(entity->type == ENNEMY) free_ennemy((Ennemy*)entity->parent);
    if(entity->type == PLAYER) free_player((Player*)entity->parent);
    
    free_animation(entity->sprite);
    free(entity->speed);
    free(entity);
}

Direction get_direction(Entity *entity) {
    if(entity->speed->speed_x > 0) return RIGHT;
    else if(entity->speed->speed_x < 0) return LEFT;
    else if(entity->speed->speed_y > 0) return BACKWARD;
    else return FORWARD;
}