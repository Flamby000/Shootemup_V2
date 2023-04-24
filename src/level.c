#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/bonus.h"
#include "../include/ennemy.h"
#include "../include/level.h"

Level* create_level(char* level_file) {
    char line[200];
    int line_size;
    Level *level = malloc(sizeof(Level));
    FILE *file = fopen(level_file, "r");
    if(file == NULL) {
        printf("Error : Cannot open file %s", level_file);
        return NULL;
    }
    level->last_line_time = 0;
    level->line_cooldown = 3000;
    level->last_wave_time = 0;
    level->wave_cooldown = 5000;
    level->nb_wave = 0;
    level->current_wave = 0;

    level->waves = NULL;

    while(fscanf(file, "%s", line) != EOF) {
        if(line[0] == '#') continue;
        if(line[0] == '=') {
            line_size = strlen(line);
            level->nb_wave++;
            level->waves = realloc(level->waves, level->nb_wave * sizeof(Wave));
        } else {
            level->waves[level->nb_wave - 1].nb_line++;
            level->waves[level->nb_wave - 1].current_line = 0;
            level->waves[level->nb_wave - 1].object_lines = realloc(level->waves[level->nb_wave - 1].object_lines, level->waves[level->nb_wave - 1].nb_line * sizeof(char*));
            level->waves[level->nb_wave - 1].object_lines[level->waves[level->nb_wave - 1].nb_line - 1] = malloc(line_size * sizeof(char));
            strcpy(level->waves[level->nb_wave - 1].object_lines[level->waves[level->nb_wave - 1].nb_line - 1], line);
        }
    }
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
                create_bonus(game, object_line[i], (settings->win_width / line_size) * i + (settings->win_width / line_size) / 2);
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

void update_level(Game* game, Level* level, int infinite) {

    if(!infinite && level->current_wave == level->nb_wave) return;
    else if(infinite && level->current_wave == level->nb_wave) {
        level->current_wave = 0;
        level->last_wave_time = MLV_get_time();
    } 

    if(MLV_get_time() - level->last_line_time > level->line_cooldown) {
        level->last_line_time = MLV_get_time();
        create_object_line(game, level->waves[level->current_wave].object_lines[level->waves[level->current_wave].current_line]);

        level->waves[level->current_wave].current_line++;

        if(level->waves[level->current_wave].current_line == level->waves[level->current_wave].nb_line) {
            level->waves[level->current_wave].current_line = 0;
            level->current_wave++;
            level->last_wave_time = MLV_get_time();
        }
    }
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

void print_level(Level* level) {
    int i, j;
    for(i = 0; i < level->nb_wave; i++) {
        printf("Wave %d\n", i);
        for(j = 0; j < level->waves[i].nb_line; j++) {
            printf("%s\n", level->waves[i].object_lines[j]);
        }
    }
}