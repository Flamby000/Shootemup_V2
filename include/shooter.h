SHOOT_FUNC get_shoot_function(int id);

#define SHOOT_PLAYER_BASIC 0
int shoot_player_basic(Game *game, Entity *entity);

#define SHOOT_BASIC 1
int shoot_basic(Game *game, Entity *entity);

#define SHOOT_TARGET_PLAYER 2
int shoot_target_player(Game *game, Entity *entity);

#define SHOOT_PERFORING_PLAYER 3
int shoot_player_perforing(Game *game, Entity *entity);

#define SHOOT_NONE 4
int shoot_none(Game *game, Entity *entity);

#define SHOOT_SUPER_LASER 5
int shoot_super_laser(Game *game, Entity *entity);

#define SHOOT_MULTIDIRECTIONAL 6
int shoot_multidirectional(Game *game, Entity *entity);

#define SHOOT_360_DIRECTION 7
int shoot_360_direction(Game *game, Entity *entity);