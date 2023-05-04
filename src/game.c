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
#include "../include/interface/menu.h"
#include "../include/animation.h"
#include "../include/ennemy.h"
#include "../include/interface/menu.h"
#include "../include/settings.h"
#include "../include/missile.h"
#include "../include/background.h"


Game* init_game() {
    Game *game = malloc(sizeof(Game));
    /*Menu main_menu;*/
    game->level = NULL;
    game->level = create_level("data/level/test.lvl");

    game->entities = NULL;

    init_background(game);
    set_background_speed(game, 1);
    settings->game_phase = MAIN_MENU_PHASE;


    create_player(game);
    /*main_menu = create_game_over_menu(game);*/
    /*remove_menu(game, &main_menu);*/

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

        if(entity->type == BUTTON) {
            update_button(game, (Button*)entity->parent);
        }
    }

    /* Update the level */
    if(game->level != NULL) {
        if(remaining_players(game) == 0) end_match(game, 0);
        if(boss_kill_count(game)) end_match(game, 1);
        if(update_level(game, game->level, settings->infinite_mode) && remaining_ennemies(game) == 0) {
            end_match(game, 1);
        }
    }
}

int boss_kill_count(Game* game) {
    EntityLink* current;
    Player* player;
    int count = 0;
    for(current = game->entities; current != NULL; current = current->next) {
        if(current->entity->type == PLAYER) {
            player = (Player*) current->entity->parent;
            count += player->boss_kill_count;
        }
    }
    return count;
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

void free_game(Game* game) {
    EntityLink* current = game->entities;
    while(current != NULL) {
        EntityLink* next = current->next;
        remove_entity(game, current->entity, 0);
        current = next;
    }
    free(game);
}

int remaining_ennemies(Game* game) {
    EntityLink* current;
    int count = 0;
    for(current = game->entities; current != NULL; current = current->next) {
        if(current->entity->type == ENNEMY) {
            count++;
        }
    }
    return count;
}

int remaining_players(Game* game) {
    EntityLink* current;
    int count = 0;
    for(current = game->entities; current != NULL; current = current->next) {
        if(current->entity->type == PLAYER) {
            count++;
        }
    }
    return count;
}

void end_match(Game* game, int win) {
    free_level(game->level);
    game->level = NULL;
    printf("Game Over %d\n", win);
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
            return;
        }
    }

    printf("Error : Entity not found\n");
}