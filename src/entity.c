#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/missile.h"
#include "../include/player.h"
#include "../include/bonus.h"
#include "../include/ennemy.h"
#include "../include/entity.h"
/*

typedef struct _Game {
    struct _EntityLink* entities;
    struct _Player *player;
    struct _Level *level;
} Game;

typedef struct _EntityLink {
    struct _Entity* entity;
    struct _EntityLink* next;
    struct _EntityLink* children;
} EntityLink;

typedef enum _EntityType {
    ENNEMY,
    PLAYER,
    MISSILE,
    LABEL,
    BONUS
    
} EntityType;
 
typedef struct _Entity{
    struct _Animation* sprite;
    int x;
    int y;
    int width;
    int height;
    int rotation;
    struct _Speed* speed;

    EntityLink *children;
    void* parent;
    EntityType type;
} Entity;
*/

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
    entity->children = NULL;
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

int update_entity(Game* game, Entity *entity) {
    EntityLink* current;

    /* Mis à jour de la vitesse */
    entity->speed->update_speed(game, entity);

    /* Mise à jour de la position à partir de la vitesse*/
    entity->x += entity->speed->speed_x;
    entity->y += entity->speed->speed_y;

    /* Manage missile update (for fuel)*/
    if(entity->type == MISSILE) 
        if(update_missile(game, (Missile*)entity->parent)) return 1;


    /* Libération de la mémoire lorsque l'entity quitte l'écran*/
    if(free_out_of_screen(game, entity)) return 1;

    /* Détection des collisions*/
    for(current = game->entities; current != NULL; current = current->next) {
        if(entity != NULL && current->entity != NULL && entity != current->entity) {
            if(on_entity_collide(game, entity, current->entity, get_entity_collide(entity, current->entity))) return 1;
        }
    }
    
    /* Mise à jour des enfants */
    if(entity->children == NULL) return 0;
    for(current = entity->children; current != NULL; current = current->next) {
        /*if(update_entity(game, current->entity)) return 1;*/
    }

    return 0;
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
    else if(entity->type == PLAYER)  return on_collide_player(game, (Player*)entity->parent, other, direction);
    else if(entity->type == ENNEMY)  return on_collide_ennemy(game, (Ennemy*)entity->parent, other, direction);
    else if(entity->type == MISSILE) return on_collide_missile(game, (Missile*)entity->parent, other, direction);
    else if(entity->type == BONUS)   return on_collide_bonus(game, (Bonus*)entity->parent, other, direction);

    return 0;
}

int free_out_of_screen(Game *game, Entity *entity) {

    /* Libération des ennemies lorsqu'ils dépassent le bas de l'écran*/
    if(entity->type == ENNEMY && entity->y > settings->win_height) {
        remove_entity(game, entity);
        return 1;
    }

    /* Libération des missiles/bonus quand ils quittent l'écran*/
    if((entity->type == MISSILE || entity->type == BONUS) && (
        entity->y  > settings->win_height || 
        entity->y + entity->height < 0 ||
        entity->x > settings->win_width ||
        entity->x + entity->width < 0)
    ) {
        remove_entity(game, entity);

        return 1;
    }

    return 0;
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
    return closest_entity(game, game->player->entity, ENNEMY);
}

void free_entity(Game* game, Entity *entity) {
    if(entity->type == MISSILE) free_missile((Missile*)entity->parent);
    if(entity->type == ENNEMY) free_ennemy(game, (Ennemy*)entity->parent);
    if(entity->type == PLAYER) free_player(game, (Player*)entity->parent);
    if(entity->type == BONUS) free_bonus((Bonus*)entity->parent);
    free_animation(entity->sprite);
    free(entity->speed);
    
    free(entity);
}

void add_child(Entity* parent, Entity* child) {
    EntityLink* link = malloc(sizeof(EntityLink));
    link->entity = child;
    link->next = NULL;
    if(parent->children == NULL) {
        parent->children = link;
    } else {
        link->next = parent->children;
        parent->children = link;
    }
}

void remove_child(Game* game, Entity* parent, Entity* child) {
    EntityLink* current = parent->children;
    EntityLink* previous = NULL;
    while(current != NULL) {
        if(current->entity == child) {
            if(previous == NULL) {
                parent->children = current->next;
            } else {
                previous->next = current->next;
            }
            free_entity(game, current->entity);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}