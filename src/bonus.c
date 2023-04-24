#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/animation.h"
#include "../include/movement.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/bonus.h"


Bonus *create_bonus(Game *game, char type, int x) {
    Bonus* bonus = malloc(sizeof(Bonus));
    int width, height, speed;
    BONUS_FUNC effect;
    Animation *animation;
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
                    printf("line : %s\n", line);

        if(strchr(line, ':') != NULL) {
            char *token = strtok(line, ":");
            strcpy(key, token);
            token = strtok(NULL, ":");
            strcpy(value, token);


            if(strcmp(key, "id") == 0) current_id = value[0];

            if(current_id == type) {
                if(     strcmp(key, "width") == 0)         width = atoi(value);
                else if(strcmp(key, "height") == 0)        height = atoi(value);
                else if(strcmp(key, "effect") == 0)        effect = get_bonus_effect_by_id(atoi(value));
                else if(strcmp(key, "animation") == 0)     animation = init_animation_wrapper(value);
                    break;
            }
        }
    }

    if(current_id == '0') {
        printf("Error : Ennemy type not found\n");
        return NULL;
    }
    speed = 10;

    bonus->entity = create_entity(x, -height, width, height, speed, movement_forward, animation, bonus, BONUS);
    bonus->effect = effect;
    insert_entity(game, bonus->entity);
    return bonus;
}

Bonus *create_random_bonus(Game *game, int x) {
    return NULL;
}

BONUS_FUNC get_bonus_effect_by_id(int id) {
    switch(id) {
        case SHIELD_BONUS: return shield_bonus; /* ID : 1*/
        default: return NULL;
    } 
}

int on_collide_bonus(Game *game, Bonus *bonus, Entity *collide, Direction direction) {
    return 0;
}

void shield_bonus(Game *game, Player* eater, int reverse) {

}

