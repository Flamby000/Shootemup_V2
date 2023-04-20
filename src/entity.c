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
    EntityLink* current;

    /* Mis à jour de la vitesse */
    entity->speed->update_speed(game, entity);
    
    /* Mise à jour de la position à partir de la vitesse*/
    entity->x += entity->speed->speed_x;
    entity->y += entity->speed->speed_y;

    /* Détection des collisions*/
    for(current = game->entities; current != NULL; current = current->next) 
        if(entity != current->entity) on_entity_collide(game, entity, current->entity, get_entity_collide(entity, current->entity));  

    /* Libération de la mémoire lorsque l'entity quitte l'écran*/
    free_out_of_screen(game, entity);
}

Direction get_entity_collide(Entity* entity, Entity* other) {
  /* The 0, 0 start from top left window corner
    *  The window height is settings->win_height and the width is settings->win_width
    *  In an entity, we have a field x and y which are the top left corner of the entity and a field width and height
    */
    /* Detect the collision between entity and return the DIRECTION of the "entity" element of the collide*/
    if(entity->x + entity->width > other->x && entity->x < other->x + other->width) {
        if(entity->y + entity->height > other->y && entity->y < other->y + other->height) {
            if(entity->y + entity->height - other->y < other->y + other->height - entity->y) {
                if(entity->x + entity->width - other->x < other->x + other->width - entity->x) {
                    if(entity->y + entity->height - other->y < entity->x + entity->width - other->x) {
                        return FORWARD;
                    } else {
                        return LEFT;
                    }
                } else {
                    if(entity->y + entity->height - other->y < other->x + other->width - entity->x) {
                        return FORWARD;
                    } else {
                        return RIGHT;
                    }
                }
            } else {
                if(entity->x + entity->width - other->x < other->x + other->width - entity->x) {
                    if(entity->y + entity->height - other->y < entity->x + entity->width - other->x) {
                        return BACKWARD;
                    } else {
                        return LEFT;
                    }
                } else {
                    if(entity->y + entity->height - other->y < other->x + other->width - entity->x) {
                        return BACKWARD;
                    } else {
                        return RIGHT;
                    }
                }
            }
        }
    }
    
    return NONE;    
}

void on_entity_collide(Game* game, Entity* entity, Entity* other, Direction direction) {
    if(direction == NONE) return;   

    if(entity->type == PLAYER) on_collide_player(game, (Player*)entity->parent, other);
    if(entity->type == ENNEMY) on_collide_ennemy(game, (Ennemy*)entity->parent, other);
    if(entity->type == MISSILE) on_collide_missile(game, (Missile*)entity->parent, other);
}

void free_out_of_screen(Game *game, Entity *entity) {

    /* Libération des ennemies lorsqu'ils dépassent le bas de l'écran*/
    if(entity->type == ENNEMY && entity->y > settings->win_height) {
        remove_entity(game, entity);
    }

    /* Libération des missiles quand ils quittent l'écran*/
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