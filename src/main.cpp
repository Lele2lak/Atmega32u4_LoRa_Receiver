/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation est réglementé par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
 */
#include <Arduino.h>

extern "C" {
#include "led_handling.h"
#include "main.h"
}

#include <FreeRTOS.h>
#include "task.h"
#include "lora_handling.hpp"

#include "internal.hpp"
#include <SPI.h>


void setup() {
  
  Serial.begin(9600);
  delay(100);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  TaskHandle_t lora_catch_up_task = NULL;

  lora_rcv_init();

  xTaskCreate(lora_catch_up_message,
              "lora_catch_up_message",
              configMINIMAL_STACK_SIZE,
              NULL,
              1,
              &lora_catch_up_task
              );
  
  vTaskStartScheduler();
  
}


void loop() {
  /*
   * The loop method has no utility in so much that we use the FreeRTOS scheduler.
   * Arduino still needs it.
   * TODO: Find a way to delete it (rewrite the digitalwrite arduino library to delete Arduino.h).
   */
  
}
