#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/game.h"
#include "../include/movement.h"
#include "../include/animation.h"
#include "../include/entity.h"
#include "../include/spaceship.h"

SpaceShip* create_spaceship(int life, int shoot_cooldown, int invincibility_duration,  SHOOT_FUNC update_shoot) {
    SpaceShip* ship = malloc(sizeof(SpaceShip));
    (&ship->life)->hp = life;
    (&ship->life)->max_hp = life; 
    (&ship->life)->shield = 0; 
    (&ship->life)->last_damage_time = 0; 
    (&ship->life)->invincibility_duration = invincibility_duration; 

    (&ship->shooter)->last_shoot_time = 0;
    (&ship->shooter)->update_shoot = update_shoot;
    (&ship->shooter)->cooldown = shoot_cooldown;

    ship->bonus = NULL;

    return ship;
}

void update_spaceship(Game *game, Entity* entity) {
    Shooter *shooter;
    if(entity->type == PLAYER)      shooter = &((Player*)entity->parent)->ship->shooter; 
    else if(entity->type == ENNEMY) shooter = &((Ennemy*)entity->parent)->ship->shooter;
    else return;

    if(MLV_get_time() - shooter->last_shoot_time > shooter->cooldown) {
        if(shooter->update_shoot(game, entity)) {
            shooter->last_shoot_time = MLV_get_time();
        }
    }    
}

void add_bonus(Game *game, Entity *entity, Bonus *bonus) {
    SpaceShip *ship = get_spaceship(entity);
    BonusLink *new_bonus;

    if(ship == NULL) return;
    bonus->effect(game, entity->parent, 0);
    
    /* TODO : adjust position when remove/add */
    bonus->entity->speed->update_speed = movement_none;
    bonus->entity->x = settings->win_width/100 + count_bonus(entity) * entity->width;
    bonus->entity->y = settings->win_width/100;

    new_bonus = malloc(sizeof(BonusLink));
    new_bonus->bonus = bonus;
    new_bonus->next = ship->bonus;
    ship->bonus = new_bonus;
}

int count_bonus(Entity *entity) {
    SpaceShip *ship = get_spaceship(entity);
    BonusLink *current;
    int count = 0;
    if(ship == NULL) return 0;

    for(current = ship->bonus; current != NULL; current = current->next) {
        count++;
    }

    return count;
}

void remove_bonus(Game *game, Entity *entity, Bonus *bonus) {
    SpaceShip *ship = get_spaceship(entity);
    BonusLink *current;
    BonusLink *previous = NULL;

    if(ship == NULL) return;

    bonus->effect(game, entity->parent, 1);

    current = ship->bonus;
    while(current != NULL) {
        if(current->bonus == bonus) {
            if(previous == NULL) ship->bonus = current->next;
            else previous->next = current->next;
            remove_entity(game, current->bonus->entity);
            return;
        }
        previous = current;
        current = current->next;
    }
}

int have_bonus(Entity *entity, char bonus_type) {
    SpaceShip *ship;
    BonusLink *current;
    if(entity->type == PLAYER)      ship = ((Player*)entity->parent)->ship;
    else if(entity->type == ENNEMY) ship = ((Ennemy*)entity->parent)->ship;
    else return 0;

    for(current = ship->bonus; current != NULL; current = current->next) {
        if(current->bonus->type == bonus_type) return 1;
    }

    return 0;
}

void free_bonuses(Game *game, Entity *entity) {
    SpaceShip *ship = get_spaceship(entity);
    BonusLink *current;
    BonusLink *next;

    if(ship == NULL) return;

    current = ship->bonus;
    while(current != NULL) {
        next = current->next;
        remove_entity(game, current->bonus->entity);
        current = next;
    }
    ship->bonus = NULL;
}

SpaceShip* get_spaceship(Entity *entity) {
    if(entity->type == PLAYER)      return ((Player*)entity->parent)->ship;
    else if(entity->type == ENNEMY) return ((Ennemy*)entity->parent)->ship;
    else return NULL;
}

void free_spaceship(Game* game, SpaceShip* spaceship) {
    /*if((&spaceship->life)->shield) remove_child(entity, (&spaceship->life)->shield_entity);*/
    free(spaceship);
}


Life* get_life(Entity *entity) {
    if(entity->type == PLAYER)      return &((Player*)entity->parent)->ship->life;
    else if(entity->type == ENNEMY) return &((Ennemy*)entity->parent)->ship->life;
    else return NULL;
}

int deals_damage(Game *game, Entity *entity, int damage) {
    Life *life = get_life(entity);
    
    if(life == NULL) return 0;

    if(damage <= 0) {
        life->hp -= damage;
        if(life->hp > life->max_hp) life->hp = life->max_hp;
        return 0;
    }

    if(MLV_get_time() - life->last_damage_time < life->invincibility_duration) return 0;

    if(life->shield) {
        disable_shield(game, entity);
        return 1;
    }

    life->hp -= damage;

    life->last_damage_time = MLV_get_time();

    if(entity->type == PLAYER) push_entity(game, entity);

    if(life->hp <= 0) {
        life->hp = 0;
        remove_entity(game, entity);
        return 1;
    } 

    return remove_random_bonus(game, entity);
}

int remove_random_bonus(Game* game, Entity *entity) {
    SpaceShip *ship = get_spaceship(entity);
    int bonus_count = count_bonus(entity);
    BonusLink *current;
    int i = 0;
    int random = MLV_get_random_integer(0, bonus_count);

    if(ship == NULL) return 0;
    if(bonus_count == 0) return 0;

    for(current = ship->bonus; current != NULL; current = current->next) {
        if(random == i) {
            remove_bonus(game, entity, current->bonus);
            return 1;
        }
        i++;
    }
    return 0;
}

void disable_shield(Game *game, Entity *entity) {
    Life *life;
    if(     entity->type == PLAYER) life = &((Player*)entity->parent)->ship->life;
    else if(entity->type == ENNEMY) life = &((Ennemy*)entity->parent)->ship->life;
    else return;

    /* Remove shield from bonuses */
    remove_bonus(game, entity, get_bonus(entity, 'S'));

    remove_child(game, entity, life->shield_entity);
    life->shield = 0;
}

Bonus *get_bonus(Entity *entity, char type) {
    BonusLink *current;
    SpaceShip *ship = get_spaceship(entity);
    if(ship == NULL) return NULL;

    for(current = ship->bonus; current != NULL; current = current->next) {
        if(current->bonus->type == type) return current->bonus;
    }

    return NULL;
}

int enable_shield(Game *game, Entity *entity) {
    Life *life;
    if(     entity->type == PLAYER) life = &((Player*)entity->parent)->ship->life;
    else if(entity->type == ENNEMY) life = &((Ennemy*)entity->parent)->ship->life;
    else return 0;

    if(life->shield) return 0;

    life->shield_entity = create_entity(
        -entity->width * 0.1, -entity->height * 0.1,
        entity->width * 1.2, entity->height * 1.2,
        entity->speed->speed, entity->speed->update_speed,  
        init_animation_wrapper("resources/utils/shield-%d.png"),
        NULL, LABEL
    );
    add_child(entity, life->shield_entity);
    
    life->shield = 1;
    return 1;
}
