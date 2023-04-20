

int (*get_shoot_function(int id))(Game*, Entity*);

#define SHOOT_PLAYER_BASIC 0
int shoot_player_basic(Game *game, Entity *entity);

#define SHOOT_BASIC 1
int shoot_basic(Game *game, Entity *entity);