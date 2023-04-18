#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/animation.h"
#include "../include/entity.h"

Entity create_entity(int x, int y, int width, int height) {
    Entity entity;
    entity.x = x;
    entity.y = y;
    entity.width = width;
    entity.height = height;

    return entity;
}    




void update_entity() {

}

void free_entity(Entity *entity) {
    free_animation(entity->sprite);
}