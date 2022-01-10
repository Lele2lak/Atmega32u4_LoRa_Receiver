/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation est réglementé par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
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