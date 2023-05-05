/**
 * @file entity.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to manage the logic of an entity
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ENTITY_H
#define ENTITY_H
/**
 * @brief Update the entity data
 * 
 * @param game of the entity
 * @param entity to update
 * @return 1 if the entity were removed, 0 otherwise
 */
int update_entity(Game* game, Entity *entity);

/**
 * @brief Free the entity memory
 * 
 * @param game of the entity
 * @param entity to free
 */
void free_entity(Game* game, Entity *entity);

/**
 * @brief Create a entity object
 * 
 * @param x position of the entity
 * @param y position of the entity
 * @param width of the entity
 * @param height of the entity
 * @param speed of the entity
 * @param update_speed movement function pointer of the entity
 * @param animation structure of the entity
 * @param destruction_img_path path of the destruction image
 * @param parent of the entity
 * @param type of the entity
 * @return The created entity pointer
 */
Entity* create_entity(int x, int y, int width, int height, 
                      int speed, SPEED_FUNC update_speed,
                      Animation* animation,
                      char* destruction_img_path,
                      void* parent, EntityType type
                    );

/**
  * @brief The entity can't go out of the screen
  * 
  * @param entity to avoid the border
  */
void avoid_collide_border(Entity *entity);

/**
 * @brief Get the direction of the entity
 * 
 * @param entity to get the direction
 * @return The direction
 */
Direction get_direction(Entity *entity);

/**
 * @brief Get the direction of an entity compared to another
 * 
 * @param entity to get the direction
 * @param other entity to compare
 * @return The direction
 */
Direction get_entity_collide(Entity* entity, Entity* other);

/**
 * @brief Called when an entity is collided by another entity
 * 
 * @param game of the entity
 * @param entity collided
 * @param other entity collided
 * @param direction of the collision
 * @return 1 if an entity were removed during collision, 0 otherwise
 */
int on_entity_collide(Game* game, Entity* entity, Entity* other, Direction direction);

/**
 * @brief Get the closest entity of an entity
 * 
 * @param game of the entity
 * @param entity to get the closest
 * @param filter type of the entity to found
 * @return The closest entity pointer, NULL if not found
 */
Entity* closest_entity(Game *game, Entity *entity, EntityType filter);

/**
 * @brief Add a child to an entity
 * 
 * @param parent of the entity
 * @param child to add
 */
void add_child(Entity* parent, Entity* child);

/**
 * @brief Remove a child from an entity
 * 
 * @param game of the entity
 * @param parent of the entity
 * @param child to remove
 */
void remove_child(Game* game, Entity* parent, Entity* child);

#endif