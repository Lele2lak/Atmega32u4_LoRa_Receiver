/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */
#include <Arduino.h>


#include "main.hpp"


#include <FreeRTOS.h>
#include "task.h"
#include "lora_handling.hpp"
#include "led_handling.hpp"

#include "internal.hpp"
#include <SPI.h>


void setup() {
  
  Serial.begin(9600);
  delay(100);

  digitalWrite(13,HIGH);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  TaskHandle_t lora_catch_up_task = NULL;

  struct tasks tasklist;


  if(internal_launch_config(NULL) == 0) {
    Serial.println("[SYSTEM] - Config load OK");
  } else {
    Serial.println("[DEBUG] - Error while loading config");
    /*Restarting*/
    internal_reset();
  }
  lora_init();



  xTaskCreate(led_glittering_et,
              "led_glitterring_et",
              configMINIMAL_STACK_SIZE,
              NULL,
              0,
              &(tasklist.led_glittering_et_Task)
              );

  xTaskCreate(lora_catch_up_message,
              "lora_catch_up_message",
              configMINIMAL_STACK_SIZE,
              (void *)&tasklist,
              2,
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
