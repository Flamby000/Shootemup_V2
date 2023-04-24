#ifndef STRUCT_H 
#define STRUCT_H 

/*#define return printf("== %s finished\n", __FUNCTION__); return*/

struct _Entity;
struct _Life;
struct _Speed;
struct _EntityLink;
struct _Game;
struct _Animation;
struct _Settings;
struct _Player;
struct _Shooter;
struct _SpaceShip;
struct _Missile;
struct _Level;
struct _Wave;

#define NONE -1

typedef void (*SPEED_FUNC)(struct _Game*, struct _Entity*);
typedef int (*SHOOT_FUNC)(struct _Game*, struct _Entity*);

extern struct _Settings *settings;

typedef struct _Settings {
    int win_width;
    int win_height;
} Settings;

typedef struct _Game {
    struct _EntityLink* entities;
    struct _Player *player;
    struct _Level *level;
} Game;

typedef struct _EntityLink {
    struct _Entity* entity;
    struct _EntityLink* next;
} EntityLink;

typedef enum _EntityType {
    ENNEMY,
    PLAYER,
    MISSILE,
    LABEL,
    BONUS
    
} EntityType;
 
typedef struct _Entity{
    struct _Animation* sprite;
    int x;
    int y;
    int width;
    int height;
    int rotation;
    struct _Speed* speed;

    void* parent;
    EntityType type;
} Entity;

typedef struct _Speed {
    int speed_x;
    int speed_y;
    int speed;
    SPEED_FUNC update_speed;
} Speed;

typedef struct _Life{
    int max_hp;
    int hp;
    int shield;
    int last_damage_time;
    int invincibility_duration;
} Life;

typedef struct _Shooter{
    SHOOT_FUNC update_shoot;
    int last_shoot_time;
    int cooldown;
} Shooter;

typedef struct _SpaceShip {
    struct _Life life;
    struct _Shooter shooter;
} SpaceShip;

typedef struct _Player {
    struct _Entity* entity;
    struct _SpaceShip* ship;
    int score;
} Player;

typedef struct _Ennemy {
    struct _Entity* entity;
    struct _SpaceShip* ship;
    int score;
} Ennemy;

typedef struct _Missile {
    struct _Entity* entity;
    struct _Entity target;
    int damage;
    int is_from_player;

    int fuel;
    int creation_time;
} Missile;

typedef struct _Wave {
    int nb_line;
    int current_line;
    char** object_lines;
} Wave;

typedef struct _Level {
    int nb_wave;
    struct _Wave* waves;

    int current_wave;

    int last_line_time;
    int line_cooldown;

    int last_wave_time;
    int wave_cooldown;
} Level;



typedef enum _Direction {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
} Direction;

typedef enum _AnimationType {
    SPRITE,
    ANIMATED,
    SQUARE,
    MULTIPLE_ANIMATED
} AnimationType;



typedef struct _Animation {
    AnimationType type;
    MLV_Image* sprite;
    MLV_Color color;

    MLV_Image** forward_images;
    MLV_Image** backward_images;
    MLV_Image** left_images;
    MLV_Image** right_images;
    
    int nb_frames;
    int current_frame;
    int frame_duration;
    int last_frame_time;
    
} Animation;

#endif 
