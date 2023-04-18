#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"

Animation init_sprite(MLV_Image* sprite) {
    Animation animation;
    animation.is_animated = 0;
    animation.sprite = sprite;
    return animation;
}

void free_animation(Animation* animation) {
    if(animation->is_animated) {
        MLV_free_image(animation->sprite);
    }
}

void draw_entity(Entity* entity) {
    Animation *animation = entity->sprite;

    if(!animation->is_animated) {
        MLV_resize_image(animation->sprite, entity->width, entity->height);
        MLV_draw_image(animation->sprite, entity->x, entity->y);
    }
}