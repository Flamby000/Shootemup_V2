#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/logic/entity.h"
#include "../../include/logic/game.h"
#include "../../include/logic/player.h"
#include "../../include/logic/spaceship.h"
#include "../../include/logic/bonus.h"
#include "../../include/logic/level.h"
#include "../../include/interface/menu.h"
#include "../../include/interface/animation.h"
#include "../../include/logic/ennemy.h"
#include "../../include/utils/movement.h"
#include "../../include/interface/menu.h"
#include "../../include/settings.h"
#include "../../include/logic/missile.h"
#include "../../include/utils/background.h"

Game* init_game() {
    Menu main_menu;
    Game *game = malloc(sizeof(Game));
    set_level(game, NULL);
    game->entities = NULL;

    init_background(game);
    set_background_speed(game, 0.5);

    main_menu = create_main_menu(game, MAIN_MENU);
    set_menu(game, &main_menu);

    game->match_status = NOT_STARTED;
    game->last_click_action_time = 0;

    MLV_play_music(settings->music, settings->volume, -1);    

    return game;
}

int is_match_entity(Entity *entity) {
    if(entity->type == PLAYER 
    || entity->type == ENNEMY 
    || entity->type == MISSILE 
    || entity->type == BONUS) return 1;
    return 0;
}

void update_game(Game *game) {
    EntityLink* current, *next;
    Entity* entity;

    /* Update entities */
    for(current = game->entities; current != NULL; current = next) {
        next = current->next;
        entity = current->entity;

        if(!(is_match_entity(entity) && game->match_status != PROCESS)) {
            if(update_entity(game, entity)) return;
        
            /* Update shoot of players/ennemies */
            if(entity->type == PLAYER || entity->type == ENNEMY) {
                update_spaceship(game, entity);
            }
        }        
    }

    /* Update the level */
    if(game->match_status == PROCESS) {
        if(game->level != NULL) {
            if(remaining_players(game) == 0) end_match(game, MATCH_LOOSE);
            if(boss_kill_count(game)) end_match(game, MATCH_WIN);
            if(update_level(game, game->level, settings->infinite_mode) && remaining_ennemies(game) == 0) {
                end_match(game, MATCH_WIN);
            }
        }
    }

    /* Update buttons */
    for(current = game->entities; current != NULL; current = next) {
        next = current->next;
        entity = current->entity;
        if(entity->type == BUTTON) {
            if(update_button(game, (Button*)entity->parent)) return;
        }
    }

    if(game->match_status == PROCESS && MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED) {
        pause_match(game);
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

int get_score(Game* game) {
    EntityLink* current;
    Player* player;
    int score = 0;
    for(current = game->entities; current != NULL; current = current->next) {
        if(current->entity->type == PLAYER) {
            player = (Player*) current->entity->parent;
            score += player->score;
        }
    }
    return score;
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

void start_match(Game* game, char* level_file) {
    EntityLink* current;
    EntityLink* next;

    for(current = game->entities; current != NULL; current = next) {
        next = current->next;
        if(is_match_entity(current->entity)) {
            remove_entity(game, current->entity, 0);
        }
    }

    set_background_speed(game, 1);
    set_level(game, level_file);
    create_player(game, 1);


    if(settings->coop_mode) create_player(game, 2);

    set_menu(game, NULL);
    game->match_status = PROCESS;
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

void remove_entities_by_type(Game* game, EntityType type) {
    EntityLink* current;
    EntityLink* next;
    for(current = game->entities; current != NULL; current = next) {
        next = current->next;
        if(current->entity->type == type) {
            remove_entity(game, current->entity, 0);
        }
    }
}

void end_match(Game* game, MatchStatus status) {
    Menu match_end_menu = create_game_over_menu(game, status);

    set_background_speed(game, 0);
    remove_entities_by_type(game, MISSILE);

    game->match_status = status;
    set_menu(game, &match_end_menu);
}

void pause_match(Game* game) {
    if(game->match_status == PROCESS) {
        Menu pause_menu = create_game_over_menu(game, PAUSE);
        set_background_speed(game, 0);
        set_menu(game, &pause_menu);
        game->match_status = PAUSE;
    } else {

        set_background_speed(game, 1);
        set_menu(game, NULL);
        game->match_status = PROCESS;
    }
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
    EntityLink* current, *next;
    if(explose) {
        create_one_shot_animation(game, entity->destruction_img_path, entity);
        MLV_play_sound(settings->explosion_sound, settings->volume*0.005);
    }
    
    for(current = game->entities; current != NULL; current = next) {
        next = current->next;
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