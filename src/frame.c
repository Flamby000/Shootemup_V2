#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/frame.h"

void init_frame() {    
    MLV_create_window(GAME_NAME, GAME_NAME, settings->win_width, settings->win_height   );
    settings->small_font = MLV_load_font(FONT_PATH, 15);        

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
        MLV_COLOR_RED, 0, "", 0, MLV_COLOR_PINK
    );
}

void draw_player(Game *game, Player* player) {
    int bar_height = 100;
    int bar_width = 30;
    int bar_margin = 10;
    int bar_count = 0;
    char buffer[255];
    int text_width, text_height;

    /* Health bar */
    draw_bar(
        settings->win_width/100 + ((bar_width*bar_count) + (bar_margin*bar_count)), settings->win_height - settings->win_height/100 - bar_height, 
        bar_width, bar_height, 
        (&player->ship->life)->hp, (&player->ship->life)->max_hp, 
        MLV_COLOR_RED, 1, "", 0, MLV_COLOR_PINK
    );   
    bar_count++;
    
    /* Cooldown bar */
    draw_bar(
        settings->win_width/100 + ((bar_width*bar_count) + (bar_margin*bar_count)), settings->win_height - settings->win_height/100 - bar_height, 
        bar_width, bar_height, 
        MLV_get_time() - (&player->ship->shooter)->last_shoot_time, (&player->ship->shooter)->cooldown, 
        MLV_COLOR_GREEN, 0, "", 0, MLV_COLOR_PINK
    );
    bar_count++;
    
    /* Cooldown bar */
    draw_bar(
        settings->win_width/100 + ((bar_width*bar_count) + (bar_margin*bar_count)), settings->win_height - settings->win_height/100 - bar_height, 
        bar_width, bar_height, 
        MLV_get_time() - (&player->ship->super_shooter)->last_shoot_time, (&player->ship->super_shooter)->cooldown, 
        MLV_COLOR_BLUE, 0, "", 0, MLV_COLOR_PINK
    );
    bar_count++;
    
    /*Stamina bar */
    draw_bar(
        settings->win_width/100 + ((bar_width*bar_count) + (bar_margin*bar_count)), settings->win_height - settings->win_height/100 - bar_height, 
        bar_width, bar_height, 
        (&player->ship->boost)->energy, (&player->ship->boost)->max_energy, 
        MLV_COLOR_YELLOW, 1, "", (&player->ship->boost)->enabled, MLV_COLOR_ORANGE
    );

    /* Draw score */
    sprintf(buffer, "%d", player->score);
    MLV_get_size_of_text(buffer, &text_width, &text_height);
    MLV_draw_text_with_font(settings->win_width - text_width - 10, 10, buffer, settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);    


    /* Invincibility frame */
    if(MLV_get_time() - (&player->ship->life)->last_damage_time < (&player->ship->life)->invincibility_duration) {
        if(MLV_get_time() % 500 < 250) draw_entity(game, player->entity, NULL);
    } else draw_entity(game, player->entity, NULL);



}

void draw_image_progress(MLV_Image* image, MLV_Image *dark_image, int x, int y, int width, int height, int value, int max_value) {
    int progress_height = (height * value) / max_value;
    char text[10];
    int text_width, text_height;

    MLV_resize_image(image, width, height);
    MLV_resize_image(dark_image, width, height);
    MLV_draw_image(dark_image, x, y);

    /* Draw health_percent of full_heart from the bot*/
    MLV_draw_partial_image(image,
        0, height - progress_height, width, progress_height,
        x, y + height - progress_height
    );

    MLV_free_image(image);
    MLV_free_image(dark_image);

    sprintf(text, "%d", value);
    MLV_get_size_of_text(text, &text_width, &text_height);
    MLV_draw_text_with_font(x + width/2 - text_width/1.5, y - text_width*3, text, settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);
}

void draw_bar(int x, int y, int width, int height, int value, int max_value, MLV_Color color, int display_value, char* name,  int flash, MLV_Color flash_color) {
    int bar_width = width;
    int bar_height = height;
    char text[10];
    int text_width, text_height;

    if(flash) color = flash_color;

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
    if(display_value) {
        sprintf(text, "%d", value);
        MLV_get_size_of_text(text, &text_width, &text_height);
        MLV_draw_text_with_font(x + width/2 - text_width/1.5, y, text, settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);
    }

    MLV_get_size_of_text(name, &text_width, &text_height);
    MLV_draw_text_with_font(x + width/2 - text_width/1.5, y - text_height*1.5, name, settings->small_font, MLV_COLOR_WHITE, MLV_TEXT_CENTER);

    MLV_draw_rectangle(x, y, width, height, MLV_COLOR_BLACK);
}