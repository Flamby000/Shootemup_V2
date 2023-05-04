#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/entity.h"
#include "../include/frame.h"
#include "../include/movement.h"
#include "../include/game.h"
#include "../include/interface/menu.h"
#include "../include/animation.h"

Animation* init_animation_wrapper(char* str) {
    if(strstr(str, "%d")) return init_animation(str);
    else return init_sprite(MLV_load_image(str));
}

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

void create_one_shot_animation(Game *game, char *path, Entity *entity) {
    Entity *entity_new;

    if(path == NULL) return;
    entity_new = create_entity(
        entity->x, entity->y, 
        entity->width, entity->height,
        0, movement_none,
        init_animation(path), NULL,
        NULL, LABEL);
    entity_new->sprite->type = ONE_SHOT_ANIMATION;
    entity_new->sprite->frame_duration = 100;

    insert_entity(game, entity_new);
}

Animation* init_animation(char* path) {
    Animation* animation = malloc(sizeof(Animation));
    int i;
    char path_i[1000];
    animation->nb_frames = 1;  
    animation->type = ANIMATED;

    while(1) {
        sprintf(path_i, path, animation->nb_frames);
        if(!MLV_path_is_a_file(path_i))  {
            break; 
        }
        animation->nb_frames++;
    }

    animation->forward_images = malloc(animation->nb_frames * sizeof(MLV_Image*));

    for(i = 1; i <= animation->nb_frames; i++) {
        sprintf(path_i, path, i);
        animation->forward_images[i-1] = MLV_load_image(path_i);
    }
    animation->current_frame = 0;
    animation->last_frame_time = 0;
    animation->frame_duration = 100;
    return animation;
}

Animation* init_multiple_animation(char* forward_path, char* backward_path, char* left_path, char* right_path) {
    Animation* animation = malloc(sizeof(Animation));
    int i;
    char path_i[1000];
    animation->nb_frames = 1;  
    animation->type = MULTIPLE_ANIMATED;

    while(1) {
        sprintf(path_i, forward_path, animation->nb_frames);
        if(!MLV_path_is_a_file(path_i))  {
            break; 
        }
        animation->nb_frames++;
    }

    animation->forward_images = malloc(animation->nb_frames * sizeof(MLV_Image*));
    for(i = 1; i <= animation->nb_frames; i++) {
        sprintf(path_i, forward_path, i);
        animation->forward_images[i-1] = MLV_load_image(path_i);
    }
    animation->backward_images = malloc(animation->nb_frames * sizeof(MLV_Image*));
    for(i = 1; i <= animation->nb_frames; i++) {
        sprintf(path_i, backward_path, i);
        animation->backward_images[i-1] = MLV_load_image(path_i);
    }
    animation->left_images = malloc(animation->nb_frames * sizeof(MLV_Image*));
    for(i = 1; i <= animation->nb_frames; i++) {
        sprintf(path_i, left_path, i);
        animation->left_images[i-1] = MLV_load_image(path_i);
    }
    animation->right_images = malloc(animation->nb_frames * sizeof(MLV_Image*));
    for(i = 1; i <= animation->nb_frames; i++) {
        sprintf(path_i, right_path, i);
        animation->right_images[i-1] = MLV_load_image(path_i);
    }

    animation->current_frame = 0;
    animation->last_frame_time = MLV_get_time();
    animation->frame_duration = 100;
    return animation;
}

void free_animation(Animation* animation) {
    int i;
    if(animation == NULL) return;
    switch(animation->type) {
        case ANIMATED || ONE_SHOT_ANIMATION:
            for(i = 0; i < animation->nb_frames; i++) {
                MLV_free_image(animation->forward_images[i]);
            }
            free(animation->forward_images);
            break;
        case SPRITE:
            MLV_free_image(animation->sprite);
            break;
        case MULTIPLE_ANIMATED:
            for(i = 0; i < animation->nb_frames; i++) {
                MLV_free_image(animation->forward_images[i]);
                MLV_free_image(animation->backward_images[i]);
                MLV_free_image(animation->left_images[i]);
                MLV_free_image(animation->right_images[i]);
            }
            free(animation->forward_images);
            free(animation->backward_images);
            free(animation->left_images);
            free(animation->right_images);
            break;
        default:
            break;
    }
    free(animation);
}

void draw_entity(Game *game, Entity* entity, Entity* parent) {
    EntityLink *child;
    Animation *animation = entity->sprite;
    int parent_x = 0;
    int parent_y = 0;

    if(entity->type == BUTTON) draw_button(game, (Button*)entity->parent);

    if(animation == NULL) return; /* Don't draw entities without animation*/
    if(parent != NULL) {
        parent_x = parent->x;
        parent_y = parent->y;
    }
    

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
            MLV_draw_image(animation->sprite, parent_x+entity->x, parent_y+entity->y);
            break;
        case ANIMATED:
            MLV_resize_image(animation->forward_images[animation->current_frame], entity->width, entity->height);
            /*int speed_x = entity->speed->speed_x;
            int speed_y = entity->speed->speed_y;
            MLV_rotate_image(animation->forward_images[animation->current_frame], atan2(speed_y, speed_x));
            */
            MLV_draw_image(animation->forward_images[animation->current_frame], parent_x+entity->x, parent_y+entity->y);

            if(MLV_get_time() - animation->last_frame_time > animation->frame_duration) {
                animation->current_frame++;
                if(animation->current_frame >= animation->nb_frames-1) animation->current_frame = 0; 
                animation->last_frame_time = MLV_get_time();
            }
            break;
        case ONE_SHOT_ANIMATION :
            MLV_resize_image(animation->forward_images[animation->current_frame], entity->width, entity->height);
            MLV_draw_image(animation->forward_images[animation->current_frame], parent_x+entity->x, parent_y+entity->y);

            if(MLV_get_time() - animation->last_frame_time > animation->frame_duration) {
                animation->current_frame++;
                animation->last_frame_time = MLV_get_time();

                if(animation->current_frame >= animation->nb_frames-1) {
                    remove_entity(game, entity, 0);
                    return;
                }
            }
            break;
        case MULTIPLE_ANIMATED:
            switch(get_direction(entity)) {
                case TOP:
                    MLV_resize_image(animation->forward_images[animation->current_frame], entity->width, entity->height);
                    MLV_draw_image(animation->forward_images[animation->current_frame], parent_x+entity->x, parent_y+entity->y);
                    break;
                case BOTTOM:
                    MLV_resize_image(animation->backward_images[animation->current_frame], entity->width, entity->height);
                    MLV_draw_image(animation->backward_images[animation->current_frame], parent_x+entity->x, parent_y+entity->y);
                    break;
                case LEFT:
                    MLV_resize_image(animation->left_images[animation->current_frame], entity->width, entity->height);
                    MLV_draw_image(animation->left_images[animation->current_frame], parent_x+entity->x, parent_y+entity->y);
                    break;
                case RIGHT:
                    MLV_resize_image(animation->right_images[animation->current_frame], entity->width, entity->height);
                    MLV_draw_image(animation->right_images[animation->current_frame], parent_x+entity->x, parent_y+entity->y);
                    break;
                default:
                    break;
            }
            if(MLV_get_time() - animation->last_frame_time > animation->frame_duration) {
                animation->current_frame++;
                if(animation->current_frame >= animation->nb_frames-1) animation->current_frame = 0; 
                animation->last_frame_time = MLV_get_time();
            }
            break;
        default:
            break;
    }

    if(entity->type == ENNEMY) draw_ennemy(game, (Ennemy*)entity->parent);

    for(child = entity->children; child != NULL; child = child->next) {
        draw_entity(game, child->entity, entity);
    }
    
    
}