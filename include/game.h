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
 * @param win if the player won the match 
 */
void end_match(Game* game, int win);

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

#endif