#ifndef ENNEMY_H
#define ENNEMY_H

/**
 * @brief The path to the ennemy data file
 * 
 */
#define ENNEMY_DATA_PATH "data/ennemies.data"

#define BASIC_ENNEMY '1'
#define TIER2_ENNEMY '2'
#define TIER3_ENNEMY '3'

/**
 * @brief Create an ennemy object
 * 
 * @param game to create the ennemy
 * @param type of ennemy
 * @param x position of the spawning ennemy point
 * @return The created ennemy pointer
 */
Ennemy* create_ennemy(Game *game, char type, int x);

/**
 * @brief Free the ennemy memory
 * 
 * @param game of the ennemy
 * @param ennemy to free
 */
void free_ennemy(Game* game, Ennemy *ennemy);

/**
 * @brief Free the ennemy if it is out of the screen
 * 
 * @param game of the ennemy
 * @param entity to free
 * @return 1 if the entity were removed, 0 otherwise
 */
int free_out_of_screen(Game *game, Entity *entity);

/**
 * @brief Called when an ennemy is collided by another entity
 * 
 * @param game of the ennemy
 * @param ennemy collided
 * @param collide with the ennemy
 * @param direction of the collision
 * @return 1 if an entity were removed during collision, 0 otherwise
 */
int on_collide_ennemy(Game *game, Ennemy *ennemy, Entity *collide, Direction direction);

/**
 * @brief Create a shoot pattern from the entity
 * 
 * @param game of the entity
 * @param entity to create the shoot pattern
 * @param shootline to create 
 */
void create_shoot_line(Game* game, Entity *entity, char* shootline);

#endif