void update_entity(Game* game, Entity *entity);
void free_entity(Entity *entity);
Entity* create_entity(int x, int y, int width, int height, 
                      int speed, void (*update_speed)(struct _Game*, struct _Entity*),
                      Animation* animation,
                      void* parent, EntityType type
                    );
void avoid_collide_border(Entity *entity);
                      
Direction get_direction(Entity *entity);


Direction get_entity_collide(Entity* entity, Entity* other);
void on_entity_collide(Game* game, Entity* entity, Entity* other, Direction direction);
