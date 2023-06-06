/**
 * @file animation.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to create and display animations
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ANIMATION_H
#define ANIMATION_H

/**
 * @brief Path to explosion images
 * 
 */
#define EXPLOSION_1 "resources/explosions/explosion%d.png"

/**
 * @brief Create a animation structure with non-animated sprite
 * 
 * @param sprite which will be displayed
 * @return An animation using only one image
 */
Animation* init_sprite(MLV_Image* sprite);

/**
 * @brief Create a animation structure with only one color to draw a square shape
 * 
 * @param color to used for the square
 * @return An animation drawing a simple square
 */
Animation* init_square(MLV_Color color);

/**
 * @brief Create a animation structure with multiple sprite
 * 
 * @param path to the file name containing image (it must contain %d to be replaced by the frame number)
 * @return An animation using multiple images
 */
Animation* init_animation(char* path);

/**
 * @brief Create a animation structure with multiple sprite for each direction of the entity
 * 
 * @param forward_path the files used to draw forward animation
 * @param backward_path the files used to draw backward animation
 * @param left_path the files used to draw left animation
 * @param right_path the files used to draw right animation
 * @return An animation using multiple images for each direction
 */
Animation* init_multiple_animation(char* forward_path, char* backward_path, char* left_path, char* right_path);

/**
 * @brief Create a simple sprite or an animation depending on the file name
 * 
 * @param str the files used to draw forward animation
 * @return The animation structure
 */
Animation* init_animation_wrapper(char* str);

/**
 * @brief Create a one shot animation displayed one time
 * 
 * @param game to display the animation
 * @param path to the file name containing images (it must contain %d to be replaced by the frame number)
 * @param entity linked to the animation
 */
void create_one_shot_animation(Game *game, char *path, Entity* entity);

/**
 * @brief Free the memory of the animation
 * 
 * @param animation to free
 */
void free_animation(Animation* animation);

/**
 * @brief Draw the animation
 * 
 * @param game to display the animation
 * @param entity linked to the animation
 * @param parent of the entity if it have one
 */
void draw_entity(Game *game, Entity* entity, Entity* parent);

Animation* copy_animation(Animation* animation);
#endif