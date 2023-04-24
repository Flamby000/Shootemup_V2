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

void draw_frame(Game* game) {
    EntityLink* current = game->entities;
    Entity *entity;
    while(current != NULL) {
        entity = current->entity;
        if(entity->type == PLAYER) {
            draw_player(game, (Player*)entity->parent);
        } else draw_entity(entity);
        
        current = current->next;
    }
}

void free_frame() {
    MLV_free_window();
}
void draw_player(Game *game, Player* player) {
    int bar_height = 100;
    int bar_width = 30;
    int bar_margin = 10;
    int bar_count = 0;

    /* Health bar */
    draw_bar(
        settings->win_width/100 + ((bar_width*bar_count) + (bar_margin*bar_count)), settings->win_height - settings->win_height/100 - bar_height, 
        bar_width, bar_height, 
        (&player->ship->life)->hp, (&player->ship->life)->max_hp, 
        MLV_COLOR_RED
    );   
    bar_count++;
    
    /* Cooldown bar */
    draw_bar(
        settings->win_width/100 + ((bar_width*bar_count) + (bar_margin*bar_count)), settings->win_height - settings->win_height/100 - bar_height, 
        bar_width, bar_height, 
        MLV_get_time() - (&player->ship->shooter)->last_shoot_time, (&player->ship->shooter)->cooldown, 
        MLV_COLOR_GREEN
    );

    /* Invincibility frame */
    if(MLV_get_time() - (&player->ship->life)->last_damage_time < (&player->ship->life)->invincibility_duration) {
        if(MLV_get_time() % 500 < 250) draw_entity(player->entity);
    } else draw_entity(player->entity);

}

void draw_bar(int x, int y, int width, int height, int value, int max_value, MLV_Color color) {
    int bar_width = width;
    int bar_height = height;
    if(width > height) { 
        bar_width = (width * value) / max_value;
        if(bar_width > width) bar_width = width;
        MLV_draw_filled_rectangle(x, y, bar_width, height, color);
    }
    else {
        bar_height = (height * value) / max_value;
        if(bar_height > height) bar_height = height;
        MLV_draw_filled_rectangle(x, y + height - bar_height, width, bar_height, color);
    }

    MLV_draw_rectangle(x, y, width, height, MLV_COLOR_BLACK);

}