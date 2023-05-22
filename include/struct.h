/**
 * @file struct.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief All the structures of the program
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STRUCT_H 
#define STRUCT_H 

/**
 * @brief Number of stars on the background
 * 
 */
#define NB_STAR 100

/**
 * @brief Maximum size of a star
 * 
 */
#define STAR_MAX_SIZE 3

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
struct _Boost;
struct _SpaceShip;
struct _Missile;
struct _Bonus;
struct _BonusLink;
struct _Level;
struct _Wave;
struct _Button;
struct _Difficulty; 

#define NONE -1


/**
 * @brief Function pointer to update the speed of an entity
 * First argument is the current game
 * Second argument is the entity to update speed
 */ 
typedef void (*SPEED_FUNC)(struct _Game*, struct _Entity*);

/**
 * @brief Function pointer to update the shoot of a spaceship
 * First argument is the current game
 * Second argument is the entity's spaceship to update
 * Return 1 if an entity was removed
 */
typedef int (*SHOOT_FUNC)(struct _Game*, struct _Entity*);

/**
 * @brief Function pointer to affect a bonus on a player
 * First argument is the current game
 * Second argument is the player to affect
 * Third argument specify if the bonus will be reversed
 */
typedef void (*BONUS_FUNC)(struct _Game*, struct _Player*, int);

/**
 * @brief Function pointer of a button click action
 * First argument is the current game
 * Second argument is the button clicked
 * Return 1
 */
typedef int (*CLICK_ACTION)(struct _Game*, struct _Button*);
extern struct _Settings *settings;

/**
 * @brief Enumeration defining a difficulty preset
 * 
 */
typedef enum _DifficultyPreset {
    EASY,
    MEDIUM,
    HARD,
    CUSTOM
} DifficultyPreset;

/**
 * @brief Structure defining the configuration of a match difficulty
 * 
 */
typedef struct _Difficulty {
    DifficultyPreset preset;
    int waves_spawn_cooldown;
    int ennemy_life_multiplicator;
    int ennemy_shoot_cooldown_multiplicator;
    int ennemy_speed_multiplicator;
    int player_life;
    int player_shoot_cooldown;
    int player_super_shoot_cooldown;
    int player_speed;
    int player_stamina;
} Difficulty;


/**
 * @brief Structure defining the settings of the game (used a global variable)
 * 
 */
typedef struct _Settings {
    int win_width;
    int win_height;
    int infinite_mode;

    MLV_Font *small_font;
    MLV_Font *medium_font;
    MLV_Font *big_font;
    MLV_Font *huge_font;
    
    struct _Difficulty *difficulty;
    int coop_mode;
    int volume;

} Settings;


/**
 * @brief Structure defining a button in the game
 * 
 */
typedef struct _Button {
    struct _Button* next;
    struct _Entity* entity;

    char* text;
    CLICK_ACTION on_click;
    MLV_Color background_color;
    MLV_Color color;
    MLV_Color over_color;
    MLV_Color border_color;
    MLV_Font *font;


    int is_over;
    int is_selected;
    int underline;

    int is_slider;
    int value;
    int max_value;
    int min_value;
} Button, *Menu;


/**
 * @brief The ID of the main menu
 * 
 */
#define MAIN_MENU -1

/**
 * @brief The ID of the campaign menu
 * 
 */
#define CAMPAIGN_MENU 0

/**
 * @brief The ID of the garage menu
 * 
 */
#define GARAGE_MENU 2

/**
 * @brief The ID of the settings menu
 * 
 */
#define SETTINGS_MENU 3

/**
 * @brief The ID of the tutorial menu
 * 
 */
#define TUTORIAL_MENU 4

/**
 * @brief The ID of the credits menu
 * 
 */
#define CREDITS_MENU 5


/**
 * @brief Enumeration of all possible match status
 * 
 */
typedef enum _MatchStatus {
    PAUSE,
    PROCESS,
    MATCH_LOOSE,
    MATCH_WIN,
    NOT_STARTED
} MatchStatus;


/**
 * @brief Structure defining the game's data
 * 
 */
typedef struct _Game {
    struct _EntityLink* entities;
    struct _Entity *background[NB_STAR+2];
    Menu *current_menu;
    
    struct _Level *level;
    MatchStatus match_status;

    int last_click_action_time;
} Game;

/**
 * @brief Structure defining a linked list of entities
 * 
 */
typedef struct _EntityLink {
    struct _Entity* entity;
    struct _EntityLink* next;
} EntityLink;

/**
 * @brief Enumeration of all possible entity types
 * 
 */
typedef enum _EntityType {
    ENNEMY,
    PLAYER,
    MISSILE,
    LABEL,
    BONUS,
    BUTTON
} EntityType;

/**
 * @brief Structure defining an entity (every object in the game is an entity) 
 * 
 */
typedef struct _Entity{
    struct _Animation* sprite;

    char* destruction_img_path;
    
    int x;
    int y;
    int width;
    int height;
    int rotation;
    struct _Speed* speed;

    struct _EntityLink* children;
    void* parent;
    EntityType type;
} Entity;

/**
 * @brief Structure defining a speed data of a spaceship
 * 
 */
typedef struct _Speed {
    int speed_x;
    int speed_y;
    int speed;
    int default_speed;
    SPEED_FUNC update_speed;
} Speed;

/**
 * @brief Structure defining a life data of a spaceship
 * 
 */
typedef struct _Life{
    struct _Entity *shield_entity;
    int max_hp;
    int hp;
    int shield;
    int last_damage_time;
    int invincibility_duration;
} Life;

/**
 * @brief Structure defining a shooter data of a spaceship
 * It used to manage the missile creaton
 */
typedef struct _Shooter{
    SHOOT_FUNC update_shoot;
    int last_shoot_time;
    int cooldown;
} Shooter;

/**
 * @brief Structure defining a linked list of a bonus
 * 
 */
typedef struct _BonusLink {
    struct _Bonus* bonus;
    struct _BonusLink* next;
} BonusLink;

/**
 * @brief Structure defining a boost of a spaceship
 * 
 */
typedef struct _Boost {
    int speed;
    int energy;
    int max_energy;

    int end_of_use_time;
    int cooldown_before_regen;
    int regen_speed;
    int consumption_speed;
    int enabled;
} Boost;

/**
 * @brief Structure defininf a spaceship data (for player and ennemy)
 * 
 */
typedef struct _SpaceShip {
    struct _Life life;
    struct _Shooter shooter;
    struct _BonusLink* bonus;
    struct _Boost boost;
    struct _Shooter super_shooter;
    int total_shoots;
} SpaceShip;


/**
 * @brief Structure defining a player's data and its controls
 * 
 */
typedef struct _Player {
    struct _Entity* entity;
    struct _SpaceShip* ship;
    int score;
    int boss_kill_count;
    int player_number;

    MLV_Keyboard_button key_left;
    MLV_Keyboard_button key_right;
    MLV_Keyboard_button key_up;
    MLV_Keyboard_button key_down;
    MLV_Keyboard_button key_shoot;
    MLV_Keyboard_button key_super_shoot;
    MLV_Keyboard_button key_boost;
} Player;

/**
 * @brief Structure defining an ennemy's data
 * 
 */
typedef struct _Ennemy {
    struct _Entity* entity;
    struct _SpaceShip* ship;
    int score;
    int is_boss;
} Ennemy;

/**
 * @brief Structure defining a missile's data
 * 
 */
typedef struct _Missile {
    struct _Entity* entity;
    struct _Entity *sender;
    struct _Entity target;
    int damage;
    int is_from_player;

    int invincible;
    int fuel;
    int creation_time;

    int last_damage_time;
} Missile;

/**
 * @brief Structure defining a bonus's data
 * 
 */
typedef struct _Bonus {
    struct _Entity* entity;
    BONUS_FUNC effect;
    char type;
    int consumer;
} Bonus;

/**
 * @brief Structure defining a wave in a level.
 * Each 'object_lines' is a line of objects (bonus or ennemies) the level file.
 */
typedef struct _Wave {
    int nb_line;
    int current_line;
    char** object_lines;

    char boss_id;
    struct _Ennemy *boss;
} Wave;

/**
 * @brief Structure defining a level
 * 
 */
typedef struct _Level {
    char* level_file;

    int nb_wave;
    struct _Wave* waves;

    int current_wave;


    int last_line_time;
    int line_cooldown;

    int last_wave_time;
    int wave_cooldown;
} Level;


/**
 * @brief Enumeration listing all possible directions (for pushing an entity)
 * 
 */
typedef enum _Direction {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
} Direction;

/**
 * @brief Enumeration listing all possible animation types for an entity
 * 
 */
typedef enum _AnimationType {
    SPRITE,
    ANIMATED,
    SQUARE,
    MULTIPLE_ANIMATED,
    ONE_SHOT_ANIMATION
} AnimationType;


/**
 * @brief Structure defining an animation of every possivble types
 * 
 */
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
