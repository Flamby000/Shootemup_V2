SpaceShip* create_spaceship(int life, int shoot_cooldown, int (*update_shoot)(struct _Game*, struct _Entity*));
void free_spaceship(SpaceShip* spaceship);
void update_spaceship(Game *game, Entity* entity);  