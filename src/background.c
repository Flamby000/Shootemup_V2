#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"
#include "../include/entity.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/movement.h"
#include "../include/background.h"


void init_background(Game *game) {
    int size, speed, i;

    /* The background image */
    insert_entity(game, 
        create_entity(
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
            )
    );

    /* Adding squares for stars*/
    for(i = 0; i < NB_STAR; i++) {
        size = rand() % STAR_MAX_SIZE + 1;
        speed = size;

        insert_entity(game, 
            create_entity(
                rand() % settings->win_width, 
                rand() % settings->win_height, 
                size, 
                size,
                speed, /* TODO : find a way to STOP the background movement */
                movement_infinite_scroll,  
                init_square(MLV_rgba(255, 255, rand() % 254 + 1, 255)), NULL,
                NULL,
                LABEL
            )
        );
    }

    /* Add big planet */
    insert_entity(game, 
        create_entity(
            -settings->win_width/100, 
            0, 
            settings->win_width/5, 
            settings->win_width/5,
            1,
            movement_infinite_scroll,  
            init_sprite(MLV_load_image("resources/utils/planet.png")), NULL,
            NULL, LABEL
        )
    );
}