#ifndef ANIMATION_H
#define ANIMATION_H

Animation* init_sprite(MLV_Image* sprite);
Animation* init_square(MLV_Color color);
Animation* init_animation(char* path);
Animation* init_multiple_animation(char* forward_path, char* backward_path, char* left_path, char* right_path);
Animation* init_animation_wrapper(char* str);

void free_animation(Animation* animation);
void draw_entity(Entity* entity, Entity* parent);

#endif