#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/entity.h"

Entity* create_entity(int x, int y, int width, int height, 
                      int speed, void (*update_speed)(struct _Entity*),
                      Animation* animation) {

    Entity* entity = malloc(sizeof(Entity));
    entity->x = x;
    entity->y = y;
    entity->width = width;
    entity->height = height;
    entity->rotation = 0;
    entity->sprite = animation;

    entity->speed = malloc(sizeof(Speed));
    entity->speed->speed_x = 0;
    entity->speed->speed_y = 0;
    entity->speed->speed = speed;  
    entity->speed->update_speed = update_speed;  
        
    return entity;
}    

void update_entity(Entity *entity) {
    entity->speed->update_speed(entity);
    entity->x += entity->speed->speed_x;
    entity->y += entity->speed->speed_y;
}

void free_entity(Entity *entity) {
    free_animation(entity->sprite);
    free(entity->speed);
    free(entity);
}