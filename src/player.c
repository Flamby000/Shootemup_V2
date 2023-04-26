#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/spaceship.h"
#include "../include/entity.h"
#include "../include/player.h"
#include "../include/shooter.h"
#include "../include/movement.h"

Player* create_player(Game *game) {
    Player* player = malloc(sizeof(Player));
    player->score = 0;
    player->entity = create_entity(
        settings->win_width / 2 - PLAYER_WIDTH / 2, 
        settings->win_height - PLAYER_HEIGHT * 2, 
        PLAYER_WIDTH, 
        PLAYER_HEIGHT,
        5, movement_controller,  
        init_multiple_animation(
            "resources/player/forward-%d.png", 
            "resources/player/backward-%d.png", 
            "resources/player/left-%d.png", 
            "resources/player/right-%d.png"), EXPLOSION_1,
        player, PLAYER
    );
    insert_entity(game, player->entity);
    player->ship = create_spaceship(5, 500, 2000, shoot_player_basic, shoot_super_laser);

    return player;
}

int on_collide_player(Game *game, Player *player, Entity *collide, Direction direction) {

    return 0;
}

void free_player(Game* game, Player* player) {
    free_spaceship(game, player->ship);
    free(player);
}