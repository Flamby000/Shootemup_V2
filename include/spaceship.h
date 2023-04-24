SpaceShip* create_spaceship(int life, int shoot_cooldown, int invincibility_duration, SHOOT_FUNC update_shoot);
void free_spaceship(Game* game, SpaceShip* spaceship);
void update_spaceship(Game *game, Entity* entity);  
int deals_damage(Game *game, Entity *entity, int damage);
int enable_shield(Game *game, Entity *entity);
void disable_shield(Game *game, Entity *entity);

void add_bonus(Game *game, Entity *entity, Bonus *bonus);
void remove_bonus(Game *game, Entity *entity, Bonus *bonus);
void free_bonuses(Game *game, Entity *entity);
int have_bonus(Entity *entity, char bonus_type);
int count_bonus(Entity *entity);
Bonus *get_bonus(Entity *entity, char type);
int remove_random_bonus(Game* game, Entity *entity);
SpaceShip* get_spaceship(Entity *entity);
