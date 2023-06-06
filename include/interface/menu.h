/**
 * @file frame.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Functions to create and display the menu and buttons
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MENU_H
#define MENU_H

/**
 * @brief Function to draw a button
 * 
 * @param game of the button
 * @param button to draw
 */
void draw_button(Game* game, Button *button);

/**
 * @brief Function to update a button data (in function of user actions)
 * 
 * @param game of the button
 * @param button to update
 * @return 1 if the button was destroyed
 */
int update_button(Game* game, Button *button);

/**
 * @brief Free the button memory
 * 
 * @param button to free
 */
void free_button(Button *button);

/**
 * @brief Function to insert a button in a menu
 * 
 * @param menu to insert the button
 * @param button  to insert
 */
void insert_button(Menu *menu, Button *button);

/**
 * @brief Create a button object
 * 
 * @param game of the button
 * @param x position of the button
 * @param y position of the button
 * @param width of the button
 * @param height of the button
 * @param text of the button
 * @param background_color of the button
 * @param color of the button's text
 * @param over_color of the button's text when the mouse is over the button
 * @param border_color of the button
 * @param font of the button's text
 * @param on_click function to call when the button is clicked
 * @param underline 1 if the text must be underlined
 * @return The pointer of the created button
 */
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

/**
 * @brief The button in argument become a slider
 * 
 * @param button to become a slider
 * @param value of the slider
 * @param min_value of the slider
 * @param max_value of the slider
 */
void set_slider(Button* button, int value, int min_value, int max_value);

/**
 * @brief Set the menu of the game. It replace and free the previous to set the new one.
 * 
 * @param game to set the menu
 * @param menu to set
 */
void set_menu(Game *game, Menu *menu);

/**
 * @brief Assign an image to a button
 * 
 * @param button to assign the image
 * @param path of the image
 */
void set_image(Button* button, char* path);
void set_id(Button* button, char* id);
Button* get_by_id(Menu menu, char* id);
void set_animation(Button* button, char* sprite);
void set_sprite(Button* button, Animation* sprite);
Button* create_element(Menu *menu, Game *game, int x, int y, int width, int height);
void set_on_click(Button* button, CLICK_ACTION on_click);
void set_circular_movement(Button* button, Button* parent);
void set_background_color(Button* button, MLV_Color color);
void set_border(Button* button, MLV_Color color);
void set_text(Button* button, char* text, MLV_Font *font, MLV_Color color);
/**
 * @brief Create a game over menu 
 * 
 * @param game of the menu
 * @param status of the match
 * @return Menu created
 */
Menu create_game_over_menu(Game *game, MatchStatus status);

/**
 * @brief Create a base of a game over match
 * 
 * @param game of the menu
 * @param text title of the menu
 * @param title_color of the title
 * @return Menu created
 */
Menu create_match_pause_sample(Game *game, char* text, MLV_Color title_color);

/**
 * @brief Create a main menu object in function of a type
 * 
 * @param game of the menu
 * @param type of the main menu
 * @return Menu created
 */
Menu create_main_menu(Game *game, int type);

/**
 * @brief Create a common main menu without submenus
 * 
 * @param game of the menu
 * @param selected_button of the menu
 * @return Menu created
 */
Menu create_main_menu_sample(Game *game, int selected_button);




#endif 