#ifndef MENU_H
#define MENU_H

void draw_button(Game* game, Button *button);
void update_button(Game* game, Button *button);
Menu create_game_over_menu(Game *game);
void free_button(Button *button);
void insert_button(Menu *menu, Button *button);
void remove_menu(Game* game, Menu* menu);
Button* create_button(Game *game, 
                      int x, int y, 
                      int width, int height, 
                      char *text, 
                      MLV_Color background_color,
                      MLV_Color color,
                      MLV_Font *font);

#endif 