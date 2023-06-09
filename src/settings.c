#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/interface/frame.h"
#include "../include/settings.h"


void load_settings() {
    unsigned int width, height;
    Difficulty *difficulty = malloc(sizeof(Difficulty));
    FILE *file;
    char key[200];
    char value[200];
    char line[400];

    MLV_init_audio();
    MLV_get_desktop_size(&width, &height);
    width -= width/25;
    height -= height/10;
    /*width = 1200;
    height = 800;
    */
    settings = malloc(sizeof(Settings));
    settings->win_width = width;
    settings->win_height = height;
    settings->infinite_mode = 0;
    settings->coop_mode = 0;
    settings->selected_level = 1;
    
    file = fopen(SETTINGS_DATA_PATH, "r");
    if(file == NULL) {
        printf("Error : Cannot open file %s\n", SETTINGS_DATA_PATH);
        return;
    }    

    
    while(fscanf(file, "%s", line) != EOF) {
        if(strchr(line, ':') != NULL) {
            char *token = strtok(line, ":");
            strcpy(key, token);
            token = strtok(NULL, ":");
            strcpy(value, token);

            if(strcmp(key, "volume") == 0) settings->volume = atoi(value);
            else if(strcmp(key, "coop_mode") == 0) settings->coop_mode = strcmp(value, "true") == 0 ? 1 : 0; 
            else if(strcmp(key, "waves_spawn_cooldown") == 0)  difficulty->waves_spawn_cooldown = atoi(value);    
            else if(strcmp(key, "ennemy_life_multiplicator") == 0) difficulty->ennemy_life_multiplicator = atoi(value);
            else if(strcmp(key, "ennemy_shoot_cooldown_multiplicator") == 0) difficulty->ennemy_shoot_cooldown_multiplicator = atoi(value);
            else if(strcmp(key, "ennemy_speed_multiplicator") == 0) difficulty->ennemy_speed_multiplicator = atoi(value);
            else if(strcmp(key, "player_life") == 0) difficulty->player_life = atoi(value);
            else if(strcmp(key, "player_shoot_cooldown") == 0) difficulty->player_shoot_cooldown = atoi(value);
            else if(strcmp(key, "player_super_shoot_cooldown") == 0) difficulty->player_super_shoot_cooldown = atoi(value);
            else if(strcmp(key, "player_speed") == 0) difficulty->player_speed = atoi(value);
            else if(strcmp(key, "player_stamina") == 0) difficulty->player_stamina = atoi(value);
            }
        }

    settings->difficulty = difficulty;

    settings->music = MLV_load_music("resources/sound/music.mp3");
    
    if(settings->music == NULL) {
        fprintf(stderr, "Erreur: la musique n'a pas été chargé\n");
        exit(EXIT_FAILURE);
    }

    settings->click_sound = MLV_load_sound("resources/sound/Highlight.wav");

    if(settings->click_sound == NULL) {
        fprintf(stderr, "Erreur: le click sound n'a pas été chargé\n");
        exit(EXIT_FAILURE);
    }

    settings->explosion_sound = MLV_load_sound("resources/sound/Explosion.wav");

    if(settings->explosion_sound == NULL) {
        fprintf(stderr, "Erreur: le son d'explosion n'a pas été chargé\n");
        exit(EXIT_FAILURE);
    }
}

void free_settings() {
    free(settings->difficulty);
    free(settings->music);
    free(settings->explosion_sound);
    free(settings->click_sound);
    free(settings);
}

void save_settings() {
    FILE *file;
    file = fopen(SETTINGS_DATA_PATH, "w");
    if(file == NULL) {
        printf("Error : Cannot open file %s\n", SETTINGS_DATA_PATH);
        return;
    }    

    fprintf(file, "volume:%d\n", settings->volume);
    fprintf(file, "coop_mode:%s\n", settings->coop_mode == 1 ? "true" : "false");
    fprintf(file, "waves_spawn_cooldown:%d\n", settings->difficulty->waves_spawn_cooldown);
    fprintf(file, "ennemy_life_multiplicator:%d\n", settings->difficulty->ennemy_life_multiplicator);
    fprintf(file, "ennemy_shoot_cooldown_multiplicator:%d\n", settings->difficulty->ennemy_shoot_cooldown_multiplicator);
    fprintf(file, "ennemy_speed_multiplicator:%d\n", settings->difficulty->ennemy_speed_multiplicator);
    fprintf(file, "player_life:%d\n", settings->difficulty->player_life);
    fprintf(file, "player_shoot_cooldown:%d\n", settings->difficulty->player_shoot_cooldown);
    fprintf(file, "player_super_shoot_cooldown:%d\n", settings->difficulty->player_super_shoot_cooldown);
    fprintf(file, "player_speed:%d\n", settings->difficulty->player_speed);
    fprintf(file, "player_stamina:%d\n", settings->difficulty->player_stamina);
    fclose(file);

}