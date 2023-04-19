#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"

Animation* init_sprite(MLV_Image* sprite) {
    Animation* animation = malloc(sizeof(Animation));
    animation->type = SPRITE;
    animation->sprite = sprite;
    return animation;
}
Animation* init_square(MLV_Color color) {
    Animation* animation = malloc(sizeof(Animation));
    animation->type = SQUARE;
    animation->color = color;
    return animation;
}

void free_animation(Animation* animation) {
    if(animation->type == SPRITE) {
        MLV_free_image(animation->sprite);
    }
    free(animation);
}

void draw_entity(Entity* entity) {
    Animation *animation = entity->sprite;

    switch(animation->type) {
        case SQUARE:
            MLV_draw_filled_rectangle(
                entity->x, 
                entity->y, 
                entity->width, 
                entity->height, 
                animation->color
            );
            break;
        case SPRITE:
            MLV_resize_image(animation->sprite, entity->width, entity->height);
            MLV_draw_image(animation->sprite, entity->x, entity->y);
            break;
    }

}