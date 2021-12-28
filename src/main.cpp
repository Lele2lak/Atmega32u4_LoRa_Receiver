#include "main.h"
#include <Arduino.h>
#include "led_handling.h"
#include <FreeRTOS.h>
#include "task.h"

extern "C" {
#include "lora_handling.h"
}

#include "internal.hpp"
#include <SPI.h>

/*
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
 // Serial.begin(19200);
  
}
 
// the loop function runs over and over again forever
void loop() {
  //digitalWrite(13, HIGH);
  
  //digitalWrite(9, HIGH); // turn the LED on (HIGH is the voltage level)

  digitalWrite(BLUE, HIGH);
  digitalWrite(13,HIGH); //DEBUG LED
  delay(100);              
  
  digitalWrite(BLUE, LOW);
  //digitalWrite(9,LOW);
  //digitalWrite(10, LOW);// turn the LED off by making the voltage LOW

  digitalWrite(13, LOW);
  delay(4000); 

 // Serial.println("TEST");
  int voltage = analogRead(A0);
//  Serial.println(voltage); 
  if (  (465 < voltage) && (voltage < 645))
    {
      digitalWrite(13, HIGH);
    } 
  else { digitalWrite(13, LOW);}          
}
*/

void setup() {

}

void loop() {

  pinMode(13, OUTPUT);
  Serial.begin(115200);

  internal_launch_config(NULL);

  TaskHandle_t internal_config_launch_handle = NULL;

  xTaskCreate(internal_launch_config,
              "internal_launch_config",
              configMINIMAL_STACK_SIZE,
              NULL,
              1,
              &internal_config_launch_handle
              );


  vTaskStartScheduler();
}
