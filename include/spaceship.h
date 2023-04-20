SpaceShip* create_spaceship(int life, int shoot_cooldown, int invincibility_duration, int (*update_shoot)(struct _Game*, struct _Entity*));
void free_spaceship(SpaceShip* spaceship);
void update_spaceship(Game *game, Entity* entity);  
int deals_damage(Game *game, Entity *entity, int damage);