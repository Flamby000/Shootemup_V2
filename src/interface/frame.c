#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/interface/animation.h"
#include "../../include/logic/game.h"
#include "../../include/interface/frame.h"

void init_frame() {    
    MLV_create_window(GAME_NAME, GAME_NAME, settings->win_width, settings->win_height   );
    printf("%d\n", settings->win_width/15);
    settings->small_font = MLV_load_font(FONT_PATH, settings->win_width/60);
    settings->medium_font = MLV_load_font(FONT_PATH, settings->win_width/42);
    settings->big_font = MLV_load_font(FONT_PATH, settings->win_width/42);
    settings->huge_font = MLV_load_font(FONT_PATH, settings->win_width/25);   
}

void draw_frame(Game* game) {
    EntityLink* current = game->entities;
    Entity *entity;
    while(current != NULL) {
        entity = current->entity;
        if(entity->type == PLAYER) {
            draw_player(game, (Player*)entity->parent);
        } else draw_entity(game, entity, NULL);
        
        current = current->next;
    }
}

void free_frame() {
    MLV_free_font(settings->small_font);
    MLV_free_font(settings->medium_font);
    MLV_free_font(settings->big_font);
    MLV_free_font(settings->huge_font);
    MLV_free_window();
}

void draw_ennemy(Game *game, Ennemy *ennemy) {
    Entity *entity = ennemy->entity;
    Life *life = &ennemy->ship->life;
    if(life->max_hp <= 1) return;
    draw_bar(
        entity->x , entity->y - entity->height/10, 
        entity->width, entity->height/10, 
        life->hp, life->max_hp, 
        MLV_COLOR_RED
    );
}

void draw_player(Game *game, Player* player) {
    /*
    int bar_height = 100;
    int bar_width = 30;
    int bar_margin = 10;
    int bar_count = 0;
    */
    int win_width = settings->win_width;
    int win_height = settings->win_height;
    char buffer[255];
    int text_width, text_height;
    int bar_width = win_width/10;
    int bar_height = win_height/20;
    int bar_espace = bar_height/2;
    int left_margin = player->player_number == 1 ? 10 : win_width - bar_width - 10;

    int current_bar_x, current_bar_y;


    /* Health bar */
    current_bar_x = left_margin;
    current_bar_y = win_height - bar_height  - bar_espace;    
    draw_bar(
        current_bar_x, current_bar_y, 
        bar_width, bar_height, 
        (&player->ship->life)->hp, (&player->ship->life)->max_hp, 
        MLV_COLOR_RED
    );
    MLV_get_size_of_text("Health", &text_width, &text_height);
    MLV_draw_text_with_font(current_bar_x - 10, current_bar_y - text_height, "Health", settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);

    
    /* Cooldown bar */
    current_bar_y -= bar_height + bar_espace;
    draw_bar(
        current_bar_x, current_bar_y, 
        bar_width, bar_height, 
        MLV_get_time() - (&player->ship->shooter)->last_shoot_time, (&player->ship->shooter)->cooldown, 
        MLV_COLOR_GREEN
    );
    MLV_get_size_of_text("Cooldown", &text_width, &text_height);
    MLV_draw_text_with_font(current_bar_x -10 , current_bar_y - text_height, "Cooldown", settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);
    
    /* Cooldown bar */
    current_bar_y -= bar_height + bar_espace;
    draw_bar(
        current_bar_x, current_bar_y, 
        bar_width, bar_height, 
        MLV_get_time() - (&player->ship->super_shooter)->last_shoot_time, (&player->ship->super_shooter)->cooldown, 
        MLV_COLOR_BLUE
    );
    MLV_get_size_of_text("Super Cooldown", &text_width, &text_height);
    MLV_draw_text_with_font(current_bar_x - 10, current_bar_y - text_height, "Super Cooldown", settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);
    
    /*Stamina bar */
    current_bar_y -= bar_height + bar_espace;
    draw_bar(
        current_bar_x, current_bar_y, 
        bar_width, bar_height, 
        (&player->ship->boost)->energy, (&player->ship->boost)->max_energy, 
        MLV_COLOR_YELLOW
    );
    MLV_get_size_of_text("Stamina", &text_width, &text_height);
    MLV_draw_text_with_font(current_bar_x - 10, current_bar_y - text_height, "Stamina", settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);


    /* Draw score 
    player->score
    */
    current_bar_y -= bar_height + bar_espace;
    sprintf(buffer, "Score : %d", player->score);
    MLV_get_size_of_text(buffer, &text_width, &text_height);
    MLV_draw_text_with_font(current_bar_x , current_bar_y - text_height, buffer, settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);

    /* Invincibility frame */
    if(MLV_get_time() - (&player->ship->life)->last_damage_time < (&player->ship->life)->invincibility_duration) {
        if(MLV_get_time() % 500 < 250) draw_entity(game, player->entity, NULL);
    } else draw_entity(game, player->entity, NULL);



}


void draw_bar(int x, int y, int width, int height, int value, int max_value, MLV_Color color) {
    int bar_width = width;
    int bar_height = height;


    if(value >= max_value) value = max_value;
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

    /* Draw text in the top part of the bar*/
    /*
    if(display_value) {
        sprintf(text, "%d", value);
        MLV_get_size_of_text(text, &text_width, &text_height);
        MLV_draw_text_with_font(x + width/2 - text_width/1.5, y, text, settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);
    }

    MLV_get_size_of_text(name, &text_width, &text_height);
    MLV_draw_text_with_font(x + width/2 - text_width/1.5, y - text_height*1.5, name, settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);
    */
    
    MLV_draw_rectangle(x, y, width, height, MLV_COLOR_BLACK);
}