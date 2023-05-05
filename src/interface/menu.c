#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/utils/movement.h"
#include "../../include/logic/entity.h"
#include "../../include/logic/game.h"
#include "../../include/interface/animation.h"
#include "../../include/utils/utils.h"
#include "../../include/interface/click_actions.h"
#include "../../include/interface/menu.h"

int update_button(Game* game, Button *button) {
    int mouse_x, mouse_y;
    int entity_removed = 0;
    MLV_get_mouse_position(&mouse_x, &mouse_y);

    if(mouse_x+7 >= button->entity->x && mouse_x <= button->entity->x + button->entity->width+7 &&
       mouse_y+7 >= button->entity->y && mouse_y <= button->entity->y + button->entity->height+7) {
        button->is_over = 1;
        if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
            if(button->on_click != NULL && button->is_slider) {
                button->value = (mouse_x - button->entity->x) * button->max_value / button->entity->width;
                if(button->value < button->min_value) button->value = button->min_value;
                if(button->value > button->max_value) button->value = button->max_value;
                entity_removed = button->on_click(game, button);

            } else if(button->on_click != NULL && button->is_selected == 0) {

                if(get_timestamp_ms() - game->last_click_action_time > 200) {
                    entity_removed = button->on_click(game, button);
                    game->last_click_action_time = get_timestamp_ms();
                }
            }
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


    /* Background */
    MLV_draw_filled_rectangle(
        button->entity->x, 
        button->entity->y, 
        button->entity->width, 
        button->entity->height, 
        button->background_color
    );

    /* Text content*/
    MLV_draw_text_with_font(
        button->entity->x, 
        button->entity->y, 
        button->text, 
        button->font,
        color
    );


    /*Slider*/
    if(button->is_slider) {
        MLV_draw_filled_rectangle(
            button->entity->x, 
            button->entity->y, 
            (button->entity->width *  button->value) / button->max_value, 
            button->entity->height, 
            button->color
        );
    }

    /* Border */
    MLV_draw_rectangle(
        button->entity->x, 
        button->entity->y, 
        button->entity->width, 
        button->entity->height, 
        button->border_color
    );

    /* Underline */
    if(button->underline) {
        MLV_draw_line(
            button->entity->x, 
            button->entity->y + button->entity->height, 
            button->entity->x + button->entity->width, 
            button->entity->y + button->entity->height, 
            color
        );
    }



}

void free_button(Button *button) {
    free(button->text);
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
                      MLV_Color border_color,
                      MLV_Font *font,
                      CLICK_ACTION on_click,
                      int underline
                      ) {

    Button *button = malloc(sizeof(Button));
    button->next = NULL;
    button->entity = create_entity(
        x, y, width, height, 
        0, movement_none, 
        NULL, NULL, 
        button, BUTTON);


    button->text = malloc(sizeof(char) * (strlen(text) + 1));
    button->text = strcpy(button->text, text);


    button->background_color = background_color;
    button->color = color;
    button->font = font;
    button->on_click = on_click;
    button->over_color = over_color;
    button->is_over = 0;
    button->is_selected = 0;
    button->underline = underline;
    button->border_color = border_color;
    button->is_slider = 0;
    button->value = 0;
    button->max_value = 0;
    button->min_value = 0;
    
    return button;
}

void set_slider(Button* button, int value, int min_value, int max_value) {
    button->is_slider = 1;
    button->value = value;
    button->max_value = max_value;
    button->min_value = min_value;
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
            MLV_rgba(0, 0, 0, 0),
            NULL,
            NULL,
            0
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
            MLV_rgba(0, 0, 0, 0),
            settings->big_font,
            NULL,
            0
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
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            go_main_menu,
            0
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
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            restart_match_action,
            0
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
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                resume_match_action,
                0
            )
        );
    }
    else menu = create_match_pause_sample(game, "Game Over", MLV_COLOR_RED);
    return menu;
}


Menu create_main_menu(Game *game, int type) {
    Menu main_menu = create_main_menu_sample(game, type);
    int box_x = settings->win_width / 3 - settings->win_width / 10;
    int box_y = settings->win_height / 6;
    int box_width = settings->win_width - settings->win_width / 4;
    int box_height = settings->win_height - settings->win_height / 4;
    int txt_width, txt_height;
    int txt_width_child, txt_height_child;
    int txt_width_previous;
    int element_count = 0;
    int space_between_elements = box_width/20;
    int element_y = box_y + box_height / 7;
    Button* tmp;
    char* buffer;

    if(type == SETTINGS_MENU) {

        /* Big menu square*/
        insert_button(&main_menu, 
            create_button(game,
                box_x, box_y,
                box_width, box_height,
                "", 
                MLV_rgba(25,78,157,100),
                MLV_rgba(0,0,0,0),
                MLV_rgba(0,0,0,0),
                MLV_COLOR_WHITE,
                NULL,
                NULL,
                0
            )
        );


        /* Menu title */
        MLV_get_size_of_text_with_font("Settings", &txt_width, &txt_height, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width / 2 - txt_width / 2, box_y,
                0, 0, 
                "Settings", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_GREEN,
                MLV_COLOR_GREEN,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                NULL,
                0
            )
        );

        /* Coop mode label */
        MLV_get_size_of_text_with_font("Coop mode : ", &txt_width, &txt_height, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements,
                0, 0, 
                "Coop mode : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                NULL,
                0
            )
        );
        /* Enable / disable button for coop*/
        MLV_get_size_of_text_with_font(settings->coop_mode ? "Enabled" : "Disabled", &txt_width_child, &txt_height_child, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width, element_y + element_count * space_between_elements, 
                txt_width_child, txt_height_child, 
                settings->coop_mode ? "Enabled" : "Disabled", 
                MLV_rgba(0, 0, 0, 0),
                settings->coop_mode ? MLV_COLOR_GREEN : MLV_COLOR_RED,
                settings->coop_mode ? MLV_COLOR_GREEN : MLV_COLOR_RED,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                toggle_coop_mode,
                0
            )
        );
        element_count++;

        /* Language */
        MLV_get_size_of_text_with_font("Language : ", &txt_width, &txt_height, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements,
                0, 0, 
                "Language : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                NULL,
                0
            )
        );
        element_count++;

        /* Volume */
        MLV_get_size_of_text_with_font("Volume : ", &txt_width, &txt_height, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements,
                0, 0, 
                "Volume : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                NULL,
                0
            )
        );

        /*slider for volume*/
        tmp = create_button(game, 
            box_x + box_width/20 + txt_width, element_y + element_count * space_between_elements + txt_height/3 - 5,
            box_width/2, txt_height/2 + 5, 
            "", 
            MLV_COLOR_LIGHT_GRAY,
            MLV_COLOR_ORANGE,
            MLV_COLOR_ORANGE,
            MLV_COLOR_BLACK,
            NULL,
            set_volume,
            0
        );
        set_slider(tmp, settings->volume, 0, 100);
        insert_button(&main_menu, tmp);

        /* Draw volume inside slider*/
        buffer = malloc(sizeof(char) * 15);
        sprintf(buffer, "%d", settings->volume);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + box_width/4 - txt_width_child/2, element_y + element_count * space_between_elements + txt_height/3 - 5,
                0, 0, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_BLACK,
                MLV_COLOR_BLACK,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        free(buffer);
        element_count++;
        element_count++;

        /* Separation */
        insert_button(&main_menu,
            create_button(game, 
                box_x+box_width/20, element_y + (element_count) * space_between_elements - 10,
                box_width-(box_width/20*2), 2,
                "",
                MLV_rgba(0, 0, 0, 0),
                MLV_rgba(0, 0, 0, 0),
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                NULL,
                NULL,
                0
            )
        );

        /* Difficulty */
        MLV_get_size_of_text_with_font("Difficulty : ", &txt_width, &txt_height, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements,
                0, 0, 
                "Difficulty : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                NULL,
                0
            )
        );


        
        
        /* 4 buttons : easy, medium, hard, custom*/
        MLV_get_size_of_text_with_font("Easy", &txt_width_child, &txt_height_child, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + (box_width/6*0), 
                element_y + element_count * space_between_elements, 
                txt_width_child, txt_height_child, 
                "Easy", 
                MLV_rgba(0, 0, 0, 0),
                settings->difficulty->preset == EASY ? MLV_COLOR_GREEN : MLV_COLOR_LIGHT_GRAY,
                settings->difficulty->preset == EASY ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                set_difficulty_easy,
                0
            )
        );
        txt_width_previous = txt_width_child + space_between_elements;
        

        MLV_get_size_of_text_with_font("Medium", &txt_width_child, &txt_height_child, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + txt_width_previous, element_y + element_count * space_between_elements, 
                txt_width_child, txt_height_child, 
                "Medium", 
                MLV_rgba(0, 0, 0, 0),
                settings->difficulty->preset == MEDIUM ? MLV_COLOR_GREEN : MLV_COLOR_LIGHT_GRAY,
                settings->difficulty->preset == MEDIUM ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                set_difficulty_medium,
                0
            )
        );
        txt_width_previous += txt_width_child+space_between_elements;

        MLV_get_size_of_text_with_font("Hard", &txt_width_child, &txt_height_child, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + txt_width_previous, element_y + element_count * space_between_elements, 
                txt_width_child, txt_height_child, 
                "Hard", 
                MLV_rgba(0, 0, 0, 0),
                settings->difficulty->preset == HARD ? MLV_COLOR_GREEN : MLV_COLOR_LIGHT_GRAY,
                settings->difficulty->preset == HARD ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                set_difficulty_hard,
                0
            )
        );
        txt_width_previous += txt_width_child+space_between_elements;


        MLV_get_size_of_text_with_font("Custom", &txt_width_child, &txt_height_child, settings->medium_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width +  txt_width_previous, element_y + element_count * space_between_elements, 
                txt_width_child, txt_height_child, 
                "Custom", 
                MLV_rgba(0, 0, 0, 0),
                settings->difficulty->preset == CUSTOM ? MLV_COLOR_GREEN : MLV_COLOR_LIGHT_GRAY,
                settings->difficulty->preset == CUSTOM ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
                MLV_rgba(0, 0, 0, 0),
                settings->medium_font,
                set_difficulty_custom,
                0
            )
        );
        element_count++;


        /* Custom presets setup */
        /* player_life */
        
        MLV_get_size_of_text_with_font("Life : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Life : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        
        /* Draw '-' */
        MLV_get_size_of_text_with_font("-", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->player_life > 1) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + txt_width, element_y + element_count * space_between_elements, 
                    txt_width_child, txt_height_child, 
                    "-", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_RED,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    decrease_player_life,
                    0
                )
            );
        }
        txt_width_previous = txt_width_child + 10;

        /* Draw value */
        buffer = malloc(sizeof(char) * 6);
        sprintf(buffer, "%d HP ", settings->difficulty->player_life);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        txt_width_previous += txt_width_child + 10;
        free(buffer);

        /* Draw '+' */
        MLV_get_size_of_text_with_font("+", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->player_life < 10) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                    txt_width_child, txt_height_child, 
                    "+", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_GREEN,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    increase_player_life,
                    0
                )
            );
        }
        element_count++;


        /*player_speed*/
        MLV_get_size_of_text_with_font("Speed : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Speed : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );

        /* Draw '-' */
        MLV_get_size_of_text_with_font("-", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->player_speed > 3) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + txt_width, element_y + element_count * space_between_elements, 
                    txt_width_child, txt_height_child, 
                    "-", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_RED,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    decrease_player_speed,
                    0
                )
            );
        }
        txt_width_previous = txt_width_child + 10;

        /* Draw value */
        buffer = malloc(sizeof(char) * 10);
        sprintf(buffer, "%d00 mph", settings->difficulty->player_speed);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        txt_width_previous += txt_width_child + 10;
        free(buffer);

        /* Draw '+' */
        MLV_get_size_of_text_with_font("+", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->player_speed < 10) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                    txt_width_child, txt_height_child, 
                    "+", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_GREEN,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    increase_player_speed,
                    0
                )
            );
        }
        element_count++;

        /* Player cooldown */
        MLV_get_size_of_text_with_font("Cooldown : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Cooldown : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );

        /* Slider for cooldown*/
        tmp = create_button(game, 
                box_x + box_width/20 + txt_width, element_y + element_count * space_between_elements, 
                (box_width - (box_width/20*2) - txt_width) /3,  txt_height, 
                "", 
                MLV_COLOR_LIGHT_GRAY,
                MLV_COLOR_GREEN,
                MLV_COLOR_ORANGE,
                MLV_COLOR_BLACK,
                settings->small_font,
                set_player_cooldown,
                0
            );
        insert_button(&main_menu, tmp);
        set_slider(tmp, settings->difficulty->player_shoot_cooldown, 200, 5000);

        /* Draw value in the slider */
        buffer = malloc(sizeof(char) * 10);
        sprintf(buffer, "%d.%d s", settings->difficulty->player_shoot_cooldown/1000, settings->difficulty->player_shoot_cooldown%1000);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + 10, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_BLACK,
                MLV_COLOR_BLACK,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        free(buffer);
        element_count++;

        /* player_super_shoot_cooldown */
        MLV_get_size_of_text_with_font("Super cooldown : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Super cooldown : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );

        /* Slider for player_super_shoot_cooldown*/
        tmp = create_button(game, 
                box_x + box_width/20 + txt_width, element_y + element_count * space_between_elements, 
                (box_width - (box_width/20*2) - txt_width) /3,  txt_height, 
                "", 
                MLV_COLOR_LIGHT_GRAY,
                MLV_rgba(25,78,157,255),
                MLV_COLOR_ORANGE,
                MLV_COLOR_BLACK,
                settings->small_font,
                set_player_super_shoot_cooldown,
                0
            );
        insert_button(&main_menu, tmp);
        set_slider(tmp, settings->difficulty->player_super_shoot_cooldown, 3000, 23000);

        /* Draw value in the slider */
        buffer = malloc(sizeof(char) * 10);

        sprintf(buffer, "%d.%d s", settings->difficulty->player_super_shoot_cooldown/1000, settings->difficulty->player_super_shoot_cooldown%1000);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + 10, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_BLACK,
                MLV_COLOR_BLACK,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        free(buffer);
        element_count++;

        /* Stamina */
        MLV_get_size_of_text_with_font("Stamina : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Stamina : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );

        /* Slider for stamina*/
        tmp = create_button(game, 
                box_x + box_width/20 + txt_width, element_y + element_count * space_between_elements, 
                (box_width - (box_width/20*2) - txt_width) /3,  txt_height, 
                "", 
                MLV_COLOR_LIGHT_GRAY,
                MLV_COLOR_YELLOW,
                MLV_COLOR_ORANGE,
                MLV_COLOR_BLACK,
                settings->small_font,
                set_player_stamina,
                0
            );
        insert_button(&main_menu, tmp);
        set_slider(tmp, settings->difficulty->player_stamina, 100, 1000);

        /* Draw value in the slider */
        buffer = malloc(sizeof(char) * 10);
        sprintf(buffer, "%d points", settings->difficulty->player_stamina);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + 10, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_BLACK,
                MLV_COLOR_BLACK,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        free(buffer);
        element_count++;


        /*waves_spawn_cooldown*/
        MLV_get_size_of_text_with_font("Waves delay : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Waves delay : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );

        /* Slider for waves_spawn_cooldown*/
        tmp = create_button(game, 
                box_x + box_width/20 + txt_width, element_y + element_count * space_between_elements, 
                (box_width - (box_width/20*2) - txt_width) /3,  txt_height, 
                "", 
                MLV_COLOR_LIGHT_GRAY,
                MLV_COLOR_ORANGE,
                MLV_COLOR_ORANGE,
                MLV_COLOR_BLACK,
                settings->small_font,
                set_waves_spawn_cooldown,
                0
            );
        insert_button(&main_menu, tmp);
        set_slider(tmp, settings->difficulty->waves_spawn_cooldown, 1000, 10000);

        /* Draw value in the slider */
        buffer = malloc(sizeof(char) * 10);
        sprintf(buffer, "%d.%d s", settings->difficulty->waves_spawn_cooldown/1000, settings->difficulty->waves_spawn_cooldown%1000);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + txt_width + 10, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_BLACK,
                MLV_COLOR_BLACK,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        free(buffer);
        element_count++;

        element_count -= 6;
        /* Second part*/
        /*ennemy_life_multiplicator*/
        MLV_get_size_of_text_with_font("Ennemy life : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + box_width/2, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Ennemy life : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );

        /* draw '-'*/
        MLV_get_size_of_text_with_font("-", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->ennemy_life_multiplicator > 1) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + box_width/2 + txt_width, element_y + element_count * space_between_elements,
                    txt_width_child, txt_height_child, 
                    "-", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_RED,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    decrease_ennemy_life_multiplicator,
                    0
                )
            );
        }
        txt_width_previous = txt_width_child + 4;

        /* Draw value */
        buffer = malloc(sizeof(char) * 10);
        sprintf(buffer, "x%d", settings->difficulty->ennemy_life_multiplicator);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + box_width/2 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        txt_width_previous += txt_width_child + 4;

        /* draw '+'*/
        MLV_get_size_of_text_with_font("+", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->ennemy_life_multiplicator < 4) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + box_width/2 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                    txt_width_child, txt_height_child, 
                    "+", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_GREEN,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    increase_ennemy_life_multiplicator,
                    0
                )
            );
        }
        txt_width_previous += txt_width_child + 4;

        element_count++;

        /*ennemy_shoot_cooldown_multiplicator*/
        MLV_get_size_of_text_with_font("Ennemy cooldown : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + box_width/2, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Ennemy cooldown : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );

        /* draw '-'*/
        MLV_get_size_of_text_with_font("-", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->ennemy_shoot_cooldown_multiplicator > 1) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + box_width/2 + txt_width, element_y + element_count * space_between_elements,
                    txt_width_child, txt_height_child, 
                    "-", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_RED,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    decrease_ennemy_shoot_cooldown_multiplicator,
                    0
                )
            );
        }
        txt_width_previous = txt_width_child + 4;

        /* Draw value */
        buffer = malloc(sizeof(char) * 10);
        sprintf(buffer, "x%d", settings->difficulty->ennemy_shoot_cooldown_multiplicator);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + box_width/2 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        txt_width_previous += txt_width_child + 4;

        /* draw '+'*/
        MLV_get_size_of_text_with_font("+", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->ennemy_shoot_cooldown_multiplicator < 4) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + box_width/2 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                    txt_width_child, txt_height_child, 
                    "+", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_GREEN,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    increase_ennemy_shoot_cooldown_multiplicator,
                    0
                )
            );
        }
        txt_width_previous += txt_width_child + 4;

        element_count++;

        /* ennemy_speed_multiplicator */
        MLV_get_size_of_text_with_font("Ennemy speed : ", &txt_width, &txt_height, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + box_width/2, element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Ennemy speed : ", 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );

        /* draw '-'*/
        MLV_get_size_of_text_with_font("-", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->ennemy_speed_multiplicator > 1) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + box_width/2 + txt_width, element_y + element_count * space_between_elements,
                    txt_width_child, txt_height_child, 
                    "-", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_RED,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    decrease_ennemy_speed_multiplicator,
                    0
                )
            );
        }
        txt_width_previous = txt_width_child + 4;

        /* Draw value */
        buffer = malloc(sizeof(char) * 10);
        sprintf(buffer, "x%d", settings->difficulty->ennemy_speed_multiplicator);
        MLV_get_size_of_text_with_font(buffer, &txt_width_child, &txt_height_child, settings->small_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/20 + box_width/2 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                txt_width_child, txt_height_child, 
                buffer, 
                MLV_rgba(0, 0, 0, 0),
                MLV_COLOR_WHITE,
                MLV_COLOR_WHITE,
                MLV_rgba(0, 0, 0, 0),
                settings->small_font,
                NULL,
                0
            )
        );
        txt_width_previous += txt_width_child + 4;

        /* draw '+'*/
        MLV_get_size_of_text_with_font("+", &txt_width_child, &txt_height_child, settings->small_font);
        if(settings->difficulty->ennemy_speed_multiplicator < 4) {
            insert_button(&main_menu, 
                create_button(game, 
                    box_x + box_width/20 + box_width/2 + txt_width + txt_width_previous, element_y + element_count * space_between_elements,
                    txt_width_child, txt_height_child, 
                    "+", 
                    MLV_rgba(0, 0, 0, 0),
                    MLV_COLOR_GREEN,
                    MLV_COLOR_ORANGE,
                    MLV_rgba(0, 0, 0, 0),
                    settings->small_font,
                    increase_ennemy_speed_multiplicator,
                    0
                )
            );
        }
        txt_width_previous += txt_width_child + 4;

        element_count += 2;

        /* SAVE BUTTON */
        MLV_get_size_of_text_with_font("Save", &txt_width, &txt_height, settings->big_font);
        insert_button(&main_menu, 
            create_button(game, 
                box_x + box_width/7 + box_width/2, 
                element_y + element_count * space_between_elements, 
                txt_width, txt_height, 
                "Save", 
                MLV_rgba(0, 128, 0, 150),
                MLV_COLOR_WHITE,
                MLV_COLOR_ORANGE,
                MLV_COLOR_WHITE,
                settings->big_font,
                save_settings_action,
                0
            )
        );

    }

    return main_menu;
}

Menu create_main_menu_sample(Game *game, int selected_button) {
    Menu menu = NULL;
    int txt_width, txt_height;
    int win_height = settings->win_height;
    int win_width = settings->win_width;
    int button_count = 0;
    int space_between_buttons = win_height/10;
    /* Game name*/
    MLV_get_size_of_text_with_font(GAME_NAME, &txt_width, &txt_height, settings->big_font);
    insert_button(&menu, 
        create_button(game, 
            win_width / 2 - txt_width / 2, win_height / 20, 
            0, 0, 
            GAME_NAME, 
            MLV_rgba(0, 0, 0, 0),
            MLV_COLOR_WHITE,
            MLV_COLOR_WHITE,
            MLV_rgba(0, 0, 0, 0),
            settings->big_font,
            NULL,
            0
        )
    );


    /* Campaign button */
    MLV_get_size_of_text_with_font("Campaign", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            win_width / 20, win_height / 4 + space_between_buttons * button_count, 
            txt_width, txt_height, 
            "Campaign", 
            MLV_rgba(0, 0, 0, 0),
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_WHITE,
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            open_campaign_map, 
            selected_button == button_count ? 0 : 1
        )
    );


    button_count++;

    /* Infinite mode button */
    MLV_get_size_of_text_with_font("Infinite", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            win_width / 20, win_height / 4 + space_between_buttons * button_count, 
            txt_width, txt_height, 
            "Infinite", 
            MLV_rgba(0, 0, 0, 0),
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_WHITE,
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            start_infinite_game, 
            selected_button == button_count ? 0 : 1
        )
    );
    button_count++;

    /* Garage button */
    MLV_get_size_of_text_with_font("Garage", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            win_width / 20, win_height / 4 + space_between_buttons * button_count, 
            txt_width, txt_height, 
            "Garage", 
            MLV_rgba(0, 0, 0, 0),
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_WHITE,
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            open_garage, 
            selected_button == button_count ? 0 : 1
        )
    );
    button_count++;

    /* Settings button */
    MLV_get_size_of_text_with_font("Settings", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            win_width / 20, win_height / 4 + space_between_buttons * button_count, 
            txt_width, txt_height, 
            "Settings", 
            MLV_rgba(0, 0, 0, 0),
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_WHITE,
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            open_settings, 
            selected_button == button_count ? 0 : 1
        )
    );
    button_count++;

    /* Tutorial button */
    MLV_get_size_of_text_with_font("Tutorial", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            win_width / 20, win_height / 4 + space_between_buttons * button_count, 
            txt_width, txt_height, 
            "Tutorial", 
            MLV_rgba(0, 0, 0, 0),
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_WHITE,
            selected_button == button_count ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            open_tutorial, 
            selected_button == button_count ? 0 : 1
        )
    );
    button_count++;

    /*Credits button*/
    MLV_get_size_of_text_with_font("Credits", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            win_width / 20, win_height / 4 + space_between_buttons * (button_count ), 
            txt_width, txt_height, 
            "Credits", 
            MLV_rgba(0, 0, 0, 0),
            selected_button == button_count  ? MLV_COLOR_GREEN : MLV_COLOR_WHITE,
            selected_button == button_count  ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            open_credits, 
            selected_button == button_count  ? 0 : 1
        )
    );
    button_count++;

    /* Quit button*/
    MLV_get_size_of_text_with_font("Quit", &txt_width, &txt_height, settings->medium_font);
    insert_button(&menu, 
        create_button(game, 
            win_width / 20, win_height / 4 + space_between_buttons * (button_count ), 
            txt_width, txt_height, 
            "Quit", 
            MLV_rgba(0, 0, 0, 0),
            selected_button == button_count  ? MLV_COLOR_GREEN : MLV_COLOR_WHITE,
            selected_button == button_count  ? MLV_COLOR_GREEN : MLV_COLOR_ORANGE,
            MLV_rgba(0, 0, 0, 0),
            settings->medium_font,
            quit_game, 
            selected_button == button_count  ? 0 : 1
        )
    );

    return menu;
}

