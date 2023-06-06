/**
 * @file click_actions.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to handle click actions
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CLICK_ACTIONS_H
#define CLICK_ACTIONS_H

/**
 * @brief Go to the main menu
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int go_main_menu(Game* game, Button* button);

/**
 * @brief Restart a match
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int restart_match_action(Game* game, Button* button);

/**
 * @brief Resume a match
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int resume_match_action(Game* game, Button* button);

/**
 * @brief Open the campaign map
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int open_campaign_map(Game* game, Button* button);

/**
 * @brief Start an infinite match
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int start_infinite_game(Game* game, Button* button);

/**
 * @brief Open settings menu
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int open_settings(Game* game, Button* button);

/**
 * @brief Open garage menu
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int open_garage(Game* game, Button* button);

/**
 * @brief Open tutorial menu
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int open_tutorial(Game* game, Button* button);

/**
 * @brief Open credits menu
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int open_credits(Game* game, Button* button);

/**
 * @brief Quit the game
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int quit_game(Game* game, Button* button);

/**
 * @brief Toogle on or off the coop mode
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int toggle_coop_mode(Game* game, Button* button);

/**
 * @brief Set the difficulty to easy
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_difficulty_easy(Game* game, Button* button);

/**
 * @brief Set the difficulty to medium
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_difficulty_medium(Game* game, Button* button);

/**
 * @brief Set the difficulty to hard
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_difficulty_hard(Game* game, Button* button);

/**
 * @brief Set the difficulty to custom
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_difficulty_custom(Game* game, Button* button);

/**
 * @brief Set the volume of the game
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_volume(Game *game, Button *button);

/**
 * @brief Decrease the max player life in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int decrease_player_life(Game *game, Button *button);

/**
 * @brief Increase the max player life in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int increase_player_life(Game *game, Button *button);

/**
 * @brief Set the player shoot cooldown in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_player_cooldown(Game *game, Button *button);

/**
 * @brief Set the player super shoot cooldown in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_player_super_shoot_cooldown(Game *game, Button *button);

/**
 * @brief Increase the player speed in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int increase_player_speed(Game *game, Button *button);

/**
 * @brief Decrease the player speed in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int decrease_player_speed(Game *game, Button *button);

/**
 * @brief Set the player stamina in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_player_stamina(Game *game, Button *button);

/**
 * @brief Set the waves spawn cooldown in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int set_waves_spawn_cooldown(Game *game, Button *button);

/**
 * @brief Decrease the ennemy life multiplicator in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int decrease_ennemy_life_multiplicator(Game *game, Button *button);

/**
 * @brief Increase the ennemy life multiplicator in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int increase_ennemy_life_multiplicator(Game *game, Button *button);

/**
 * @brief Inecrease the ennemy shoot cooldown multiplicator in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int increase_ennemy_shoot_cooldown_multiplicator(Game *game, Button *button);

/**
 * @brief Decrease the ennemy shoot cooldown multiplicator in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int decrease_ennemy_shoot_cooldown_multiplicator(Game *game, Button *button);

/**
 * @brief Increase the ennemy speed multiplicator in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int increase_ennemy_speed_multiplicator(Game *game, Button *button);

/**
 * @brief Decrease the ennemy speed multiplicator in settings
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int decrease_ennemy_speed_multiplicator(Game *game, Button *button);

/**
 * @brief Save the settings in the file
 * 
 * @param game of the button
 * @param button clicked
 * @return 1
 */
int save_settings_action(Game *game, Button *button);

int set_selected_level(Game *game, Button *button);

#endif