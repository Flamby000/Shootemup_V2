/**
 * @file frame.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to create and display the game frame
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FRAME_H
#define FRAME_H

/**
 * @brief The default window width
 * 
 */
#define WIN_WIDTH 1200

/**
 * @brief The default window height
 * 
 */
#define WIN_HEIGHT 800

/**
 * @brief Path of the font
 * 
 */
#define FONT_PATH "resources/fonts/Retro.ttf"

/**
 * @brief Initialize the frame
 * 
 */
void init_frame();

/**
 * @brief Draw the game on the frame
 * 
 * @param game to draw
 */
void draw_frame(Game* game);

/**
 * @brief Free the frame memory
 * 
 */
void free_frame();

/**
 * @brief Draw the player data on the frame (Its HUD)
 * 
 * @param game of the player
 * @param player to draw the data
 */
void draw_player(Game *game, Player* player);

/**
 * @brief Draw the ennemy data on the frame
 * 
 * @param game of the ennemy
 * @param ennemy to draw the data
 */
void draw_ennemy(Game *game, Ennemy *ennemy);

/**
 * @brief Draw a bar on the frame
 * 
 * @param x position of the bar
 * @param y position of the bar
 * @param width width of the bar
 * @param height height of the bar
 * @param value of the data to display
 * @param max_value of the data to displaye
 * @param color of the bar
 * @param display_value 1 if the value must be displayed, 0 otherwise
 * @param name of the bar
 * @param flash 1 if the bar must flash, 0 otherwise
 * @param flash_color of the bar when it is flashing
 */
void draw_bar(int x, int y, int width, int height, int value, int max_value, MLV_Color color, int display_value, char* name, int flash, MLV_Color flash_color);

void draw_image_progress(MLV_Image* image, MLV_Image *dark_image, int x, int y, int width, int height, int value, int max_value);

#endif