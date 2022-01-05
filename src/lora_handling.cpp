/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation est réglementé par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
 */

#include "lora_handling.hpp"

#include "led_handling.h"
#include <FreeRTOS.h>
#include "task.h"
#include <Arduino.h>
#include "internal.hpp"
#include <RH_RF95.h>

static message_t message_received;
static RH_RF95 rf95(RFM95_CS, RFM95_INT);

static uint8_t buff_message[sizeof(message_t)];
static uint8_t buff_message_len = sizeof(message_t);

void lora_default_config(void* taskparameters) {
    
}

void lora_rcv_init() {

    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    while(!rf95.init());
    while(!rf95.setFrequency(915.0));

}

void lora_catch_up_message(void* taskparameters) {
    while(1) {
        /* Check if a message was received */
        if(rf95.available()) {

            Serial.println("[LORA] - Message reçu");

            /* Write the message into a message type buffer */
            if(!rf95.recv(buff_message,&buff_message_len)) {
                Serial.println("[LORA] - Recopie du message impossible");
            }
            else {
                lora_handling_message_received(buff_message);
            }
        }
    }
}

void lora_handling_message_received(uint8_t* message) {

    struct message_t* message_recv = (struct message_t*)message;
    
    switch (message_recv->message_action)
    {
    case ACTION_REPORT_REQUEST:
        internal_report();
        break;
    
    case ACTION_OPERATIONAL_TEST:
        /* TODO */
        break;

    case ACTION_ON:
        /* TODO */
        Serial.println("Turn ON the LED");
        break;

    case ACTION_OFF:
        /* TODO */
        break;
    
    case ACTION_GLITTER_ET:
        /* TODO */
        break;
    
    default:
        break;
    }  
}