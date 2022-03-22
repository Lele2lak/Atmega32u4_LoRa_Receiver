/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */

#include "lora_handling.hpp"

#include "led_handling.hpp"
#include <FreeRTOS.h>
#include "task.h"
#include <Arduino.h>
#include "internal.hpp"
#include <RH_RF95.h>
#include "main.hpp"
#include "network.hpp"

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
    while(!rf95.setFrequency(LORA_FREQ));

    /* Set the transmission power */
    rf95.setTxPower(13);

}

void lora_change_power(uint8_t tx_power) {
    rf95.setTxPower(tx_power);
}

void lora_catch_up_message(void* taskparameters) {

    other_tasks = (struct tasks*) taskparameters;
    uint8_t destination;
    enum action action_to_perform;
    while(1) {
        /* Check if a message was received */
        if(rf95.available()) {

            Serial.println("[LORA] - Message reçu");

            /* Write the message into a message type buffer */
            if(!rf95.recv(buff_message,&buff_message_len)) {
                Serial.println("[LORA] - Recopie du message impossible");
            }
            else {
                /*If the message is not for us, drop it*/
                if( ((((struct message_t*) buff_message)->destination_id) != internal_config_get_self_id()) || 
                    ((((struct message_t*) buff_message)->destination_id) != UNIVERSAL_CALL)) {
                    memset(&buff_message,0,buff_message_len);
                    Serial.println("[LORA] - ID not matching, message dropped");
                }
                else {
                    /*Send an acknowledge back*/
                    destination = ((struct message_t*) buff_message)->source_id;
                    lora_send_ack(ACK_OK, destination);
                    Serial.println("[LORA] - ID matching, sending acknowledge back");

                    /*Treat the message received*/
                    if( ((struct message_t*) buff_message)->data_u.ack == ACK_ATTENDANCE) {
                        lora_handling_attendance_received(buff_message);
                    }
                    else {
                        lora_handling_message_received(buff_message);
                    }
                }
            }
        }
    }
}

void lora_send(uint8_t* buff, size_t size) {
    uint8_t* buffer_to_send = buff;
    rf95.send(buffer_to_send, size);
    rf95.waitPacketSent();
}

uint8_t lora_send_ack(e_ack_type ack, uint8_t destination) {
    struct message_t ack_message;
    ack_message.message_action = ACTION_ACK;
    ack_message.data_u.ack = ack;
    ack_message.source_id = internal_config_get_self_id();
    lora_send((uint8_t*)&ack_message,sizeof(ack_message));

}

int lora_send_light_inf(int index) {
    struct message_t inf_message;
    inf_message.destination_id = T_MESH_POINT[index].id;
    inf_message.source_id = internal_config_get_self_id();
    inf_message.message_action = ACTION_INFOS;
    inf_message.data_u.infos.mesh_id = T_MESH_POINT[index].mesh_id;
    inf_message.data_u.infos.status = T_MESH_POINT[index].status;
    inf_message.data_u.infos.type = T_MESH_POINT[index].type;

    lora_send((uint8_t*)&inf_message, sizeof(inf_message));
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

    case ACTION_RESET: {
        internal_reset();
        break;
    }

    case ACTION_RQST_ATTENDANCE_ACK: {
        /*Send an acknowledge to the destination light*/
        lora_send_ack(ACK_ATTENDANCE, message_recv->source_id);
        break;
    }
    case ACTION_ACK: {
        
        switch (message_recv->data_u.ack)
        {   /*A light's close here, adding it to the mesh and sending it back its infos*/
            case ACK_ATTENDANCE:{
                uint32_t source_id = message_recv->source_id;
                uint8_t source_status = 0;
                uint8_t source_type = 0;
                int ret;
                
                ret = network_add_a_point(source_id, source_status, source_type);

                if(ret < 0) {
                    /*Mesh tab is full, throw an error*/
                }
                else {
                    /*After adding a light to a mesh, sending it back its infos */
                    lora_send_light_inf(ret);
                }
            }
            break;
        
        default:
            break;
        }
        break;
    }
    case ACTION_INFOS: {
        /*Write into internal config the new parameters given by the mesh node*/
        internal_config_set_light_type(message_recv->data_u.infos.type);
        internal_config_set_light_status(message_recv->data_u.infos.status);
        internal_config_set_light_mesh_id(message_recv->data_u.infos.mesh_id);
        
        break;
    }
    default: {
        Serial.println("[DEBUG] - Default Case");
        break;
    }
    }  
}

void lora_handling_attendance_received(uint8_t* nuff_message) {

}
/*
 *TODO
 *Synchroniser les clocks (calculer le délai de propagation)
 */