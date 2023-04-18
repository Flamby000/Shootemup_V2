#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"
#include "../include/entity.h"
#include "../include/animation.h"
#include "../include/game.h"
#include "../include/background.h"

void init_background(Game *game) {
    Entity entity = create_entity(0, 0, WIN_WIDTH, WIN_HEIGHT);
    Animation animation = init_sprite(MLV_load_image("resources/background.png"));
    entity.sprite = &animation;
    insert_entity(game, &entity);
}