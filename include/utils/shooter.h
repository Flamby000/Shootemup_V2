/**
 * @file shooter.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to create the missiles from a sender when it shoot
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SHOOTER_H
#define SHOOTER_H

/**
 * @brief Get the shoot function from its ID
 * 
 * @param id of the shoot function
 * @return SHOOT_FUNCT pointer defining a shoot pattern
 */
SHOOT_FUNC get_shoot_function(int id);

/**
 * @brief ID of the function shoot_player_basic
 * 
 */
#define SHOOT_PLAYER_BASIC 0

/**
 * @brief Shoot a basic missile from the player
 * 
 * @param game of the sender
 * @param entity shooting
 * @return 0 if success, 1 overwise
 */
int shoot_player_basic(Game *game, Entity *entity);

/**
 * @brief ID of the function shoot_basic
 * 
 */
#define SHOOT_BASIC 1

/**
 * @brief Shoot a basic missile from an ennemy
 * 
 * @param game of the sender
 * @param entity shooting
 * @return 1 if success, 0 overwise
 */
int shoot_basic(Game *game, Entity *entity);

/**
 * @brief ID of the function shoot_target_player
 * 
 */
#define SHOOT_TARGET_PLAYER 2

/**
 * @brief Shoot a missile from an ennemy to the player
 * 
 * @param game of the sender
 * @param entity shooting
 * @return 1 if success, 0 overwise
 */
int shoot_target_player(Game *game, Entity *entity);

/**
 * @brief ID of the function shoot_perforing_player
 * 
 */
#define SHOOT_PERFORING_PLAYER 3

/**
 * @brief Shoot a perforing missile from the player
 * 
 * @param game of the sender
 * @param entity shooting
 * @return 1 if success, 0 overwise
 */
int shoot_player_perforing(Game *game, Entity *entity);

/**
 * @brief ID of the function shoot_none
 * 
 */
#define SHOOT_NONE 4

/**
 * @brief Do nothing
 * 
 * @param game of the entity
 * @param entity to not shoot
 * @return 0
 */
int shoot_none(Game *game, Entity *entity);

/**
 * @brief ID of the function shoot_super_laser
 * 
 */
#define SHOOT_SUPER_LASER 5
/**
 * @brief Shoot a super laser from the player
 * 
 * @param game of the sender
 * @param entity shooting
 * @return 1 if success, 0 overwise
 */
int shoot_super_laser(Game *game, Entity *entity);

/**
 * @brief ID of the function shoot_multidirectional
 * 
 */
#define SHOOT_MULTIDIRECTIONAL 6

/**
 * @brief Shoot missiles in multiple direction from the player
 * 
 * @param game of the sender
 * @param entity shooting
 * @return 1 if success, 0 overwise
 */
int shoot_multidirectional(Game *game, Entity *entity);

/**
 * @brief ID of the function shoot_360_direction
 * 
 */
#define SHOOT_360_DIRECTION 7

/**
 * @brief Shoot missiles in multiple direction from the sender
 * 
 * @param game of the sender
 * @param entity shooting
 * @return 1 if success, 0 overwise
 */
int shoot_360_direction(Game *game, Entity *entity);

#endif