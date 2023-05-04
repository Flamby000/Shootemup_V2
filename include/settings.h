#ifndef SETTINGS_H
#define SETTINGS_H

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

#endif