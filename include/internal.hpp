/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation sont réglementées par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
 */

#ifndef INTERNAL_H
#define INTERNAL_H

#include <stdint.h>

#define POINT   0
#define NODE    1
#define BATPORT A2

struct report_t {
    uint32_t battery_level;
    uint16_t time_since_launched;
};

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
 * Method to get the functional report befor turning ON.
 */
void internal_report(void);

/*
 * Method to get the detailed state report of the device.
 */
struct report_t internal_detailed_report(void);

#endif /*INTERNAL_H*/