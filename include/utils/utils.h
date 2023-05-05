/**
 * @file utils.h
 * @author Max Ducoudré & Adam Mehdaoui
 * @brief Utils function of the program
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef UTILS_H
#define UTILS_H
/**
 * @brief Get the timestamp from the start of the program in milliseconds
 * 
 * @return Milliseconds from the start of the program
 */
long get_timestamp_ms();

/**
 * @brief Temporize the program to have a constant framerate
 * 
 * @param update_time the last time the program was updated
 * @param space_time the time between each update
 * @return 1 if the program should be updated, 0 otherwise
 */
int temporize(long *update_time, long space_time);

#endif