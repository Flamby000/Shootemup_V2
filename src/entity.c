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
                      int speed, SPEED_FUNC update_speed,
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

    /* Libération de la mémoire lorsque l'entity quitte l'écran*/
    free_out_of_screen(game, entity);

    /* Détection des collisions*/
    for(current = game->entities; current != NULL; current = current->next) {
        if(entity != NULL && current->entity != NULL && entity != current->entity) {
            if(on_entity_collide(game, entity, current->entity, get_entity_collide(entity, current->entity))) return;
        }
    }
}

Direction get_entity_collide(Entity* entity, Entity* other) {
    int entity_right = entity->x + entity->width;
    int entity_bottom = entity->y + entity->height;
    int other_right = other->x + other->width;
    int other_bottom = other->y + other->height;
    if(entity->type == LABEL) return NONE;

    if(entity->x < other_right && entity_right > other->x && 
    entity->y < other_bottom && entity_bottom > other->y) {
        int horiz_dist = (entity->x + entity->width/2) - (other->x + other->width/2);
        int vert_dist = (entity->y + entity->height/2) - (other->y + other->height/2);
        if(abs(horiz_dist) > abs(vert_dist)) {
            if(horiz_dist < 0) {
                return RIGHT;
            } else {
                return LEFT;
            }
        } else {
            if(vert_dist < 0) {
                return TOP;
            } else {
                return BOTTOM;
            }
        }
    }
    return NONE;
}

int on_entity_collide(Game* game, Entity* entity, Entity* other, Direction direction) {
    if(direction == NONE) return 0;   
    else if(entity->type == PLAYER) return on_collide_player(game, (Player*)entity->parent, other, direction);
    else if(entity->type == ENNEMY) return on_collide_ennemy(game, (Ennemy*)entity->parent, other, direction);
    else if(entity->type == MISSILE) return on_collide_missile(game, (Missile*)entity->parent, other, direction);

    return 0;
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
    else if(entity->speed->speed_y > 0) return BOTTOM;
    else return TOP;
}

Entity* closest_entity(Game *game, Entity *entity, EntityType filter) {
    EntityLink *closest = NULL;
    EntityLink *current = NULL;
    for(current=game->entities; current!=NULL; current=current->next) {
        if(current->entity->type == filter) {
            if(closest == NULL) {
                closest = current;
            } else {
                if(abs(current->entity->x - entity->x) < abs(closest->entity->x - entity->x)) {
                    closest = current;
                }
            }
        } 
    }
    if(closest == NULL) return NULL;
    return closest->entity;
}

Entity* closest_ennemy(Game *game) {
    return closest_entity(game, game->player, ENNEMY);
}