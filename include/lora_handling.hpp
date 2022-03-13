/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */

/* 
 * This file aims to define the shape of exchanged message between the devices
 * When a message is received, it is translated here.
 */

#ifndef LORA_HANDLING_H
#define LORA_HANDLING_H

#include <RH_RF95.h>
#include "internal.hpp"

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

/*Time between two message when no aknowledge is received*/
#define TO_SEND_MESSAGE 100

enum color {
    RED,
    GREEN,
    BLUE,
    WHITE       /*Possibilite de preciser directement la chaleur du blanc voulu*/
};

enum action {
    ACTION_GLITTER_ET,              /*Faire scintiller la lampe selon la seq de la Tour Eiffel*/
    ACTION_GLITTER_ET_OFF,          /*Arreter la sequence de scintillement Tour Eiffel*/
    ACTION_GLITTER_SEQ,             /*Transmettre une sequence de scintillement specifique + couleur */
    ACTION_OPERATIONAL_TEST,        /*Envoyer une seq de test*/
    ACTION_ON,                      /*Allumer la lampe*/
    ACTION_OFF,                     /*L'eteindre*/
    ACTION_REPORT_REQUEST,          /*Demander un rapport d'etat*/
    ACTION_REPORT_RECONFIG,         /*Reconfigurer selon le rapport d'etat*/
    ACTION_REPORT_SEND,             /*Envoie d'un message de rapport*/
    ACTION_ACK,
    ACTION_RESET
};

/*Enum of different acknowledge types*/
enum e_ack_type {
    ACK_OK,
    ACK_KO
};

/* 
 * Definition de la forme generale d'un message reçu par une autre lampe/station
 */
struct message_t {
    uint8_t source_id;   /*Source id*/
    uint8_t destination_id;
    enum action message_action;
    union data
    {
        struct report_t report;
        uint8_t report_status;
        e_ack_type ack;
        /* Possibilité de rajouter d'autres données */
    }data_u;
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
 * Init the LoRa Receive and Send processes
 */
void lora_init(void);

/*
 * Send a message using LoRa
 */
void lora_send(uint8_t* buff, size_t message_size);

/*
 * Send an acknowledge message
 */
uint8_t lora_send_ack(e_ack_type ack, enum action action_performed, uint8_t remote_addr);
#endif /*LORA_HANDLING_H*/