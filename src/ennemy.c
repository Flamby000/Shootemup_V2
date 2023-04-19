#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/spaceship.h"

#include "../include/entity.h"
#include "../include/player.h"
#include "../include/movement.h"


Ennemy* create_ennemy(Game *game, char type, int x) {
    Ennemy* ennemy = malloc(sizeof(Ennemy));
    int width, height;
    ennemy->type = type;

    switch (type) {
        case BASIC_ENNEMY:
        height = 60;
        width = 43;
        insert_entity(game,
            create_entity(
                x,
                -height,
                width,
                height,
                1,
                movement_forward,
                init_sprite(MLV_load_image("resources/ennemies/ennemy1-forward-1.png")),
                ennemy, ENNEMY));
        ennemy->ship = create_spaceship(1, 1000, NULL);
            break;
        default:
        printf("Error : Ennemy type not found\n");
            break;
    }
    ennemy->score = 10;
    return ennemy;
}

void free_ennemy(Game *game, Ennemy *ennemy) {
    free_spaceship(ennemy->ship);
    remove_entity(game, ennemy->entity);
    free(ennemy);
}


