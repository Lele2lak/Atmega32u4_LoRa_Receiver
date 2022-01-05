/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation est réglementé par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
 */

#ifndef INTERNAL_H
#define INTERNAL_H

#include <stdint.h>

#define POINT   0
#define NODE    1
#define BATPORT A9

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