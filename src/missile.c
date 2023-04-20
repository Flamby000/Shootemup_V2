#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/movement.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/entity.h"
#include "../include/missile.h"

Missile* create_missile(Game *game, Entity *sender, MissileType type) {
    Missile *missile = malloc(sizeof(Missile));
    int width, height, x, y, speed, damage;
    void (*movement)(struct _Game*, struct _Entity*);
    Animation *animation;
    
    switch(type) {
        case BASIC_MISSILE:
            width = sender->width/5;
            height = sender->width/5;
            x = sender->x + sender->width/2 - width/2;
            y = sender->y + sender->height/2;
            speed = 5;
            damage = 1;
            animation = init_sprite(MLV_load_image("resources/missiles/missile6_1.png"));
            movement = movement_forward;
            target = game->player->entity;
            break;

        case BASIC_PLAYER_MISSILE:
            width = sender->width/3;
            height = sender->height/3;
            x = sender->x + sender->width/2 - width/2;
            y = sender->y + sender->height/2;
            speed = 5;
            damage = 1;
            animation = init_animation("resources/missiles/missile1_%d.png");
            movement = movement_backward;
            break;
            
        default:
            printf("Error : Missile type not found\n");
            break;
    }

    missile->entity = create_entity(x, y, width, height, speed, movement, animation, missile, MISSILE);
    insert_entity(game, missile->entity);
    missile->damage = damage;
    return missile;
}



void free_missile(Game *game, Missile *missile) {
    remove_entity(game, missile->entity);
    free(missile);
}