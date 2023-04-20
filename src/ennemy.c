#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/spaceship.h"

#include "../include/entity.h"
#include "../include/player.h"
#include "../include/shooter.h"
#include "../include/movement.h"
#include "../include/ennemy.h"

Ennemy* create_ennemy(Game *game, char type, int x) {
    Ennemy* ennemy = malloc(sizeof(Ennemy));
    int width, height, speed, cooldown, life, score, invincibility;
    void (*movement)(struct _Game*, struct _Entity*);
    int (*shoot)(struct _Game*, struct _Entity*);
    Animation *animation;
    char key[200];
    char value[200];
    char line[400];
    char current_id = '0';
    FILE *file = fopen(ENNEMY_DATA_PATH, "r");

    if(file == NULL) {
        printf("Error : Cannot open file %s", ENNEMY_DATA_PATH);
        return NULL;
    }

    while(fscanf(file, "%s", line) != EOF) {
        if(strchr(line, ':') != NULL) {
            char *token = strtok(line, ":");
            strcpy(key, token);
            token = strtok(NULL, ":");
            strcpy(value, token);

            if(strcmp(key, "id") == 0) current_id = value[0];

            if(current_id == type) {
                if(     strcmp(key, "width") == 0)        width = atoi(value);
                else if(strcmp(key, "height") == 0)        height = atoi(value);
                else if(strcmp(key, "animation") == 0)     animation = init_animation_wrapper(value);
                else if(strcmp(key, "speed") == 0)         speed = atoi(value);
                else if(strcmp(key, "movement") == 0)      movement = get_movement_function(atoi(value));
                else if(strcmp(key, "life") == 0)          life = atoi(value);
                else if(strcmp(key, "cooldown") == 0)      cooldown = atoi(value);
                else if(strcmp(key, "score") == 0)         score = atoi(value);
                else if(strcmp(key, "invincibility") == 0) invincibility = atoi(value);
                else if(strcmp(key, "shoot") == 0) {       shoot = get_shoot_function(atoi(value));
                    break;
                }
            }
        }
    }

    if(current_id == '0') {
        printf("Error : Ennemy type not found\n");
        return NULL;
    }

    fclose(file);

    insert_entity(game, create_entity(x, -height, width, height, speed, movement, animation, ennemy, ENNEMY));
    ennemy->ship = create_spaceship(life, cooldown, invincibility, shoot);
    ennemy->score = score;
    return ennemy;
}

void free_ennemy(Ennemy *ennemy) {
    free_spaceship(ennemy->ship);
    free(ennemy);
}


int on_collide_ennemy(Game *game, Ennemy *ennemy, Entity *collide, Direction direction) {
    if(collide->type == PLAYER) {
        deals_damage(game, collide, 1);
        return 1;
    }
    return 0;
}
