#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"
#include "../include/entity.h"
#include "../include/movement.h"

void (*get_movement_function(int id)) (Game*, Entity*) {
    switch(id) {
        case MOVEMENT_NONE:            return movement_none;            /* id : 0 */
        case MOVEMENT_FORWARD:         return movement_forward;         /* id : 1 */
        case MOVEMENT_BACKWARD:        return movement_backward;        /* id : 2 */
        case MOVEMENT_INFINITE_SCROLL: return movement_infinite_scroll; /* id : 3 */
        case MOVEMENT_CONTROLLER:      return movement_controller;      /* id : 4 */
        default:                       return movement_none;
    }
}

void movement_none(Game *game, Entity *entity) {
    Speed *speed = entity->speed;
    speed->speed_x = 0;
    speed->speed_y = 0;
}

void movement_forward(Game *game, Entity *entity) {
    Speed *speed = entity->speed;
    speed->speed_x = 0;
    speed->speed_y = speed->speed;
}

void movement_backward(Game *game, Entity *entity) {
    Speed *speed = entity->speed;
    speed->speed_x = 0;
    speed->speed_y = -speed->speed;
}


void movement_infinite_scroll(Game *game, Entity *entity) {
    movement_forward(game, entity);
    if(entity->y > settings->win_height) {
        entity->y = -entity->height;
    }
}

void movement_controller(Game *game, Entity *entity) {
    Speed *speed = entity->speed;

    if(MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED) {
        speed->speed_y = -speed->speed;
    } else if(MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED) {
        speed->speed_y = speed->speed;
    } else {
        speed->speed_y = 0;
    }
    
    if(MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED) {
        speed->speed_x = -speed->speed;
    } else if(MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED) {
        speed->speed_x = speed->speed;
    } else {
        speed->speed_x = 0;
    }

    avoid_collide_border(entity);
}