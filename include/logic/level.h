/**
 * @file level.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to manage the logic of a level
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef LEVEL_H
#define LEVEL_H

/**
 * @brief Create a level from a file
 * 
 * @param level_file path
 * @return A pointer to the level defined on the file
 */
Level* create_level(char* level_file);

/**
 * @brief Called each frame to update the level on the game. It spawn the waves and the boss missiles
 * 
 * @param game of the level
 * @param level to update
 * @param infinite 1 if the level is infinite, 0 otherwise
 * @return 1 if the level is over, 0 otherwise
 */
int update_level(Game* game, Level* level, int infinite);

/**
 * @brief Free the memory allocated for the level
 * 
 * @param level to free
 */
void free_level(Level* level);

/**
 * @brief Create a wave from a string. Each characters correspond to an entity (ennemy or bonus)
 * 
 * @param game of the wave
 * @param object_line string with the wave elements
 */
void create_object_line(Game *game, char* object_line);

/**
 * @brief Get the entity type from a character (its id)
 * 
 * @param object id
 * @return EntityType of the object 
 */
EntityType get_object_type(char object);


void set_level(Game* game, char* level_file);
int get_high_score(int level_number);
void set_high_score(int level_number, int score);
int get_ennemy_count(int level_number);
Animation* get_boss_animation(int level_number);
#endif