#define ENNEMY_DATA_PATH "data/ennemies.data"

#define BASIC_ENNEMY '1'

Ennemy* create_ennemy(Game *game, char type, int x);
void free_ennemy(Ennemy *ennemy);
void free_out_of_screen(Game *game, Entity *entity);
void on_collide_ennemy(Game *game, Ennemy *ennemy, Entity *collide);