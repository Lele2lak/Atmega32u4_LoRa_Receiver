/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation sont réglementées par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
 */

#ifndef MAIN_H
#define MAIN_H

#include <FreeRTOS.h>
#include "task.h"

struct tasks {
  TaskHandle_t led_glittering_et_Task;
};

#endif /*MAIN_H*/