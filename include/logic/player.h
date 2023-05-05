/**
 * @file player.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to manage the logic of a player
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

/**
 * @brief Default width of the player
 * 
 */
#define PLAYER_WIDTH 42

/**
 * @brief Default height of the player
 * 
 */
#define PLAYER_HEIGHT 74    

/**
 * @brief Create a player object
 * 
 * @param game to create the player
 * @param player_number of the player
 * @return Pointer of the created player
 */
Player* create_player(Game *game, int player_number);

/**
 * @brief Free the player allocated memory
 * 
 * @param game of the player to free
 * @param player to free
 */
void free_player(Game* game, Player* player);

/**
 * @brief Called when a player is collided by another entity
 * 
 * @param game of the player
 * @param player collided
 * @param collide other entity
 * @param direction of the collision
 * @return 1 if an entity were removed, 0 otherwise
 */
int on_collide_player(Game *game, Player *player, Entity *collide, Direction direction);


#endif