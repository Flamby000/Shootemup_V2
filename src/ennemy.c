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

Ennemy* create_ennemy(Game *game, char type, int x) {
    Ennemy* ennemy = malloc(sizeof(Ennemy));
    int width, height, speed, cooldown, life, score;
    void (*movement)(struct _Game*, struct _Entity*);
    int (*shoot)(struct _Game*, struct _Entity*);
    Animation *animation;

    switch (type) {
        case BASIC_ENNEMY:
            height = 60;
            width = 43;
            speed = 5;
            cooldown = 1000;
            life = 1;
            score = 10;
            animation = init_animation("resources/ennemies/ennemy1-forward-%d.png");
            movement = movement_forward;
            shoot = shoot_basic;
            break;

        default:
            printf("Error : Ennemy type not found\n");
            break;
    }


    insert_entity(game, create_entity(x, -height, width, height, speed, movement, animation, ennemy, ENNEMY));
    ennemy->ship = create_spaceship(life, cooldown, shoot);
    ennemy->score = score;
    ennemy->type = type;

    return ennemy;
}

void free_ennemy(Ennemy *ennemy) {
    free_spaceship(ennemy->ship);
    free(ennemy);
}


