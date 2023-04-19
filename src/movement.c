#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"
#include "../include/movement.h"


void movement_none(Entity *entity) {
    Speed *speed = entity->speed;
    speed->speed_x = 0;
    speed->speed_y = 0;
}

void movement_forward(Entity *entity) {
    Speed *speed = entity->speed;
    speed->speed_x = 0;
    speed->speed_y = speed->speed;
}

void movement_infinite_scroll(Entity *entity) {
    movement_forward(entity);
    if(entity->y > WIN_HEIGHT) {
        entity->y = -entity->height;
    }
}