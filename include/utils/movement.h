/**
 * @file movement.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to update the movement and speed of an entity
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H

/**
 * @brief Get the movement function pointer from its ID
 * 
 * @param id of the movement function
 * @return a SPEED_FUNCTION pointer defining a movement pattern
 */
SPEED_FUNC get_movement_function(int id);

/**
 * @brief ID of the function movement_none
 * 
 */
#define MOVEMENT_NONE 0

/**
 * @brief Correspond to no movement
 * 
 * @param game of the entity to update speed
 * @param entity to update speed
 */
void movement_none(Game* game, Entity *entity);

/**
 * @brief ID of the function movement_forward
 * 
 */
#define MOVEMENT_FORWARD 1

/**
 * @brief Correspond to a movement forward. The entity will move forward.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_forward(Game* game, Entity *entity);

/**
 * @brief ID of the function movement_backward
 * 
 */
#define MOVEMENT_BACKWARD 2

/**
 * @brief Correspond to a movement backward. The entity will move backward.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_backward(Game *game, Entity *entity);

/**
 * @brief ID of the function movement_infinite_scroll
 * 
 */
#define MOVEMENT_INFINITE_SCROLL 3

/**
 * @brief Correspond to a movement infinite scroll. When the entity is out of screen, it appears at the top of the screen.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_infinite_scroll(Game* game, Entity *entity);

/**
 * @brief ID of the function movement_controller
 * 
 */
#define MOVEMENT_CONTROLLER 4

/**
 * @brief Correspond to a movement controlled by the player. The entity will move according to the player inputs.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void user_movement_controller(Game *game, Entity *entity);

/**
 * @brief ID of the function movement_follow_player
 * 
 */
#define MOVEMENT_FOLLOW_PLAYER 5

/**
 * @brief Correspond to a movement following the player. The entity will follow the player.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_follow_player(Game* game, Entity *entity);

/**
 * @brief ID of the function movement_sinusoidal
 * 
 */
#define MOVEMENT_SINUSOIDAL 6

/**
 * @brief Correspond to a movement sinusoidal. The entity will move in a sinusoidal pattern.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_sinusoidal(Game* game, Entity *entity);

/**
 * @brief ID of the function movement_circle_entity
 * 
 */
#define MOVEMENT_CIRCLE_ENTITY 7

/**
 * @brief Correspond to a movement circling an entity. The entity will circle around another entity.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_circle_entity(Game *game, Entity *entity);

/**
 * @brief ID of the function movement_follow_x
 * 
 */
#define MOVEMENT_FOLLOW_X 8

/**
 * @brief Correspond to a movement following the player on its X axis. 
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_follow_x(Game *game, Entity *entity);

/**
 * @brief ID of the function movement_left_right
 * 
 */
#define MOVEMENT_LEFT_RIGHT 9

/**
 * @brief Correspond to a movement left and right. The entity will bounce on the left and right borders of the screen.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_left_right(Game *game, Entity *entity);

/**
 * @brief ID of the function movement_follow_ennemy
 * 
 */
#define MOVEMENT_FOLLOW_ENNEMY 10

/**
 * @brief Correspond to a movement following an ennemy. The entity will follow an ennemy.
 * 
 * @param game of the entity
 * @param entity to update speed
 */
void movement_follow_ennemy(Game *game, Entity *entity);

/**
 * @brief Push the entity on the bottom.
 * 
 * @param game of the entity to push
 * @param entity to push
 */
void push_entity(Game *game, Entity *entity);

/**
 * @brief The entity will follow the target
 * 
 * @param game of the entities
 * @param entity to move
 * @param target to follow
 */
void movement_follow_entity(Game *game, Entity *entity, Entity *target);

/**
 * @brief The entity will move in a circle pattern
*/
void movement_circle_button(Game *game, Entity *entity);

#endif