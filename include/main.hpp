/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */

#ifndef MAIN_H
#define MAIN_H

#include <FreeRTOS.h>
#include "task.h"

struct tasks {
  TaskHandle_t led_glittering_et_Task;
};

#endif /*MAIN_H*/