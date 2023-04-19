void update_entity(Entity *entity);
void free_entity(Entity *entity);
Entity* create_entity(int x, int y, int width, int height, 
                      int speed, void (*update_speed)(struct _Entity*),
                      Animation* animation,
                      void* parent, EntityType type
                    );
void avoid_collide_border(Entity *entity);
                      
Direction get_direction(Entity *entity);