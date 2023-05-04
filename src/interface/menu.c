#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/movement.h"
#include "../../include/entity.h"
#include "../../include/game.h"
#include "../../include/animation.h"
#include "../../include/interface/menu.h"

void update_button(Game* game, Button *button) {
}

void draw_button(Game* game, Button *button) { 
    if(button->font == NULL) button->font = settings->small_font;

    MLV_draw_text_with_font(
        button->entity->x, 
        button->entity->y, 
        button->text, 
        button->font,
        button->color
    );

    MLV_draw_filled_rectangle(
        button->entity->x, 
        button->entity->y, 
        button->entity->width, 
        button->entity->height, 
        button->background_color
    );

}

void free_button(Button *button) {
    free(button);
}


void insert_button(Menu *menu, Button *button) {
    Button *current;
    if(*menu == NULL) {
        *menu = button;
        return;
    }
    for(current = *menu; current->next != NULL; current = current->next);
    current->next = button;
}

Button* create_button(Game *game, 
                      int x, int y, 
                      int width, int height, 
                      char *text, 
                      MLV_Color background_color,
                      MLV_Color color,
                      MLV_Font *font) {

    Button *button = malloc(sizeof(Button));
    button->next = NULL;
    button->entity = create_entity(
        x, y, width, height, 
        0, movement_none, 
        NULL, NULL, 
        button, BUTTON);
    button->text = text;
    button->background_color = background_color;
    button->color = color;
    button->font = font;
    insert_entity(game, button->entity);
    return button;
}

Menu create_game_over_menu(Game *game) {
    Menu menu = NULL;
    int txt_width, txt_height;
    char *text = "Game Over";

    /* Darker background*/    
    insert_button(&menu, create_button(game, 
        0, 0, 
        settings->win_width, settings->win_height,
        "", 
        MLV_rgba(0, 0, 0, 150),
        MLV_COLOR_WHITE,
        NULL
    ));

    /* Game over text */
    MLV_get_size_of_text_with_font(
        text, 
        &txt_width, &txt_height, 
        settings->big_font
    );
    insert_button(&menu, create_button(game, 
        settings->win_width / 2 - txt_width / 2, settings->win_height / 10, 
        10, 10, 
        text, 
        MLV_rgba(0, 0, 0, 0),
        MLV_COLOR_WHITE,
        settings->big_font
    ));
    return menu;
}

void remove_menu(Game* game, Menu* menu) {
    Button *current, *next;
    for(current = *menu; current != NULL; current = next) {
        next = current->next;
        remove_entity(game, current->entity, 0);
    }
}

