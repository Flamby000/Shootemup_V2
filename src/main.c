#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <unistd.h>

#include <MLV/MLV_all.h>
#include "../include/struct.h"

#include "../include/frame.h"
#include "../include/animation.h"
#include "../include/entity.h"
#include "../include/game.h"

int quit = 0;

void sigint_handler(int sig) {
    quit = 1;
}

int main() {
    Game game;


    init_frame();
    init_game();

    signal(SIGINT, sigint_handler);
    
    while(!quit) {
        /* Print first entity*/
        print_entities(&game);

        update_frame(&game);
        update_game();
    }

    printf("Free memory\n");
    free_game(&game);
    free_frame();
    

    return EXIT_SUCCESS;
}