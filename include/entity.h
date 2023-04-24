int update_entity(Game* game, Entity *entity);
void free_entity(Entity *entity);
Entity* create_entity(int x, int y, int width, int height, 
                      int speed, SPEED_FUNC update_speed,
                      Animation* animation,
                      void* parent, EntityType type
                    );
void avoid_collide_border(Entity *entity);
                      
Direction get_direction(Entity *entity);

Direction get_entity_collide(Entity* entity, Entity* other);
int on_entity_collide(Game* game, Entity* entity, Entity* other, Direction direction);
Entity* closest_entity(Game *game, Entity *entity, EntityType filter);
Entity* closest_ennemy(Game *game);