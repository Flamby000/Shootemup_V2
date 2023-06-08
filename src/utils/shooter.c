#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/logic/entity.h"
#include "../../include/logic/ennemy.h"
#include "../../include/logic/missile.h"
#include "../../include/utils/shooter.h"

SHOOT_FUNC get_shoot_function(int id) {
    switch(id) {
        case SHOOT_PLAYER_BASIC:     return shoot_player_basic;    /* id : 0 */
        case SHOOT_BASIC:            return shoot_basic;           /* id : 1 */
        case SHOOT_TARGET_PLAYER:    return shoot_target_player;   /* id : 2 */
        case SHOOT_PERFORING_PLAYER: return shoot_player_perforing;/* id : 3 */
        case SHOOT_NONE:             return shoot_none;            /* id : 4 */
        case SHOOT_SUPER_LASER:      return shoot_super_laser;     /* id : 5 */
        case SHOOT_MULTIDIRECTIONAL: return shoot_multidirectional;/* id : 6 */
        case SHOOT_360_DIRECTION:    return shoot_360_direction;   /* id : 7 */
        default: return shoot_basic;
    }
}

int shoot_player_basic(Game *game, Entity *entity) {
    Player *player = (Player*)entity->parent;
    if(MLV_get_keyboard_state(player->key_shoot) == MLV_PRESSED) {
       create_missile(game, entity, BASIC_PLAYER_MISSILE, -1);
       return 1;
    }
    return 0;
}

int shoot_player_perforing(Game *game, Entity *entity) {
    Player *player = (Player*)entity->parent;

    if(MLV_get_keyboard_state(player->key_shoot) == MLV_PRESSED) {
       create_missile(game, entity, PERFORING_PLAYER_MISSILE, -1);
       return 1;
    }
    return 0;
}

int shoot_basic(Game *game, Entity *entity) {
    create_missile(game, entity, BASIC_MISSILE, -1);
    return 1;
}

int shoot_target_player(Game *game, Entity *entity) {
    create_missile(game, entity, TARGET_PLAYER_MISSILE, -1);
    return 1;
}


int shoot_none(Game *game, Entity *entity) {
    return 0;
}

int shoot_super_laser(Game *game, Entity *entity) {
    Player *player = (Player*)entity->parent;

    if(MLV_get_keyboard_state(player->key_super_shoot) == MLV_PRESSED) {
        create_missile(game, entity, SUPER_LASER_MISSILE, -1);
       return 1;
    }
    return 0;
}

int shoot_multidirectional(Game *game, Entity *entity) {
    Player *player = (Player*)entity->parent;

    if(MLV_get_keyboard_state(player->key_shoot) == MLV_PRESSED) {
        create_shoot_line(game, entity, "0X6X0");
        return 1;
    }
    return 0;
}

int shoot_360_direction(Game *game, Entity *entity) {
    create_missile(game, entity, BASIC_MISSILE, -1);

    return 0;
}