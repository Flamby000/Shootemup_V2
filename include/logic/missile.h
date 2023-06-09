/**
 * @file missile.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to manage the logic of a missile
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MISSILE_H
#define MISSILE_H

/**
 * @brief The path of the file containing the missiles data
 * 
 */
#define MISSILE_DATA_PATH "data/missiles.data"

/**
 * @brief The ID of the basic player missile
 * 
 */
#define BASIC_PLAYER_MISSILE 0

/**
 * @brief The id of the basic missile from an ennemy
 * 
 */
#define BASIC_MISSILE 1

/**
 * @brief The id of the missile targeting the player
 * 
 */
#define TARGET_PLAYER_MISSILE 2

/**
 * @brief The id of the missile perforing entities
 * 
 */
#define PERFORING_PLAYER_MISSILE 3

/**
 * @brief The id of protecting missile
 * 
 */
#define PROTECTING_MISSILE 4

/**
 * @brief The id of the super laser missile
 * 
 */
#define SUPER_LASER_MISSILE 5


/**
 * @brief 
 * 
 */
#define DIRECTIONAL_MISSILE 7

/**
 * @brief Free the memory allocated for the missile
 * 
 * @param missile to free
 */
void free_missile(Missile *missile);

/**
 * @brief Create a missile object
 * 
 * @param game of the missile
 * @param sender of the missile
 * @param type id of the missile type
 * @param x position to spawn the missile
 * @return Pointer of the created missile
 */
Missile* create_missile(Game *game, Entity *sender, int type, int x);

/**
 * @brief Load a missile from the missiles data file with its type id
 * 
 * @param id of the missile type
 * @param sender of the missile
 * @return Pointer of the created missile
 */
Missile* load_missile(int id, Entity *sender);

/**
 * @brief Called when the missile is collided by another entity
 * 
 * @param game of the missile
 * @param missile collided
 * @param collide entity
 * @param direction of the collision
 * @return 1 if an entity was destroyed, 0 otherwise
 */
int on_collide_missile(Game *game, Missile *missile, Entity *collide, Direction direction);

/**
 * @brief Called each frame to update the missile's data
 * 
 * @param game of the missile
 * @param missile to update
 * @return 1 if the missile was destroyed, 0 otherwise
 */
int update_missile(Game *game, Missile *missile);


Missile* create_directional_missile(Game *game, Entity *sender, int direction);
#endif 
