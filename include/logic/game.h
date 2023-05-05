/**
 * @file game.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to manage the logic of the game
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GAME_H
#define GAME_H

/**
 * @brief The name of the game
 * 
 */
#define GAME_NAME "Space Crusade"

/**
 * @brief Initialize the game
 * 
 * @return The game structure pointer
 */
Game* init_game();

/**
 * @brief Update the game data
 * 
 * @param game to update
 */
void update_game(Game *game);

/**
 * @brief Free the game memory
 * 
 * @param game to free
 */
void free_game(Game* game);


/**
 * @brief End a space crusader match of the game
 * 
 * @param game to end the match
 * @param status new status of the match
 */
void end_match(Game* game, MatchStatus status);

/**
 * @brief Insert an entity into the game
 * 
 * @param game to insert the entity
 * @param entity to insert
 */
void insert_entity(Game* game, struct _Entity* entity);

/**
 * @brief Remove an entity from the game
 * 
 * @param game to remove the entity
 * @param entity to remove
 * @param explose if the entity explose when it is removed
 */
void remove_entity(Game* game, struct _Entity* entity, int explose);

/**
 * @brief Get the entity id object
 * 
 * @param game of the entity
 * @param entity to get the id
 * @return the id of the entity or NULL if the entity is not in the game
 */
int get_entity_id(Game* game, Entity* entity);

/**
 * @brief Get the number of alive ennemies in the game
 * 
 * @param game to count the ennemies
 * @return the number of alive ennemies
 */
int remaining_ennemies(Game* game);

/**
 * @brief Get the number of remaning players
 * 
 * @param game to count the players
 * @return the number of remaining players
 */
int remaining_players(Game* game);


/**
 * @brief Get the number of bosses killed by players in a game
 * 
 * @param game to count the bosses
 * @return the number of bosses killed
 */
int boss_kill_count(Game* game);

/**
 * @brief Get if a boss is currently alive in the game
 * 
 * @param game to check if a boss is alive
 * @return 1 if a boss is alive, 0 otherwise
 */
int is_boss_alive(Game* game);


/**
 * @brief Start a match of the game
 * 
 * @param game to start the match
 * @param level_file to load the level
 */
void start_match(Game* game, char* level_file);

/**
 * @brief Remove all entities of specified type
 * 
 * @param game to remove the entities
 * @param type of the entities to remove
 */
void remove_entities_by_type(Game* game, EntityType type);

/**
 * @brief See if an entity is a match entity
 * 
 * @param entity to check
 * @return 1 if the entity is a match entity, 0 otherwise
 */
int is_match_entity(Entity *entity);


/**
 * @brief Pause or resume a match
 * 
 * @param game to pause or resume 
 */
void pause_match(Game* game);


/**
 * @brief Calculate the score of every players
 * 
 * @param game to calculate the score
 * @return the score of every players
 */
int get_score(Game* game);



#endif