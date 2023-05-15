#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/interface/animation.h"
#include "../../include/logic/game.h"
#include "../../include/logic/missile.h"
#include "../../include/interface/menu.h"
#include "../../include/logic/player.h"
#include "../../include/logic/bonus.h"
#include "../../include/logic/ennemy.h"
#include "../../include/logic/entity.h"

Entity* create_entity(int x, int y, int width, int height, 
                      int speed, SPEED_FUNC update_speed,
                      Animation* animation, 
                      char* destruction_img_path,
                      void* parent, EntityType type
                      ) {

    Entity* entity = malloc(sizeof(Entity));
    entity->x = x;
    entity->y = y;
    entity->width = width;
    entity->height = height;
    entity->rotation = 0;
    entity->sprite = animation;
    if(destruction_img_path != NULL) {
        entity->destruction_img_path = malloc(sizeof(char) * strlen(destruction_img_path) + 1);
        strcpy(entity->destruction_img_path, destruction_img_path);
    } else {
        entity->destruction_img_path = NULL;
    }


    entity->speed = malloc(sizeof(Speed));
    entity->speed->speed_x = 0;
    entity->speed->speed_y = 0;
    entity->speed->speed = speed;  
    entity->speed->default_speed = speed;
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
    if(entity->type == MISSILE) if(update_missile(game, (Missile*)entity->parent)) return 1;


    /* Libération de la mémoire lorsque l'entity quitte l'écran*/
    if(free_out_of_screen(game, entity)) return 1;

    /* Détection des collisions*/
    for(current = game->entities; current != NULL; current = current->next) {
        if(entity != NULL && current->entity != NULL && entity != current->entity) {
            if(on_entity_collide(game, entity, current->entity, get_entity_collide(entity, current->entity))) return 1;
        }
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
    else if(entity->type == MISSILE) return on_collide_missile(game,(Missile*)entity->parent, other, direction);
    else if(entity->type == BONUS)   return on_collide_bonus(game,  (Bonus*)entity->parent, other, direction);

    return 0;
}

int free_out_of_screen(Game *game, Entity *entity) {

    /* Libération des ennemies lorsqu'ils dépassent le bas de l'écran*/
    if(entity->type == ENNEMY && entity->y > settings->win_height) {
        remove_entity(game, entity, 0);
        return 1;
    }

    /* Libération des missiles/bonus quand ils quittent l'écran*/
    if((entity->type == MISSILE || entity->type == BONUS) && (
        entity->y  > settings->win_height || 
        entity->y + entity->height < 0 ||
        entity->x > settings->win_width ||
        entity->x + entity->width < 0)
    ) {
        remove_entity(game, entity, 0);

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



void free_entity(Game* game, Entity *entity) {
    EntityLink* current;
    EntityLink* next = NULL;
    if(entity->type == MISSILE) free_missile((Missile*)entity->parent);
    if(entity->type == ENNEMY) free_ennemy(game, (Ennemy*)entity->parent);
    if(entity->type == BUTTON) free_button((Button*)entity->parent);
    if(entity->type == PLAYER) free_player(game, (Player*)entity->parent);
    if(entity->type == BONUS) free_bonus((Bonus*)entity->parent);
    free(entity->destruction_img_path);

    /* Free children */
    current = entity->children;
    while(current != NULL) {
        next = current->next;
        free_entity(game, current->entity);
        free(current);
        current = next;
    }

    free_animation(entity->sprite);
    free(entity->speed);
    
    free(entity);
    entity = NULL;
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