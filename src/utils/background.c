#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../../include/struct.h"
#include "../../include/interface/frame.h"
#include "../../include/logic/entity.h"
#include "../../include/interface/animation.h"
#include "../../include/logic/game.h"
#include "../../include/utils/movement.h"
#include "../../include/utils/background.h"

void set_background_speed(Game *game, double factor) {
    int i;
    for(i = 0; i < NB_STAR+2; i++) {
        game->background[i]->speed->speed = game->background[i]->speed->default_speed;
        game->background[i]->speed->speed = game->background[i]->speed->speed * factor;
    }
}

void init_background(Game *game) {
    int size, speed, i;
    int element_count = 0;
    Entity *tmp;

    /* The background image */
    tmp = create_entity(
            0, 
            0, 
            settings->win_width, 
            settings->win_height,
            0,
            movement_none,  
            init_sprite(MLV_load_image("resources/background.png")),
            NULL,
            NULL,
            LABEL
        );
    game->background[element_count] = tmp;
    element_count++;
    insert_entity(game, tmp);

    /* Adding squares for stars*/
    for(i = 0; i < NB_STAR; i++) {
        size = rand() % STAR_MAX_SIZE + 1;
        speed = size;
        tmp = create_entity(
                rand() % settings->win_width, 
                rand() % settings->win_height, 
                size, 
                size,
                speed, /* TODO : find a way to STOP the background movement */
                movement_infinite_scroll,  
                init_square(MLV_rgba(255, 255, rand() % 254 + 1, 255)), NULL,
                NULL,
                LABEL
            );
        game->background[element_count] = tmp;
        element_count++;
        insert_entity(game, tmp);
    }

    /* Add big planet */
    tmp = create_entity(
            -settings->win_width/100, 
            0, 
            settings->win_width/5, 
            settings->win_width/5,
            1,
            movement_infinite_scroll,  
            init_sprite(MLV_load_image("resources/utils/planet.png")), NULL,
            NULL, LABEL
        );
    game->background[element_count] = tmp;
    element_count++;
    insert_entity(game, tmp);
}

void set_background_image(Game *game, Animation *animation) {
    /* Set the image of the planet*/
    int index = NB_STAR+1;
    free_animation(game->background[index]->sprite);
    game->background[index]->sprite = animation;

}