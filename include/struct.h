struct _Entity;
struct _Life;
struct _Speed;
struct _EntityLink;
struct _Game;
struct _Animation;


typedef struct _Game {
    struct _EntityLink* entities;
} Game;

typedef struct _EntityLink {
    struct _Entity* entity;
    struct _EntityLink* next;
} EntityLink;

typedef struct _Entity{
    struct _Animation* sprite;
    int x;
    int y;
    int width;
    int height;
    int rotation;
    struct _Speed *speed;
} Entity;

typedef struct _Speed {
    int speed_x;
    int speed_y;
    int speed;
    void (*update_speed)(struct _Speed*);
} Speed;

typedef struct _Life{
    int max_hp;
    int hp;
    int shield;
} Life;


typedef struct _Animation {
    int is_animated;
    MLV_Image* sprite;
} Animation;
