/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */

#ifndef INTERNAL_H
#define INTERNAL_H

#include <stdint.h>

#define POINT   0
#define NODE    1
#define BATPORT A2
#define UNIVERSAL_CALL 0

struct report_t {
    float battery_level;
    float battery_current;
    uint16_t time_since_launched;
};

enum status {
    ERROR               = 100,          /* Global error */
    BATTERY_ERROR       = 101,          /* Specific error due to battery level */
    LED_ERROR           = 102,          /* Specific error due to LED state */
    TEMPERATURE_ERROR   = 103,          /* Specific error due to temperature */
    OK                  = 104           /* OK status */
};

/*
 * Define wether a light is a point or a node.
 */
void internal_config_set_light_type(uint8_t type);

/*
 * Get the light id.
 */
uint8_t internal_config_get_self_id(void);

/*
 * Get the light type.
 */
uint8_t internal_config_get_light_type(void);

/*
 * Reset the light software
 */
void internal_reset(void);
/*
 * Launch an initial config.
 */
uint8_t internal_launch_config(void* parameters);

/*
 * Method to get the functional report befor turning ON.
 */
uint8_t internal_report(void);

/*
 * Method to get the detailed state report of the device.
 */
struct report_t internal_detailed_report(void);

#endif /*INTERNAL_H*/