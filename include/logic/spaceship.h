/**
 * @file spaceship.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to manage the logic of a spaceship (player or ennemy)
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SPACESHIP_H
#define SPACESHIP_H

/**
 * @brief Create a spaceship object
 * 
 * @param life of the spaceship
 * @param shoot_cooldown of the basic spaceship shoot 
 * @param invincibility_duration of the spaceship when it is hit
 * @param update_shoot for basic spaceship shoot
 * @param update_super_shoot for super spaceship shoot
 * @return Pointer of the created spaceship
 */
SpaceShip* create_spaceship(int life, int shoot_cooldown, int invincibility_duration, SHOOT_FUNC update_shoot, SHOOT_FUNC update_super_shoot);

/**
 * @brief Free the spaceship allocated memory
 * 
 * @param game of the spaceship to free
 * @param spaceship to free
 */
void free_spaceship(Game* game, SpaceShip* spaceship);

/**
 * @brief Update the spaceship data
 * 
 * @param game of the entity
 * @param entity to update
 */
void update_spaceship(Game *game, Entity* entity);

/**
 * @brief Function to deals damage to a spaceship
 * 
 * @param game of the entity
 * @param entity to deals damage (player or ennemy)
 * @param damage to deals (it can be negative to heal the spaceship)
 * @return 1 if the entity was destroyed, 0 otherwise
 */
int deals_damage(Game *game, Entity *entity, int damage);

/**
 * @brief Function to enable the shield of a spaceship
 * 
 * @param game of the entity
 * @param entity to enable the shield (it have to be a player or an ennemy)
 * @return 1 if the shield was enabled, 0 otherwise
 */
int enable_shield(Game *game, Entity *entity);

/**
 * @brief Function to disable the shield of a spaceship
 * 
 * @param game of the entity
 * @param entity to disable the shield (it have to be a player or an ennemy)
 */
void disable_shield(Game *game, Entity *entity);

/**
 * @brief Get the life object from an entity
 * 
 * @param entity of the spaceship (it must be a player or an ennemy)
 * @return Life* of the spaceship
 */
Life* get_life(Entity *entity);

/**
 * @brief Add a bonus to a spaceship
 * 
 * @param game of the entity
 * @param entity spceship linked to the entity
 * @param bonus to apply on the spaceship
 */
void add_bonus(Game *game, Entity *entity, Bonus *bonus);

/**
 * @brief Remove a bonus from a spaceship
 * 
 * @param game of the entity
 * @param entity to remove the bonus
 * @param bonus to remove
 */
void remove_bonus(Game *game, Entity *entity, Bonus *bonus);

/**
 * @brief Free the bonuses of a spaceship
 * 
 * @param game of the entity
 * @param entity of the spaceship
 */
void free_bonuses(Game *game, Entity *entity);

/**
 * @brief Check if a spaceship have a bonus
 * 
 * @param entity to check
 * @param bonus_type to check
 * @return 1 if the spaceship have the bonus, 0 otherwise
 */
int have_bonus(Entity *entity, char bonus_type);

/**
 * @brief Count the number of bonus of a spaceship
 * 
 * @param entity to count the bonus
 * @return the number of bonus
 */
int count_bonus(Entity *entity);

/**
 * @brief Get the bonus pointer from a spaceship
 * 
 * @param entity to check
 * @param type of bonus to check
 * @return Return the bonus pointer or NULL if the spaceship don't have the bonus
 */
Bonus *get_bonus(Entity *entity, char type);

/**
 * @brief Remove a random bonus from a spaceship
 * 
 * @param game of the entity
 * @param entity of the spaceship
 * @return 1 if the bonus was removed, 0 otherwise
 */
int remove_random_bonus(Game* game, Entity *entity);

/**
 * @brief Get the spaceship object from an entity
 * 
 * @param entity of the spaceship (it must be a player or an ennemy)
 * @return Pointer of the spaceship
 */
SpaceShip* get_spaceship(Entity *entity);

/**
 * @brief Update the spaceship boost data
 * 
 * @param game of the entity
 * @param entity of the spaceship to update boost
 */
void update_boost(Game *game, Entity* entity);

#endif