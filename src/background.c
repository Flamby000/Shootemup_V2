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
    int i;
    int size;

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
            LABEL
            )
    );

    /* Adding squares for stars*/
    for(i = 0; i < NB_STAR; i++) {
        size = rand() % STAR_MAX_SIZE + 1;

        insert_entity(game, 
            create_entity(
                rand() % settings->win_width, 
                rand() % settings->win_height, 
                size, 
                size,
                size, /* TODO : find a way to STOP the background movement */
                movement_infinite_scroll,  
                init_square(MLV_rgba(rand() % 254 + 1,rand() % 254 + 1, rand() % 254 + 1, 255)),
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
            init_sprite(MLV_load_image("resources/utils/planet.png")),
            NULL, LABEL
        )
    );
}