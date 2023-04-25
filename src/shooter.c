#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/missile.h"
#include "../include/shooter.h"

SHOOT_FUNC get_shoot_function(int id) {
    switch(id) {
        case SHOOT_PLAYER_BASIC:  return shoot_player_basic; /* id : 1 */
        case SHOOT_BASIC:         return shoot_basic;        /* id : 2 */
        case SHOOT_TARGET_PLAYER: return shoot_target_player;/* id : 3 */
        case SHOOT_PERFORING_PLAYER: return shoot_player_perforing;/* id : 4 */
        default: return shoot_basic;
    }
}

int shoot_player_basic(Game *game, Entity *entity) {
    if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED) {
       create_missile(game, entity, BASIC_PLAYER_MISSILE);
       return 1;
    }
    return 0;
}

int shoot_player_perforing(Game *game, Entity *entity) {
    if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED) {
       create_missile(game, entity, PERFORING_PLAYER_MISSILE);
       return 1;
    }
    return 0;
}


int shoot_basic(Game *game, Entity *entity) {
    create_missile(game, entity, BASIC_MISSILE);
    return 1;
}

int shoot_target_player(Game *game, Entity *entity) {
    create_missile(game, entity, TARGET_PLAYER_MISSILE);
    return 1;
}

