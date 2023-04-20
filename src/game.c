#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/player.h"
#include "../include/spaceship.h"
#include "../include/animation.h"
#include "../include/ennemy.h"
#include "../include/background.h"



Game* init_game() {
    Game *game = malloc(sizeof(Game));
    game->entities = NULL;

    init_background(game);
    game->player = create_player(game);

    create_ennemy(game, BASIC_ENNEMY, settings->win_width/2);


    return game;
}

void update_game(Game *game) {

    
    EntityLink* current = game->entities;
    Entity* entity;
    while(current != NULL) {
        entity = current->entity;
        /* Update movement entity*/
        update_entity(game, entity);

        /* Update shoot of players/ennemies*/
        if(entity->type == PLAYER || entity->type == ENNEMY) {
            update_spaceship(game, entity);
        }
    
        current = current->next;
    }


}

void free_game(Game* game) {
    EntityLink* current = game->entities;
    while(current != NULL) {
        EntityLink* next = current->next;
        free_entity(current->entity);
        free(current);
        current = next;
    }

    free_player(game->player);
    free(game);
}


void insert_entity(Game* game, Entity* entity) {

    EntityLink* new_entity = malloc(sizeof(EntityLink));
    new_entity->entity = entity;
    new_entity->next = NULL;

    if(game->entities == NULL) {
        game->entities = new_entity;
    } else {
        EntityLink* current = game->entities;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = new_entity;
    }
    
}

int entity_count(Game *game) {
    int count = 0;
    EntityLink* current = game->entities;
    while(current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void print_entities(Game *game) {
}

void remove_entity(Game* game, Entity* entity) {
    EntityLink* current = game->entities;
    EntityLink* previous = NULL;
    while(current != NULL) {
        if(current->entity == entity) {
            if(previous == NULL) {
                game->entities = current->next;
            } else {
                previous->next = current->next;
            }
            free_entity(current->entity);
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
}