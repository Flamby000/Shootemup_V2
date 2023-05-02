#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/player.h"
#include "../include/spaceship.h"
#include "../include/bonus.h"
#include "../include/level.h"
#include "../include/animation.h"
#include "../include/ennemy.h"
#include "../include/missile.h"
#include "../include/background.h"



Game* init_game() {
    Game *game = malloc(sizeof(Game));
    game->level = create_level("data/level/level-1.lvl");
    game->entities = NULL;

    init_background(game);
    game->player = create_player(game);
    game->is_match_on = 1;
    return game;
}

void update_game(Game *game) {
    EntityLink* current;
    Entity* entity;

    for(current = game->entities; current != NULL; current = current->next) {
        entity = current->entity;
        /* Update movement entity*/
        if(update_entity(game, entity)) return;
        
        /* Update shoot of players/ennemies*/
        if(entity->type == PLAYER || entity->type == ENNEMY) {
            update_spaceship(game, entity);
        }
    }

    /* Update the level */
    update_level(game, game->level, 1);
}

void free_game(Game* game) {
    EntityLink* current = game->entities;
    while(current != NULL) {
        EntityLink* next = current->next;
        remove_entity(game, current->entity, 0);
        current = next;
    }
    free(game);
}

void end_match(Game* game) {
    game->is_match_on = 0;
    printf("Game Over\n");
}

void insert_entity(Game* game, Entity* entity) {
    EntityLink* new_entity = malloc(sizeof(EntityLink));
    new_entity->entity = entity;
    new_entity->next = NULL;

    if(game->entities == NULL) {
        game->entities = new_entity;
    } else {
        EntityLink* current;
        for(current = game->entities; current != NULL; current = current->next) {
            if(current->next == NULL) {
                current->next = new_entity;
                update_entity(game, entity);
                return;
            }
        }
    }
}

int get_entity_id(Game* game, Entity* entity) {
    int id = 0;
    EntityLink* current;
    for(current = game->entities; current != NULL; current = current->next) {
        if(current->entity == entity) {
            return id;
        }
        id++;
    }
    return -1;
}


int is_boss_alive(Game* game) {
    EntityLink* current;
    for(current = game->entities; current != NULL; current = current->next) {
        if(current->entity->type == ENNEMY) {
            Ennemy* ennemy = (Ennemy*) current->entity->parent;
            if(ennemy->is_boss) return 1;
        }
    }
    return 0;
}

int entity_count(Game *game) {
    int count = 0;
    EntityLink* current;
    for(current = game->entities; current != NULL; current = current->next) {
        count++;
    }
    return count;
}

void remove_entity(Game* game, Entity* entity, int explose) {
    EntityLink* current;
    int boss_alive = is_boss_alive(game);
    if(explose) create_one_shot_animation(game, entity->destruction_img_path, entity);

    for(current = game->entities; current != NULL; current = current->next) {

        if(current->entity == entity) {
            /* if entity is the first element of the list */
            if(current == game->entities) {
                game->entities = current->next;

            } else {
                EntityLink* previous = game->entities;
                while(previous->next != current) {
                    previous = previous->next;
                }
                previous->next = current->next;
            }
            free_entity(game, current->entity);
            free(current);
            current = NULL;
            if(!is_boss_alive(game) && boss_alive) end_match(game);
            return;
        }
    }

    printf("Error : Entity not found\n");
}