#ifndef ANIMATION_H
#define ANIMATION_H

#define EXPLOSION_1 "resources/explosions/explosion%d.png"

Animation* init_sprite(MLV_Image* sprite);
Animation* init_square(MLV_Color color);
Animation* init_animation(char* path);
Animation* init_multiple_animation(char* forward_path, char* backward_path, char* left_path, char* right_path);
Animation* init_animation_wrapper(char* str);

void create_one_shot_animation(Game *game,char *path, Entity* entity);
void free_animation(Animation* animation);
void draw_entity(Game *game, Entity* entity, Entity* parent);

#endif