#define WIN_WIDTH 1200
#define WIN_HEIGHT 800

void init_frame();
void draw_frame(Game* game);
void free_frame();
void draw_player(Game *game, Player* player);
void draw_bar(int x, int y, int width, int height, int value, int max_value, MLV_Color color);