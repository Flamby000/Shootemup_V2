#define BONUS_DATA_PATH "data/bonus.data"
#define RANDOM_BONUSES "S"

Bonus *create_bonus(Game *game, char type, int x);
void free_bonus(Bonus *bonus);


BONUS_FUNC get_bonus_effect_by_id(int id);

int on_collide_bonus(Game *game, Bonus *bonus, Entity *collide, Direction direction);
int is_bonus_reachable(Game *game, Bonus *bonus);

#define RANDOM_BONUS 'R'
Bonus *create_random_bonus(Game *game, int x);

#define SHIELD_EFFECT 1
void shield_effect(Game *game, Player* eater, int reverse);

#define MAX_LIFE_INCREASE_EFFECT 2
void max_life_increase_effect(Game *game, Player* eater, int reverse);