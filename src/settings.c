#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"
#include "../include/frame.h"

void load_settings() {
    unsigned int width, height;
    MLV_get_desktop_size(&width, &height);


    width -= width/25;
    height -= height/25;


    settings = malloc(sizeof(Settings));
    settings->win_width = width;
    settings->win_height = height;

}

