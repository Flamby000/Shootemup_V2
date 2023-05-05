#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/interface/animation.h"
#include "../../include/logic/game.h"
#include "../../include/logic/spaceship.h"
#include "../../include/logic/entity.h"
#include "../../include/utils/shooter.h"
#include "../../include/utils/movement.h"
#include "../../include/logic/player.h"

/*
typedef struct _Player {
    struct _Entity* entity;
    struct _SpaceShip* ship;
    int score;
    int boss_kill_count;
    int player_number;

    MLV_Keyboard_button key_left;
    MLV_Keyboard_button key_right;
    MLV_Keyboard_button key_up;
    MLV_Keyboard_button key_down;
    MLV_Keyboard_button key_shoot;
    MLV_Keyboard_button key_super_shoot;
    MLV_Keyboard_button key_boost;
} Player;
*/

Player* create_player(Game *game, int player_number) {
    Player* player = malloc(sizeof(Player));
    int x = settings->win_width / 2 - PLAYER_WIDTH / 2;

    if(settings->coop_mode) {
        if(player_number == 1) x -= 20;
        else x += 20;
    }

    player->key_left = player_number == 1 ? MLV_KEYBOARD_q : MLV_KEYBOARD_LEFT;
    player->key_right = player_number == 1 ? MLV_KEYBOARD_d : MLV_KEYBOARD_RIGHT;
    player->key_up = player_number == 1 ? MLV_KEYBOARD_z : MLV_KEYBOARD_UP;
    player->key_down = player_number == 1 ? MLV_KEYBOARD_s : MLV_KEYBOARD_DOWN;
    player->key_shoot = player_number == 1 ? MLV_KEYBOARD_e : MLV_KEYBOARD_SPACE;
    player->key_super_shoot = player_number == 1 ? MLV_KEYBOARD_a : MLV_KEYBOARD_KP_ENTER;
    player->key_boost = player_number == 1 ? MLV_KEYBOARD_LSHIFT : MLV_KEYBOARD_EXCLAIM;
    
    player->score = 0;
    player->entity = create_entity(
        x, 
        settings->win_height - PLAYER_HEIGHT * 2, 
        PLAYER_WIDTH, 
        PLAYER_HEIGHT,
        settings->difficulty->player_speed, user_movement_controller,  
        init_multiple_animation(
            "resources/player/forward-%d.png", 
            "resources/player/backward-%d.png", 
            "resources/player/left-%d.png", 
            "resources/player/right-%d.png"), EXPLOSION_1,
        player, PLAYER
    );
    insert_entity(game, player->entity);
    player->ship = create_spaceship(settings->difficulty->player_life, settings->difficulty->player_shoot_cooldown, settings->difficulty->player_super_shoot_cooldown, shoot_player_basic, shoot_super_laser);
    player->boss_kill_count = 0;
    player->player_number = player_number;
    return player;
}

int on_collide_player(Game *game, Player *player, Entity *collide, Direction direction) {

    return 0;
}

void free_player(Game* game, Player* player) {
    free_spaceship(game, player->ship);
    free(player);
}