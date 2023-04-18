#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/frame.h"


void init_frame() {
    MLV_create_window(GAME_NAME, GAME_NAME, WIN_WIDTH, WIN_HEIGHT);
}

void update_frame(Game* game) {
    EntityLink* current = game->entities;
    MLV_clear_window(MLV_COLOR_BLACK);


    while (current != NULL) {
        draw_entity(current->entity);
        current = current->next;
    }


    MLV_wait_milliseconds(12);

    MLV_actualise_window();
}

void free_frame() {
    MLV_free_window();
}