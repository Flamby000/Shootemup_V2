#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/movement.h"
#include "../../include/entity.h"
#include "../../include/game.h"
#include "../../include/animation.h"
#include "../../include/interface/click_actions.h"
#include "../../include/interface/menu.h"

int update_button(Game* game, Button *button) {
    int mouse_x, mouse_y;
    int entity_removed = 0;
    MLV_get_mouse_position(&mouse_x, &mouse_y);

    if(mouse_x >= button->entity->x && mouse_x <= button->entity->x + button->entity->width &&
       mouse_y >= button->entity->y && mouse_y <= button->entity->y + button->entity->height) {
        button->is_over = 1;
        if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
            if(button->on_click != NULL && button->is_selected == 0) entity_removed = button->on_click(game, button);
            button->is_selected = 1;
        } else if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_RELEASED) {
            button->is_selected = 0;
        }
    } else {
        if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
            button->is_selected = 0;
        }

        button->is_over = 0;
    }
    return entity_removed;
}

void draw_button(Game* game, Button *button) { 
    MLV_Color color;
    if(button->font == NULL) button->font = settings->small_font;

    if(button->is_over) color = button->over_color;
    else color = button->color;

    MLV_draw_text_with_font(
        button->entity->x, 
        button->entity->y, 
        button->text, 
        button->font,
        color
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
                      MLV_Color over_color,
                      MLV_Font *font,
                      CLICK_ACTION on_click
                      ) {

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
    button->on_click = on_click;
    button->over_color = over_color;
    button->is_over = 0;
    button->is_selected = 0;
    return button;
}


void set_menu(Game *game, Menu *menu) {
    Button *current;

if(game->current_menu != NULL)     remove_entities_by_type(game, BUTTON);

    game->current_menu = menu;

    if(menu == NULL) return;
    
    for(current = *menu; current != NULL; current = current->next) 
        insert_entity(game, current->entity);
}


Menu create_match_pause_sample(Game *game, char* text, MLV_Color title_color) {
    Menu menu = NULL;
    int txt_width, txt_height;

    /* Darker background*/    
    insert_button(&menu, 
        create_button(game, 
            0, 0, 
            settings->win_width, settings->win_height,
            "", 
            MLV_rgba(0, 0, 0, 150),
            MLV_COLOR_WHITE,
            MLV_COLOR_WHITE,
            NULL,
            NULL
        )
    );

    /* Game over text */
    MLV_get_size_of_text_with_font(text, &txt_width, &txt_height, settings->big_font);
    insert_button(&menu, 
        create_button(game, 
            settings->win_width / 2 - txt_width / 2, settings->win_height / 10, 
            0, 0, 
            text, 
            MLV_rgba(0, 0, 0, 0),
            title_color,
            title_color,
            settings->big_font,
            NULL
        )
    );

    /* Main menu button */
    MLV_get_size_of_text_with_font("Main menu", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            settings->win_width / 20, settings->win_height / 4, 
            txt_width, txt_height, 
            "Main menu", 
            MLV_rgba(0, 0, 0, 0),
            MLV_COLOR_GRAY,
            MLV_COLOR_WHITE,
            settings->medium_font,
            go_main_menu
        )
    );

    MLV_get_size_of_text_with_font("Restart", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            settings->win_width / 20, settings->win_height / 4 + txt_height * 2, 
            txt_width, txt_height, 
            "Restart", 
            MLV_rgba(0, 0, 0, 0),
            MLV_COLOR_GRAY,
            MLV_COLOR_WHITE,
            settings->medium_font,
            restart_match_action
        )
    );

    return menu;
}

Menu create_game_over_menu(Game *game, MatchStatus status) {
    Menu menu; 
    int txt_width, txt_height;
    if(status == MATCH_WIN) menu = create_match_pause_sample(game, "You win !", MLV_COLOR_GREEN);
    else if(status == PAUSE) {
        menu = create_match_pause_sample(game, "Pause", MLV_COLOR_LIGHT_GRAY);
        MLV_get_size_of_text_with_font("Resume", &txt_width, &txt_height, settings->medium_font);
        insert_button(&menu, 
            create_button(game, 
                settings->win_width / 20, settings->win_height / 4 + txt_height * 4, 
                txt_width, txt_height, 
                "Resume", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_GRAY,
                MLV_COLOR_WHITE,
                settings->medium_font,
                resume_match_action
            )
        );
    }
    else menu = create_match_pause_sample(game, "Game Over", MLV_COLOR_RED);
    return menu;
}