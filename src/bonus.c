#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/animation.h"
#include "../include/movement.h"
#include "../include/shooter.h"
#include "../include/missile.h"
#include "../include/game.h"
#include "../include/spaceship.h"
#include "../include/bonus.h"


Bonus *create_bonus(Game *game, char type, int x) {
    Bonus* bonus = malloc(sizeof(Bonus));
    int width, height, speed;
    Animation *animation;
    char *token;
    char key[200];
    char value[200];
    char line[400];
    char current_id = '0';

    FILE *file = fopen(BONUS_DATA_PATH, "r");

    if(file == NULL) {
        printf("Error : Cannot open file %s", BONUS_DATA_PATH);
        return NULL;
    }

    while(fscanf(file, "%s", line) != EOF) {
        if(strchr(line, ':') != NULL) {
            token = strtok(line, ":");
            strcpy(key, token);
            token = strtok(NULL, ":");
            strcpy(value, token);

            if(strcmp(key, "id") == 0) current_id = value[0];

            if(current_id == type) {
                if(     strcmp(key, "width") == 0)         width = atoi(value);
                else if(strcmp(key, "height") == 0)        height = atoi(value);
                else if(strcmp(key, "consumer") == 0)      if(strcmp(value, "true") == 0) bonus->consumer = 1; else bonus->consumer = 0;
                else if(strcmp(key, "animation") == 0) {   animation = init_animation_wrapper(value);
                    break;
                }
            }
        }
    }
    fclose(file);

    if(current_id == '0') {
        printf("Error : Ennemy type not found\n");
        return NULL;
    }
    speed = rand() % 5 + 2;

    bonus->entity = create_entity(x, -height, width, height, speed, movement_forward, animation, EXPLOSION_1, bonus, BONUS);
    bonus->effect = get_bonus_effect_by_id(current_id);
    bonus->type = type;
    insert_entity(game, bonus->entity);
    return bonus;
}

Bonus *create_random_bonus(Game *game, int x) {
    char types[] = RANDOM_BONUSES;
    return create_bonus(game, types[MLV_get_random_integer(0, strlen(types) - 1)], x);
}


int on_collide_bonus(Game *game, Bonus *bonus, Entity *collide, Direction direction) {
    if(collide->type == PLAYER) {
        if(bonus->consumer) {
            bonus->effect(game, (Player*)collide->parent, 0);
            remove_entity(game, bonus->entity, 0);
            return 1;
        }

        if(is_bonus_reachable(game, bonus)) {
            if(have_bonus(collide, bonus->type)) {
                remove_entity(game, bonus->entity, 0);
                return 1;
            }
            add_bonus(game, collide, bonus);
            return 1;
        }
    }
    return 0;
}

int is_bonus_reachable(Game *game, Bonus *bonus) {
    EntityLink *link;
    BonusLink *bonus_link;
    for(link = game->entities; link != NULL; link = link->next) {
        if(link->entity->type == PLAYER) {
            Player *player = (Player*)link->entity->parent;
            for(bonus_link = player->ship->bonus; bonus_link != NULL; bonus_link = bonus_link->next) {
                if(bonus_link->bonus == bonus) return 0;
            }
        }
    }
    return 1;
}

void free_bonus(Bonus *bonus) {
    free(bonus);
}

BONUS_FUNC get_bonus_effect_by_id(char id) {
    switch(id) {
        case SHIELD_EFFECT: return shield_effect; 
        case MAX_LIFE_INCREASE_EFFECT: return max_life_increase_effect;
        case POWER_UP_SHOOT_EFFECT: return power_up_shoot_effect; 
        case LIFE_INCREASE_EFFECT: return life_increase_effect;
        case POWER_UP_SPEED_EFFECT: return power_up_speed_effect;
        case SPAWN_UNIT_EFFECT: return spawn_unit_effect;
        default: return NULL;
    } 
}

void shield_effect(Game *game, Player* eater, int reverse) {
    if(reverse) return;
    else enable_shield(game, eater->entity);
}

void max_life_increase_effect(Game *game, Player* eater, int reverse) {
    Life* life = get_life(eater->entity);
    if(life == NULL) return;
    if(!reverse) {
        life->max_hp++;
        life->hp = life->max_hp;
    } else {
        life->max_hp--;
    }
}

void power_up_speed_effect(Game *game, Player* eater, int reverse) {
    if(!reverse) eater->entity->speed->speed += 3;
    else eater->entity->speed->speed -= 3;
}

void power_up_shoot_effect(Game *game, Player* eater, int reverse) {
    SpaceShip *ship = eater->ship;
    Shooter *shooter = &ship->shooter;
    if(!reverse) shooter->update_shoot = shoot_player_perforing;
    else shooter->update_shoot = shoot_player_basic;
}

void life_increase_effect(Game *game, Player* eater, int reverse) {
    deals_damage(game, eater->entity, -1);
}


void spawn_unit_effect(Game *game, Player* eater, int reverse) {
    if(!reverse) {
        create_missile(game, eater->entity, PROTECTING_MISSILE);
    }
}