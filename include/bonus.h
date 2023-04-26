#define BONUS_DATA_PATH "data/bonus.data"

Bonus *create_bonus(Game *game, char type, int x);
void free_bonus(Bonus *bonus);

BONUS_FUNC get_bonus_effect_by_id(char id);

int on_collide_bonus(Game *game, Bonus *bonus, Entity *collide, Direction direction);
int is_bonus_reachable(Game *game, Bonus *bonus);


#define RANDOM_BONUSES "SPHVMU"

#define RANDOM_BONUS 'R'
Bonus *create_random_bonus(Game *game, int x);

#define SHIELD_EFFECT 'S'
void shield_effect(Game *game, Player* eater, int reverse);

#define LIFE_INCREASE_EFFECT 'H'
void life_increase_effect(Game *game, Player* eater, int reverse);

#define MAX_LIFE_INCREASE_EFFECT 'M'
void max_life_increase_effect(Game *game, Player* eater, int reverse);

#define POWER_UP_SHOOT_EFFECT 'P'
void power_up_shoot_effect(Game *game, Player* eater, int reverse);

#define POWER_UP_SPEED_EFFECT 'V'
void power_up_speed_effect(Game *game, Player* eater, int reverse);

#define SPAWN_UNIT_EFFECT 'U'
void spawn_unit_effect(Game *game, Player* eater, int reverse);