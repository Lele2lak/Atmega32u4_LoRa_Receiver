#ifndef INTERNAL_H
#define INTERNAL_H

#include <stdint.h>

#define POINT   0
#define NODE    1

/*
 * Define wether a light is a point or a node.
 */
void internal_config_set_light_type(uint8_t type);

/*
 * Get the light type.
 */
uint8_t internal_config_get_light_type(void);

/*
 * Launch an initial config.
 */
void internal_launch_config(void* parameters);

/*
 * Method to get the light battery level.
 */
void internal_report(void);

#endif /*INTERNAL_H*/