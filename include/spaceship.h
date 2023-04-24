SpaceShip* create_spaceship(int life, int shoot_cooldown, int invincibility_duration, SHOOT_FUNC update_shoot);
void free_spaceship(Game* game, SpaceShip* spaceship);
void update_spaceship(Game *game, Entity* entity);  
int deals_damage(Game *game, Entity *entity, int damage);
int enable_shield(Game *game, Entity *entity);