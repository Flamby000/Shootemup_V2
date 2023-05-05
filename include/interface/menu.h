#ifndef MENU_H
#define MENU_H

void draw_button(Game* game, Button *button);
int update_button(Game* game, Button *button);
void free_button(Button *button);
void insert_button(Menu *menu, Button *button);
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
                      );

void set_slider(Button* button, int value, int min_value, int max_value);

void set_menu(Game *game, Menu *menu);


Menu create_game_over_menu(Game *game, MatchStatus status);
Menu create_match_pause_sample(Game *game, char* text, MLV_Color title_color);

Menu create_main_menu(Game *game, int type);
Menu create_main_menu_sample(Game *game, int selected_button);

#endif 