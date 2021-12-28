#include "lora_handling.h"
#include "led_handling.h"
#include <FreeRTOS.h>
#include "task.h"
#include <Arduino.h>


void lora_handling_message_received(void* parameters) {

    while(1)
    {
        struct message_t message_recv;
        
        switch (message_recv.message_action)
        {
        case ACTION_REPORT_REQUEST:
            internal_report(NULL);
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