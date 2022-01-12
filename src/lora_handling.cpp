/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation sont réglementées par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
 */

#include "lora_handling.hpp"

#include "led_handling.hpp"
#include <FreeRTOS.h>
#include "task.h"
#include <Arduino.h>
#include "internal.hpp"
#include <RH_RF95.h>
#include "main.hpp"

static message_t message_received;
static RH_RF95 rf95(RFM95_CS, RFM95_INT);

static uint8_t buff_message[sizeof(message_t)];
static uint8_t buff_message_len = sizeof(message_t);

static struct tasks* other_tasks;

void lora_default_config(void* taskparameters) {
    
}

void lora_init() {

    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    while(!rf95.init());
    while(!rf95.setFrequency(915.0));

    /* Set the transmission power */
    rf95.setTxPower(13);

}

void lora_catch_up_message(void* taskparameters) {

    other_tasks = (struct tasks*) taskparameters;
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

void lora_send(uint8_t* buff, size_t size) {
    uint8_t* buffer_to_send = buff;
    rf95.send(buffer_to_send, size);
    rf95.waitPacketSent();
}

void lora_handling_message_received(uint8_t* message) {

    struct message_t* message_recv = (struct message_t*)message;

    switch (message_recv->message_action)
    {
    case ACTION_REPORT_REQUEST: {
        Serial.println("[DEBUG] - Report Request");
        //internal_report();
        
        struct report_t report = internal_detailed_report();

        struct message_t message_to_send;
        message_to_send.message_action = ACTION_REPORT_SEND;
        
        message_to_send.data_u.report = report;

        struct report_t report_test = (struct report_t)message_to_send.data_u.report;

        Serial.print("[LORA] - Battery lvl: ");
        Serial.println(report_test.battery_level);

        lora_send((uint8_t*)&message_to_send,sizeof(message_to_send));

        break;
    }
    
    case ACTION_OPERATIONAL_TEST: {
        /* TODO */
        Serial.println("[DEBUG] - Operational Test");
        break;
    }

    case ACTION_ON: {
        /* TODO */
        Serial.println("Turn ON the LED");
        led_white_on();
        break;
    }

    case ACTION_OFF: {
        /* TODO */
        Serial.println("Turn OFF the LED");
        led_white_off();
        break;
    }
    
    case ACTION_GLITTER_ET: {
        /* TODO */
        uint8_t led = WHITE_LED;
        
        Serial.println("[DEBUG] - Glitter check");

        if( (other_tasks != NULL) && (uxTaskPriorityGet(other_tasks->led_glittering_et_Task) != 3)) {
            vTaskPrioritySet(other_tasks->led_glittering_et_Task,3);
        }
        break;
    }
    
    case ACTION_GLITTER_ET_OFF: {
        Serial.println("[DEBUG] - Glitter OFF");

        if((other_tasks->led_glittering_et_Task != NULL) && (uxTaskPriorityGet(other_tasks->led_glittering_et_Task) == 3)) {
            vTaskPrioritySet(other_tasks->led_glittering_et_Task,0);
        }
        else {
            Serial.println("[Task] - Led Glittering Task isn't running.");
        }
        break;
    }

    default: {
        Serial.println("[DEBUG] - Default Case");
        break;
    }
    }  
}