#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/missile.h"
#include "../include/shooter.h"

int shoot_player_basic(Game *game, Entity *entity) {
    if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED) {
       create_missile(game, entity, BASIC_PLAYER_MISSILE);
       return 1;
    }

    return 0;
}

int shoot_basic(Game *game, Entity *entity) {
    create_missile(game, entity, BASIC_MISSILE);
    return 1;
}