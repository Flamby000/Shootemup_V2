#ifndef BACKGROUND_H
#define BACKGROUND_H

/**
 * @brief Init the background of the game
 * 
 * @param game to init the background
 */
void init_background(Game *game);

/**
 * @brief Set the speed of the background
 * 
 * @param game to set the background speed
 * @param factor to multiply the speed
 */
void set_background_speed(Game *game, double factor);

#endif