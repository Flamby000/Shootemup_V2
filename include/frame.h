#define WIN_WIDTH 1200
#define WIN_HEIGHT 800

#define FONT_PATH "resources/fonts/Retro.ttf"

void init_frame();
void draw_frame(Game* game);
void free_frame();
void draw_player(Game *game, Player* player);
void draw_bar(int x, int y, int width, int height, int value, int max_value, MLV_Color color, int display_value, char* name, int flash, MLV_Color flash_color);
void draw_image_progress(MLV_Image* image, MLV_Image *dark_image, int x, int y, int width, int height, int value, int max_value);