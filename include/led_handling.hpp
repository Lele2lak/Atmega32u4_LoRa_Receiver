/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */

#ifndef LED_HANDLING_H
#define LED_HANDLING_H


#define WHITE_LED 12
#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11

/*
 * Turn ON the white LED
 */
void led_white_on(void);

/*
 * Turn OFF the white LED
 */
void led_white_off(void);

/*
 * Glittering with Eiffel Tower template
 */
void led_glittering_et(void* taskparameters);

/*
 * Init the led module tasks
 */
void led_init(void);

#endif /*LED_HANDLING_H*/