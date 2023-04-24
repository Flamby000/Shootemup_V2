#define MISSILE_DATA_PATH "data/missiles.data"

#define BASIC_PLAYER_MISSILE 0
#define BASIC_MISSILE 1

void free_missile(Missile *missile);
Missile* create_missile(Game *game, Entity *sender, int type);
Missile* load_missile(int id, Entity *sender);
int on_collide_missile(Game *game, Missile *missile, Entity *collide, Direction direction);


