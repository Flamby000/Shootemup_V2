#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/movement.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/spaceship.h"
#include "../include/entity.h"
#include "../include/missile.h"

Missile* create_missile(Game *game, Entity *sender, int type) {
    Missile *missile;
    int width, height, speed, damage, x, y;
    void (*movement)(struct _Game*, struct _Entity*);
    Animation *animation;
    char key[200];
    char value[200];
    char line[400];
    int current_id = -1;
    FILE *file = fopen(MISSILE_DATA_PATH, "r");

    if(file == NULL) {
        printf("Error : Cannot open file %s\n", MISSILE_DATA_PATH);
        return NULL;
    }
    while(fscanf(file, "%s", line) != EOF) {
        if(strchr(line, ':') != NULL) {
            char *token = strtok(line, ":");
            strcpy(key, token);
            token = strtok(NULL, ":");
            strcpy(value, token);

            if(strcmp(key, "id") == 0) current_id = atoi(value);

            if(current_id == type) {
                if(     strcmp(key, "width") == 0)     width = atoi(value);
                else if(strcmp(key, "height") == 0)    height = atoi(value);
                else if(strcmp(key, "animation") == 0) animation = init_animation_wrapper(value);
                else if(strcmp(key, "speed") == 0)     speed = atoi(value);
                else if(strcmp(key, "damage") == 0)    damage = atoi(value);
                else if(strcmp(key, "movement") == 0){ movement = get_movement_function(atoi(value));
                    break;
                } 
            }
        }
    }
    fclose(file);

    if(current_id == -1) {
        printf("Error : Cannot find missile with id %d\n", type);
        return NULL;
    }

    x = sender->x + sender->width/2 - width/2;
    y = sender->y + sender->height/2 - height/2;

    missile = malloc(sizeof(Missile));
    missile->entity = create_entity(x, y, width, height, speed, movement, animation, missile, MISSILE);
    missile->damage = damage;
    if(sender->type == PLAYER) missile->is_from_player = 1;
    else missile->is_from_player = 0;

    insert_entity(game, missile->entity);
    return missile;
}

void free_missile(Missile *missile) {
    free(missile);
}

void on_collide_missile(Game *game, Missile *missile, Entity *collide) {
    if(collide->type == PLAYER && !missile->is_from_player) {
        deals_damage(game, collide, missile->damage);
        remove_entity(game, missile->entity);
    }
    else if(collide->type == ENNEMY && missile->is_from_player) {
        deals_damage(game, collide, missile->damage);
        remove_entity(game, missile->entity);
    }

}
