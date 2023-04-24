#define BONUS_DATA_PATH "data/bonus.data"
#define RANDOM_BONUS 'R'

Bonus *create_bonus(Game *game, char type, int x);
Bonus *create_random_bonus(Game *game, int x);

BONUS_FUNC get_bonus_effect_by_id(int id);

int on_collide_bonus(Game *game, Bonus *bonus, Entity *collide, Direction direction);

#define SHIELD_BONUS 1
void shield_bonus(Game *game, Player* eater, int reverse);
