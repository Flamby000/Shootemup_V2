#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/missile.h"
#include "../include/spaceship.h"
#include "../include/bonus.h"
#include "../include/entity.h"
#include "../include/player.h"
#include "../include/shooter.h"
#include "../include/movement.h"
#include "../include/ennemy.h"

Ennemy* create_ennemy(Game *game, char type, int x) {
    Ennemy* ennemy = malloc(sizeof(Ennemy));
    int width, height, speed, cooldown, life, score, invincibility;
    SPEED_FUNC movement;
    SHOOT_FUNC shoot;
    Animation *animation;
    int is_boss = 0;
    char* token;
    char key[200];
    char value[200];
    char line[400];
    char current_id = 'X';

    FILE *file = fopen(ENNEMY_DATA_PATH, "r");

    if(file == NULL) {
        printf("Error : Cannot open file %s", ENNEMY_DATA_PATH);
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
                else if(strcmp(key, "animation") == 0)     animation = init_animation_wrapper(value);
                else if(strcmp(key, "speed") == 0)         speed = atoi(value);
                else if(strcmp(key, "movement") == 0)      movement = get_movement_function(atoi(value));
                else if(strcmp(key, "life") == 0)          life = atoi(value);
                else if(strcmp(key, "cooldown") == 0)      cooldown = atoi(value);
                else if(strcmp(key, "is_boss") == 0) {     if(strcmp(value, "true") == 0) is_boss = 1; }
                else if(strcmp(key, "score") == 0)         score = atoi(value);
                else if(strcmp(key, "invincibility") == 0) invincibility = atoi(value);
                else if(strcmp(key, "shoot") == 0) {       shoot = get_shoot_function(atoi(value));
                    break;
                }
            }
        }
    }
    fclose(file);

    if(current_id == 'X') {
        printf("Error : Ennemy type not found\n");
        return NULL;
    }

    ennemy->entity = create_entity(x, -height, width, height, speed, movement, animation, EXPLOSION_1, ennemy, ENNEMY);
    ennemy->ship = create_spaceship(life, cooldown, invincibility, shoot, shoot_none);
    ennemy->score = score;
    ennemy->is_boss = is_boss;
    
    insert_entity(game, ennemy->entity);
    return ennemy;
}


void create_shoot_line(Game* game, Entity *entity, char* shootline) {
    int i;
    int line_size = strlen(shootline);

    for(i = 0; i < line_size; i++) {
        if(shootline[i] == 'X') continue;
        create_missile(game,
            entity, 
            shootline[i] - '0', 
            entity->x + (entity->width / line_size) * i + (entity->width / line_size) / 2
            );
    }
}

void free_ennemy(Game* game, Ennemy *ennemy) {
    free_spaceship(game, ennemy->ship);
    free(ennemy);
}

int on_collide_ennemy(Game *game, Ennemy *ennemy, Entity *collide, Direction direction) {
    int ennemy_score = ennemy->score;
    int ennemy_is_boss = ennemy->is_boss;
    int player_die = 0;
    if(collide->type == PLAYER) {
            
        player_die = deals_damage(game, collide, 1);
        if(deals_damage(game, ennemy->entity, 1)){
            if(!player_die) {
                ((Player*)collide->parent)->score += ennemy_score;
                ((Player*)collide->parent)->boss_kill_count +=ennemy_is_boss;
            }
        }
        return 1;
    }

    if(collide->type == BONUS  && is_bonus_reachable(game, (Bonus*)collide->parent)) {
        remove_entity(game, collide, 1);
        return 1;
    }
    return 0;
}
