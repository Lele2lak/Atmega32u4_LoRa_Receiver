/*
 * Ce code est la propriété des membres du projet DAZZ Illumination Tour Eiffel. Sa copie et son
 * utilisation est réglementé par la convention de partenariat établie conjointement entre l'
 * ECE Paris, la Société d'Exploitation de la Tour Eiffel, ainsi que les membres du projet.
 */

/* 
 * This file aims to define the shape of exchanged message between the devices
 * When a message is received, it is translated here.
 */

#ifndef LORA_HANDLING_H
#define LORA_HANDLING_H

#include <RH_RF95.h>

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

enum color {
    RED,
    GREEN,
    BLUE,
    WHITE       /*Possibilite de preciser directement la chaleur du blanc voulu*/
};

enum action {
    ACTION_GLITTER_ET,              /*Faire scintiller la lampe selon la seq de la Tour Eiffel*/
    ACTION_GLITTER_SEQ,             /*Transmettre une sequence de scintillement specifique + couleur */
    ACTION_OPERATIONAL_TEST,        /*Envoyer une seq de test*/
    ACTION_ON,                      /*Allumer la lampe*/
    ACTION_OFF,                     /*L'eteindre*/
    ACTION_REPORT_REQUEST,          /*Demander un rapport d'etat*/
    ACTION_REPORT_RECONFIG          /*Reconfigurer selon le rapport d'etat*/
};

enum status {
    BATTERY_STATUS,
    GENERAL_STATUS,
    LED_STATUS,
    TEMPERATURE_STATUS
};

/* 
 * Definition de la forme generale d'un message reçu par une autre lampe/station
 */
struct message_t {
    enum action message_action;
    uint8_t data[10];
};

/*
 * Defines action to perform when a message is received
 */
void lora_handling_message_received(uint8_t* message_buff);

/*
 * Implement a default config for Lora protocol
 */
void lora_default_config(void* taskparameters);

/*
 * Wait for a message to come
 */
void lora_catch_up_message(void* taskparameters);

/*
 * Init the LoRa Receive process.
 */
void lora_rcv_init();

#endif /*LORA_HANDLING_H*/