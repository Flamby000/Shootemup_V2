#define PLAYER_WIDTH 42
#define PLAYER_HEIGHT 74    

Player* create_player(Game *game);
void free_player(Game* game, Player* player);
int on_collide_player(Game *game, Player *player, Entity *collide, Direction direction);
