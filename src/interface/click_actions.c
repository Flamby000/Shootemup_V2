#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/game.h"
#include "../../include/interface/menu.h"
#include "../../include/interface/click_actions.h"

int go_main_menu(Game* game, Button* button) {
    printf("go_main_menu\n");
    return 1;
}

int restart_match_action(Game* game, Button* button) {
    start_match(game, game->level->level_file);
    return 1;
}

int resume_match_action(Game* game, Button* button) {
    resume_match(game);
    return 1;
}