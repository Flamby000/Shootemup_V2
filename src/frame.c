#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/frame.h"


void init_frame() {    
    MLV_create_window(GAME_NAME, GAME_NAME, settings->win_width, settings->win_height   );
}

void update_frame(Game* game) {
    EntityLink* current = game->entities;
    while(current != NULL) {
        draw_entity(current->entity);
        current = current->next;
    }
}

void free_frame() {
    MLV_free_window();
}