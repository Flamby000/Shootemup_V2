SPEED_FUNC get_movement_function(int id);

#define MOVEMENT_NONE 0
void movement_none(Game* game, Entity *entity);

#define MOVEMENT_FORWARD 1
void movement_forward(Game* game, Entity *entity);

#define MOVEMENT_BACKWARD 2
void movement_backward(Game *game, Entity *entity);

#define MOVEMENT_INFINITE_SCROLL 3
void movement_infinite_scroll(Game* game, Entity *entity);

#define MOVEMENT_CONTROLLER 4
void movement_controller(Game* game, Entity *entity);

#define MOVEMENT_FOLLOW_PLAYER 5
void movement_follow_player(Game* game, Entity *entity);




void push_entity(Game *game, Entity *entity);
void movement_follow_entity(Game *game, Entity *entity, Entity *target);