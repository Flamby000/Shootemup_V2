#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * @brief The settings file path
 * 
 */
#define SETTINGS_DATA_PATH "data/settings.data"

/**
 * @brief The game phases
 * 
 */
typedef enum _GamePhase {
    MATCH_PHASE,
    MAIN_MENU_PHASE
} GamePhase;

/**
 * @brief Load the game settings
 * 
 */
void load_settings();


/**
 * @brief free the game settings
 * 
 */
void free_settings();


/**
 * @brief Save the game settings
 * 
 */
void save_settings();
#endif