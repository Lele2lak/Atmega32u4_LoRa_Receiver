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

int main() {
  
  init();
  setup();

  //digitalWrite(11,HIGH);
  //Serial.begin(115200);
  
  lora_rcv_init();
  //internal_launch_config(NULL);
  //internal_report();

  TaskHandle_t internal_config_launch_handle = NULL;
  TaskHandle_t lora_catch_up_task = NULL;

  xTaskCreate(lora_catch_up_message,
              "lora_catch_up_message",
              configMINIMAL_STACK_SIZE,
              NULL,
              1,
              &lora_catch_up_task
              );
  
  /*xTaskCreate(internal_launch_config,
              "internal_launch_config",
              configMINIMAL_STACK_SIZE,
              NULL,
              1,
              &internal_config_launch_handle
              );
  */

  vTaskStartScheduler();

}

void setup() {
  /* Serial.begin(9600);
   while (!Serial) {
     //delay(1);
   }*/

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

/*void loop() {

  
}*/
