#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/background.h"

typedef struct _Game {
    struct _EntityLink* entities;
} Game;

typedef struct _EntityLink {
    struct _Entity* entity;
    struct _EntityLink* next;
} EntityLink;

Game init_game() {
    Game game;

    init_background(&game);
    return game;
}

void update_game() {
    
}

void free_game(Game* game) {
    EntityLink* current = game->entities;
    EntityLink* next = NULL;
    while (current != NULL) {
        next = current->next;
        free_entity(current->entity);
        free(current);
        current = next;
    }
}



void insert_entity(Game* game, Entity* entity) {
    EntityLink* link = malloc(sizeof(EntityLink));
    link->entity = entity;
    link->next = NULL;
    if (game->entities == NULL) {
        game->entities = link;
    } else {
        EntityLink* current = game->entities;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = link;
    }
}

int entity_count(Game *game) {

}



void print_entities(Game *game) {
    

}

void remove_entity(Game* game, Entity* entity) {
    EntityLink* current = game->entities;
    EntityLink* previous = NULL;
    while (current != NULL) {
        if (current->entity == entity) {
            if (previous == NULL) {
                game->entities = current->next;
            } else {
                previous->next = current->next;
            }
            free_entity(current->entity);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}