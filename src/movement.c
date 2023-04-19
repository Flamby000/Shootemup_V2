#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"
#include "../include/entity.h"
#include "../include/movement.h"

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
    if(entity->y > WIN_HEIGHT) {
        entity->y = -entity->height;
    }
}

void movement_controller(Game *game, Entity *entity) {
    Speed *speed = entity->speed;

    if(MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED) {
        speed->speed_y = -speed->speed;
    } else if(MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED) {
        speed->speed_y = speed->speed;
    } else {
        speed->speed_y = 0;
    }
    
    if(MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED) {
        speed->speed_x = -speed->speed;
    } else if(MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED) {
        speed->speed_x = speed->speed;
    } else {
        speed->speed_x = 0;
    }

    avoid_collide_border(entity);
}




