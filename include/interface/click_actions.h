#ifndef CLICK_ACTIONS_H
#define CLICK_ACTIONS_H

int go_main_menu(Game* game, Button* button);
int restart_match_action(Game* game, Button* button);
int resume_match_action(Game* game, Button* button);
int open_campaign_map(Game* game, Button* button);
int start_infinite_game(Game* game, Button* button);
int open_settings(Game* game, Button* button);
int open_garage(Game* game, Button* button);
int open_tutorial(Game* game, Button* button);
int open_credits(Game* game, Button* button);
int quit_game(Game* game, Button* button);
int toggle_coop_mode(Game* game, Button* button);
int set_difficulty_easy(Game* game, Button* button);
int set_difficulty_medium(Game* game, Button* button);
int set_difficulty_hard(Game* game, Button* button);
int set_difficulty_custom(Game* game, Button* button);
int set_volume(Game *game, Button *button);
int decrease_player_life(Game *game, Button *button);
int increase_player_life(Game *game, Button *button);
int set_player_cooldown(Game *game, Button *button);
int set_player_super_shoot_cooldown(Game *game, Button *button);
int increase_player_speed(Game *game, Button *button);
int decrease_player_speed(Game *game, Button *button);
int set_player_stamina(Game *game, Button *button);
int set_waves_spawn_cooldown(Game *game, Button *button);
int decrease_ennemy_life_multiplicator(Game *game, Button *button);
int increase_ennemy_life_multiplicator(Game *game, Button *button);
int increase_ennemy_shoot_cooldown_multiplicator(Game *game, Button *button);
int decrease_ennemy_shoot_cooldown_multiplicator(Game *game, Button *button);
int increase_ennemy_speed_multiplicator(Game *game, Button *button);
int decrease_ennemy_speed_multiplicator(Game *game, Button *button);
int save_settings_action(Game *game, Button *button);
#endif