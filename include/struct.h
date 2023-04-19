struct _Entity;
struct _Life;
struct _Speed;
struct _EntityLink;
struct _Game;
struct _Animation;
struct _Settings;

struct _Settings* settings;

typedef struct _Settings {
    int win_width;
    int win_height;
} Settings;

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
    struct _Speed* speed;
} Entity;

typedef struct _Speed {
    int speed_x;
    int speed_y;
    int speed;
    void (*update_speed)(struct _Entity*);
} Speed;

typedef struct _Life{
    int max_hp;
    int hp;
    int shield;
} Life;


typedef enum _AnimationType {
    SPRITE,
    ANIMATED,
    SQUARE
} AnimationType;

typedef struct _Animation {
    AnimationType type;
    MLV_Image* sprite;
    MLV_Color color;
} Animation;
