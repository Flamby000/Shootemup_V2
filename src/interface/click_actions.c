#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/logic/game.h"
#include "../../include/settings.h"
#include "../../include/utils/background.h"
#include "../../include/interface/menu.h"
#include "../../include/interface/click_actions.h"

int go_main_menu(Game* game, Button* button) {
    EntityLink* current, *next;
    Menu main_menu = create_main_menu(game, MAIN_MENU);
    set_background_speed(game, 0.5);

    for(current = game->entities; current != NULL; current = next) {
        next = current->next;
        if(is_match_entity(current->entity)) {
            remove_entity(game, current->entity, 0);
        }
    }

    set_menu(game, &main_menu);
    return 1;
}

int restart_match_action(Game* game, Button* button) {
    start_match(game, game->level->level_file);
    return 1;
}

int resume_match_action(Game* game, Button* button) {
    pause_match(game);
    return 1;
}

int open_campaign_map(Game* game, Button* button) {
    Menu campaign_menu = create_main_menu(game, CAMPAIGN_MENU);
    set_menu(game, &campaign_menu);

    settings->infinite_mode = 0;    

    return 1;
}

int start_infinite_game(Game* game, Button* button) {
    settings->infinite_mode = 1;    
    start_match(game, "data/level/level-3.lvl");
    return 1;
}

int open_settings(Game* game, Button* button) {
    Menu settings_menu = create_main_menu(game, SETTINGS_MENU);
    set_menu(game, &settings_menu);

    return 1;
}


int open_garage(Game* game, Button* button) {
    Menu garage_menu = create_main_menu(game, GARAGE_MENU);
    set_menu(game, &garage_menu);

    return 1;
}

int open_tutorial(Game* game, Button* button) {
    Menu tutorial_menu = create_main_menu(game, TUTORIAL_MENU);
    set_menu(game, &tutorial_menu);

    return 1;
}

int open_credits(Game* game, Button* button) {
    Menu credits_menu = create_main_menu(game, CREDITS_MENU);
    set_menu(game, &credits_menu);
    return 1;
}

int quit_game(Game* game, Button* button) {
    
    return 1;
}

void update_setting_menu(Game *game) {
    Menu settings_menu;
    settings_menu = create_main_menu(game, SETTINGS_MENU);
    set_menu(game, &settings_menu);
}

int toggle_coop_mode(Game* game, Button* button) {

    settings->coop_mode = !settings->coop_mode;

    update_setting_menu(game);


    return 1;
}

int set_difficulty_easy(Game* game, Button* button) {
    settings->difficulty->preset = EASY;

    settings->difficulty->waves_spawn_cooldown = 3000;
    settings->difficulty->ennemy_life_multiplicator = 1;
    settings->difficulty->ennemy_shoot_cooldown_multiplicator = 2;
    settings->difficulty->ennemy_speed_multiplicator = 1;
    settings->difficulty->player_life = 5;
    settings->difficulty->player_shoot_cooldown = 250;
    settings->difficulty->player_super_shoot_cooldown = 2500;
    settings->difficulty->player_speed = 7;
    settings->difficulty->player_stamina = 300;


    update_setting_menu(game);
    return 1;
}


int set_difficulty_medium(Game* game, Button* button) {
    settings->difficulty->preset = MEDIUM;


    settings->difficulty->waves_spawn_cooldown = 2500;
    settings->difficulty->ennemy_life_multiplicator = 1;
    settings->difficulty->ennemy_shoot_cooldown_multiplicator = 1;
    settings->difficulty->ennemy_speed_multiplicator = 1;
    settings->difficulty->player_life = 3;
    settings->difficulty->player_shoot_cooldown = 500;
    settings->difficulty->player_super_shoot_cooldown = 5000;
    settings->difficulty->player_speed = 5;
    settings->difficulty->player_stamina = 200;



    update_setting_menu(game);
    return 1;
}

int set_difficulty_hard(Game* game, Button* button) {
    settings->difficulty->preset = HARD;

    settings->difficulty->waves_spawn_cooldown = 2000;
    settings->difficulty->ennemy_life_multiplicator = 2;
    settings->difficulty->ennemy_shoot_cooldown_multiplicator = 1;
    settings->difficulty->ennemy_speed_multiplicator = 2;
    settings->difficulty->player_life = 2;
    settings->difficulty->player_shoot_cooldown = 750;
    settings->difficulty->player_super_shoot_cooldown = 10000;
    settings->difficulty->player_speed = 4;
    settings->difficulty->player_stamina = 100;

    update_setting_menu(game);
    
    return 1;
}

int set_difficulty_custom(Game* game, Button* button) {
    settings->difficulty->preset = CUSTOM;
    update_setting_menu(game);
    return 1;
}

int set_volume(Game *game, Button *button) {
    MLV_Music *music;
    MLV_stop_music();
    music = MLV_load_music("resources/sound/music.mp3");

    settings->volume = button->value;

    MLV_play_music(music, settings->volume*0.01, -1);

    update_setting_menu(game);
    return 1;
}

int decrease_player_life(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->player_life > 1) {
        settings->difficulty->player_life--;
    }
    update_setting_menu(game);

    return 1;
}
int increase_player_life(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->player_life < 10) {
        settings->difficulty->player_life++;
    }
    update_setting_menu(game);

    return 1;
}

int set_player_cooldown(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    settings->difficulty->player_shoot_cooldown = button->value;
    update_setting_menu(game);
    return 1;
}

int set_player_super_shoot_cooldown(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    settings->difficulty->player_super_shoot_cooldown = button->value;
    update_setting_menu(game);
    return 1;
}

int increase_player_speed(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->player_speed < 10) {
        settings->difficulty->player_speed++;
    }
    update_setting_menu(game);

    return 1;
}
int decrease_player_speed(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->player_speed > 3) {
        settings->difficulty->player_speed--;
    }
    update_setting_menu(game);

    return 1;
}

int set_player_stamina(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    settings->difficulty->player_stamina = button->value;
    update_setting_menu(game);
    return 1;
}

int set_waves_spawn_cooldown(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    settings->difficulty->waves_spawn_cooldown = button->value;
    update_setting_menu(game);
    return 1;
}

int decrease_ennemy_life_multiplicator(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->ennemy_life_multiplicator > 1) {
        settings->difficulty->ennemy_life_multiplicator--;
    }
    update_setting_menu(game);
    return 1;
}

int increase_ennemy_life_multiplicator(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->ennemy_life_multiplicator < 4) {
        settings->difficulty->ennemy_life_multiplicator++;
    }
    update_setting_menu(game);
    return 1;
}

int increase_ennemy_shoot_cooldown_multiplicator(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->ennemy_shoot_cooldown_multiplicator < 4) {
        settings->difficulty->ennemy_shoot_cooldown_multiplicator++;
    }
    update_setting_menu(game);
    return 1;
}

int decrease_ennemy_shoot_cooldown_multiplicator(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->ennemy_shoot_cooldown_multiplicator > 1) {
        settings->difficulty->ennemy_shoot_cooldown_multiplicator--;
    }
    update_setting_menu(game);
    return 1;
}

int increase_ennemy_speed_multiplicator(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->ennemy_speed_multiplicator < 4) {
        settings->difficulty->ennemy_speed_multiplicator++;
    }
    update_setting_menu(game);
    return 1;
}

int decrease_ennemy_speed_multiplicator(Game *game, Button *button) {
    settings->difficulty->preset = CUSTOM;
    if(settings->difficulty->ennemy_speed_multiplicator > 1) {
        settings->difficulty->ennemy_speed_multiplicator--;
    }
    update_setting_menu(game);
    return 1;
}

int save_settings_action(Game *game, Button *button) {
    save_settings();
    go_main_menu(game, button);
    return 1;
}