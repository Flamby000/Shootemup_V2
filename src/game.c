#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/player.h"
#include "../include/background.h"


Game* init_game() {
    Game *game = malloc(sizeof(Game));
    game->entities = NULL;
    init_background(game);

    game->player = create_player(game);
    
    return game;
}

void update_game(Game *game) {
    EntityLink* current = game->entities;
    while(current != NULL) {
        update_entity(current->entity);
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
    return 0;
}

void print_entities(Game *game) {
}

void remove_entity(Game* game, Entity* entity) {
}