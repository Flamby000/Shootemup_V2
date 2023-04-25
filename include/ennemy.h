#define ENNEMY_DATA_PATH "data/ennemies.data"

#define BASIC_ENNEMY '1'
#define TIER2_ENNEMY '2'
#define TIER3_ENNEMY '3'

Ennemy* create_ennemy(Game *game, char type, int x);
void free_ennemy(Game* game, Ennemy *ennemy);
int free_out_of_screen(Game *game, Entity *entity);
int on_collide_ennemy(Game *game, Ennemy *ennemy, Entity *collide, Direction direction);