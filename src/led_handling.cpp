/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */

#include "led_handling.hpp"
#include <Arduino.h>

#include <FreeRTOS.h>
#include "task.h"


void led_white_on() {
    digitalWrite(WHITE_LED, HIGH);
}

void led_white_off() {
    digitalWrite(WHITE_LED, LOW);
}

void led_glittering_et(void* taskparameters) {
    uint8_t LED = *(uint8_t*) taskparameters;
    Serial.println("[DEBUG] - Check LED GLITTERING");

    while(1) {
        digitalWrite(12, HIGH);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        digitalWrite(12, LOW);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}