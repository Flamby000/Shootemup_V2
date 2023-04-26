
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long get_timestamp_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

int temporize(long *update_time, long space_time) {
    long now_time = get_timestamp_ms();
    if((now_time- (*update_time)) > space_time) {
        *update_time = get_timestamp_ms();
        return 0;
    }    
    return 1;
}
