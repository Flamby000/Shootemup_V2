#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/game.h"
#include "../include/bonus.h"
#include "../include/ennemy.h"
#include "../include/level.h"

Level* create_level(char* level_file) {
    char line[200];
    int line_size;
    int boss_id = 'X';
    int i;
    Level *level = malloc(sizeof(Level));
    FILE *file = fopen(level_file, "r");
    if(file == NULL) {
        printf("Error : Cannot open file %s", level_file);
        return NULL;
    }

    level->level_file = level_file;
    level->last_line_time = 0;
    level->line_cooldown = settings->difficulty->waves_spawn_cooldown;
    level->last_wave_time = 0;
    level->wave_cooldown = settings->difficulty->waves_spawn_cooldown*1.5;
    level->nb_wave = 0;
    level->current_wave = 0;

    level->waves = NULL;

    while(fscanf(file, "%s", line) != EOF) {
        if(line[0] == '#') continue;
        if(line[0] == '=' || line[0] == '-') {
            line_size = strlen(line);
            level->nb_wave++;
            level->waves = realloc(level->waves, level->nb_wave * sizeof(Wave));
            level->waves[level->nb_wave - 1].nb_line = 0;
            level->waves[level->nb_wave - 1].object_lines = NULL;
            if(line[0] == '=') boss_id = 'X';
            else {
                for(i = 0; line[i] != '\0'; i++){
                    if(line[i] != '-') {
                        boss_id = line[i];
                        break;
                    }
                } 
            }
        } else {

            level->waves[level->nb_wave - 1].nb_line++;
            level->waves[level->nb_wave - 1].current_line = 0;
            level->waves[level->nb_wave - 1].object_lines = realloc(level->waves[level->nb_wave - 1].object_lines, level->waves[level->nb_wave - 1].nb_line * sizeof(char*));
            level->waves[level->nb_wave - 1].object_lines[level->waves[level->nb_wave - 1].nb_line - 1] = malloc(line_size * sizeof(char));
            level->waves[level->nb_wave - 1].boss_id = boss_id;
            level->waves[level->nb_wave - 1].boss = NULL;
            strcpy(level->waves[level->nb_wave - 1].object_lines[level->waves[level->nb_wave - 1].nb_line - 1], line);
        }
    }

    fclose(file);
    return level;
}

void create_object_line(Game *game, char* object_line) {
    int line_size = strlen(object_line);
    int i;

    for(i = 0; i < line_size; i++) {
        switch(get_object_type(object_line[i])) {
            case ENNEMY:
                create_ennemy(game, object_line[i], (settings->win_width / line_size) * i + (settings->win_width / line_size) / 2);
                break;
            case BONUS :
                if(object_line[i] == 'R') create_random_bonus(game, (settings->win_width / line_size) * i + (settings->win_width / line_size) / 2);
                else create_bonus(game, object_line[i], (settings->win_width / line_size) * i + (settings->win_width / line_size) / 2);
                break;
            default :
                break;
        }    
    }
}

EntityType get_object_type(char object) {
    if(object == 'X') return NONE;
    else if('0' <= object && object <= '9') return ENNEMY;
    else return BONUS;
}

void set_level(Game* game, char* level_file) {
    if(game->level != NULL) {
        free_level(game->level);
        game->level = NULL;
    }
    if(level_file == NULL) {
        game->level = NULL;
    } else {
        game->level = create_level(level_file);
    }
}

int update_level(Game* game, Level* level, int infinite) {
    if(level == NULL) return 1;

    if(!infinite 
        && (!(level->waves[level->current_wave].boss_id == 'X')) 
        && boss_kill_count(game) != 0) 
        return 1;

    if(!infinite && level->current_wave == level->nb_wave
    && level->waves[level->current_wave].current_line == level->waves[level->current_wave].nb_line) return 1;

    else if(infinite && level->current_wave == level->nb_wave) {
        level->current_wave = 0;
        level->last_wave_time = MLV_get_time();
    } 

    if(MLV_get_time() - level->last_line_time > level->line_cooldown) {
        level->last_line_time = MLV_get_time();
        if(level->waves[level->current_wave].boss_id == 'X') {
            create_object_line(game, level->waves[level->current_wave].object_lines[level->waves[level->current_wave].current_line]);

            level->waves[level->current_wave].current_line++;

            if(level->waves[level->current_wave].current_line == level->waves[level->current_wave].nb_line) {
                if(infinite) level->waves[level->current_wave].current_line = 0;
                level->current_wave++;
                level->last_wave_time = MLV_get_time();
            }
        } else {            

            if(!is_boss_alive(game)) {
                level->waves[level->current_wave].boss = create_ennemy(game, level->waves[level->current_wave].boss_id, settings->win_width / 2);
            } else {
                create_shoot_line(game, level->waves[level->current_wave].boss->entity, level->waves[level->current_wave].object_lines[level->waves[level->current_wave].current_line]);
                level->waves[level->current_wave].current_line++;
                if(level->waves[level->current_wave].current_line == level->waves[level->current_wave].nb_line) {
                    level->waves[level->current_wave].current_line = 0;
                }
            }

            /*level->current_wave++;*/
        }
    }
    return 0;
}


void free_level(Level* level) {
    int i, j;
    for(i = 0; i < level->nb_wave; i++) {
        for(j = 0; j < level->waves[i].nb_line; j++) {
            free(level->waves[i].object_lines[j]);
        }
        free(level->waves[i].object_lines);
    }
    free(level->waves);
    free(level);
}