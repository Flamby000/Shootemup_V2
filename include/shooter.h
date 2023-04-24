SHOOT_FUNC get_shoot_function(int id);

#define SHOOT_PLAYER_BASIC 0
int shoot_player_basic(Game *game, Entity *entity);

#define SHOOT_BASIC 1
int shoot_basic(Game *game, Entity *entity);


#define SHOOT_TARGET_PLAYER 2
int shoot_target_player(Game *game, Entity *entity);