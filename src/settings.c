#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"
#include "../include/settings.h"

void load_settings() {
    unsigned int width, height;
    MLV_get_desktop_size(&width, &height);
    width -= width/25;
    height -= height/10;
    width = 800;
    height = 600;

    settings = malloc(sizeof(Settings));
    settings->win_width = width;
    settings->win_height = height;
    settings->infinite_mode = 0;
    settings->coop_mode = 0;
}

