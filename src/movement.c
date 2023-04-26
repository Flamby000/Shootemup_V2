#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"
#include "../include/entity.h"
#include "../include/movement.h"
#include "../include/utils.h"


SPEED_FUNC get_movement_function(int id) {
    switch(id) {
        case MOVEMENT_NONE:            return movement_none;            /* id : 0 */
        case MOVEMENT_FORWARD:         return movement_forward;         /* id : 1 */
        case MOVEMENT_BACKWARD:        return movement_backward;        /* id : 2 */
        case MOVEMENT_INFINITE_SCROLL: return movement_infinite_scroll; /* id : 3 */
        case MOVEMENT_CONTROLLER:      return movement_controller;      /* id : 4 */
        case MOVEMENT_FOLLOW_PLAYER:   return movement_follow_player;   /* id : 5 */
        case MOVEMENT_SINUSOIDAL:      return movement_sinusoidal;      /* id : 6 */
        case MOVEMENT_CIRCLE_ENTITY:   return movement_circle_entity;   /* id : 7 */
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

void movement_sinusoidal(Game *game, Entity *entity) {
    Speed *speed = entity->speed;
    speed->speed_x = (speed->speed*2) * sin (entity->y * 0.01);
    speed->speed_y = speed->speed;
}

void movement_controller(Game *game, Entity *entity) {
    Speed *speed = entity->speed;

    if(MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED) {
        if(speed->speed_y > -speed->speed) {
            speed->speed_y -= 2;
            if(speed->speed_y < -speed->speed) {
                speed->speed_y = -speed->speed;
            }
        }
    } else if(MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED) {
        if(speed->speed_y < speed->speed) {
            speed->speed_y += 2;
            if(speed->speed_y > speed->speed) {
                speed->speed_y = speed->speed;
            }
        }
    } else {
        if(speed->speed_y > 0) {
            speed->speed_y -= 0.1;
            if(speed->speed_y < 0) {
                speed->speed_y = 0;
            }
        } else if(speed->speed_y < 0) {
            speed->speed_y += 0.1;
            if(speed->speed_y > 0) {
                speed->speed_y = 0;
            }
        }
    }
    
    if(MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED) {
        if(speed->speed_x > -speed->speed) {
            speed->speed_x -= 2;
            if(speed->speed_x < -speed->speed) {
                speed->speed_x = -speed->speed;
            }
        }
    } else if(MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED) {
        if(speed->speed_x < speed->speed) {
            speed->speed_x += 2;
            if(speed->speed_x > speed->speed) {
                speed->speed_x = speed->speed;
            }
        }
        speed->speed_x = speed->speed;
    } else {
        if(speed->speed_x > 0) {
            speed->speed_x -= 0.1;
            if(speed->speed_x < 0) {
                speed->speed_x = 0;
            }
        } else if(speed->speed_x < 0) {
            speed->speed_x += 0.1;
            if(speed->speed_x > 0) {
                speed->speed_x = 0;
            }
        }
    }

    avoid_collide_border(entity);
}


void movement_follow_player(Game *game, Entity *entity) {
    movement_follow_entity(game, entity, closest_entity(game, entity, PLAYER));
}

void movement_follow_entity(Game *game, Entity *entity, Entity *target) {
    float angle;

    if(target != NULL) {
        angle = atan2((target->y + target->height/2) - entity->y, (target->x + target->width/2)  - entity->x);
        entity->speed->speed_x = entity->speed->speed * cos(angle);
        entity->speed->speed_y = entity->speed->speed * sin(angle);
    }
     else {
        movement_forward(game, entity);
    }
}

void movement_circle_entity(Game *game, Entity *entity) {
    Entity *player_entity = closest_entity(game, entity, PLAYER);
    entity->x = player_entity->x + (player_entity->width/2)  + (cos(get_timestamp_ms()/1000.0) * 100);
    entity->y = player_entity->y + (player_entity->height/2) + (sin(get_timestamp_ms()/1000.0) * 100);
}

void push_entity(Game *game, Entity *entity) {
    Speed *speed = entity->speed;
    speed->speed_y +=20;
}

