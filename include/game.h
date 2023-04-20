#define GAME_NAME "Space Crusade"
#define GAME_SPEED 60.0

Game* init_game();
void update_game(Game *game);
void free_game(Game* game);

void insert_entity(Game* game, struct _Entity* entity);
void remove_entity(Game* game, struct _Entity* entity);