/**
 * @file bonus.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to manage the logic of a bonus
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef BONUS_H
#define BONUS_H

/**
 * @brief The path of the bonus data file
 * 
 */
#define BONUS_DATA_PATH "data/bonus.data"

/**
 * @brief Create a bonus object
 * 
 * @param game to create the bonus
 * @param type of bonus
 * @param x position of the spawning bonus point
 * @return The created bonus pointer
 */
Bonus *create_bonus(Game *game, char type, int x);

/**
 * @brief Free the bonus memory
 * 
 * @param bonus to free
 */
void free_bonus(Bonus *bonus);

/**
 * @brief Get the bonus effect function by the bonus type ID
 * 
 * @param id of the bonus type
 * @return A pointer to the bonus effect function
 */
BONUS_FUNC get_bonus_effect_by_id(char id);


/**
 * @brief Function called when a bonus collide another entity
 * 
 * @param game of the bonus
 * @param bonus collided
 * @param collide with the bonus
 * @param direction of the collision
 * @return 1 if an entity were removed during collision, 0 otherwise
 */
int on_collide_bonus(Game *game, Bonus *bonus, Entity *collide, Direction direction);

/**
 * @brief Check if a bonus can be reached by a player
 * 
 * @param game of the bonus
 * @param bonus to check
 * @return 1 if the bonus can be reached, 0 otherwise
 */
int is_bonus_reachable(Game *game, Bonus *bonus);

/**
 * @brief List of possible bonus types spawned by the 'RANDOM_BONUS' id
 * 
 */
#define RANDOM_BONUSES "SPHVMUL"

/**
 * @brief Identify the random bonus type
 * 
 */
#define RANDOM_BONUS 'R'
/**
 * @brief Create a random bonus object
 * 
 * @param game to create the bonus
 * @param x position of the spawning bonus point
 * @return The created bonus pointer
 */
Bonus *create_random_bonus(Game *game, int x);

/**
 * @brief Identify the shield bonus type
 * 
 */
#define SHIELD_EFFECT 'S'
/**
 * @brief Apply the shield effect to a player
 * 
 * @param game of the bonus
 * @param eater of the bonus
 * @param reverse if the effect is reversed
 */
void shield_effect(Game *game, Player* eater, int reverse);

/**
 * @brief Identify the life increase bonus type
 * 
 */
#define LIFE_INCREASE_EFFECT 'H'

/**
 * @brief Apply the life increase effect to a player
 * 
 * @param game of the bonus
 * @param eater of the bonus
 * @param reverse if the effect is reversed
 */
void life_increase_effect(Game *game, Player* eater, int reverse);

/**
 * @brief Identify the life decrease bonus type
 * 
 */
#define LIFE_DECREASE_EFFECT 'L'
/**
 * @brief Apply the life decrease effect to a player
 * 
 * @param game of the bonus
 * @param eater of the bonus
 * @param reverse if the effect is reversed
 */
void life_decrease_effect(Game *game, Player* eater, int reverse);

/**
 * @brief Identify the max life increase bonus type
 * 
 */
#define MAX_LIFE_INCREASE_EFFECT 'M'
/**
 * @brief Increase the max life effect to the eater
 * 
 * @param game of the bonus
 * @param eater of the bonus
 * @param reverse if the effect is reversed
 */
void max_life_increase_effect(Game *game, Player* eater, int reverse);

/**
 * @brief Identify the power up shoot bonus type
 * 
 */
#define POWER_UP_SHOOT_EFFECT 'P'
/**
 * @brief Increase the power of the eater shoot
 * 
 * @param game of the bonus
 * @param eater of the bonus
 * @param reverse if the effect is reversed
 */
void power_up_shoot_effect(Game *game, Player* eater, int reverse);

/**
 * @brief Identify the power up speed bonus type
 * 
 */
#define POWER_UP_SPEED_EFFECT 'V'

/**
 * @brief Increase the speed of the eater
 * 
 * @param game of the bonus
 * @param eater of the bonus
 * @param reverse if the effect is reversed
 */
void power_up_speed_effect(Game *game, Player* eater, int reverse);

/**
 * @brief Identify a spawn unit bonus type
 * 
 */
#define SPAWN_UNIT_EFFECT 'U'

/**
 * @brief Spawn a unit to protect the eater
 * 
 * @param game of the bonus
 * @param eater of the bonus
 * @param reverse if the effect is reversed
 */
void spawn_unit_effect(Game *game, Player* eater, int reverse);

#endif