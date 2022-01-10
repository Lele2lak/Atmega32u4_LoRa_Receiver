/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation est réglementé par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
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