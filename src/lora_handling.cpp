
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
static uint8_t buff_message_len = sizeof(buff_message);

void lora_default_config(void* taskparameters) {
    
}

void lora_rcv_init() {

    /* Debug LED */
    digitalWrite(12,HIGH);

    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    while(!rf95.init());

    while(!rf95.setFrequency(915.0));

    /* Debug LED */
    digitalWrite(12,LOW);

}

void lora_catch_up_message(void* taskparameters) {
    while(1) {
        /* Check if a message was received */
        
        //digitalWrite(10,HIGH);

        if(rf95.available()) {
            digitalWrite(12,HIGH);
            vTaskDelay(100 / portTICK_PERIOD_MS);

            /* Write this message into a message type buffer */
            if(!rf95.recv(buff_message,&buff_message_len)) {
                digitalWrite(11,HIGH);
                vTaskDelay(100 / portTICK_PERIOD_MS);
                digitalWrite(11,LOW);
            }

            digitalWrite(12,LOW);
        }
        else {
           // digitalWrite(10,LOW);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

    }

}

void lora_handling_message_received(void* taskparameters) {

    while(1)
    {
        struct message_t message_recv;
        
        switch (message_recv.message_action)
        {
        case ACTION_REPORT_REQUEST:
            internal_report();
            break;
        
        case ACTION_OPERATIONAL_TEST:
            /* TODO */
            break;

        case ACTION_ON:
            /* TODO */
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
}