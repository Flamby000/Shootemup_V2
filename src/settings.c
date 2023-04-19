#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"



void load_settings() {
    settings = malloc(sizeof(Settings));
    settings->win_width = WIN_WIDTH;
    settings->win_height = WIN_HEIGHT;        
}

