/* This file aims to define the shape of exchanged message between the devices
 * When a message is received, it is translated here.
 */

#ifndef LORA_HANDLING_H
#define LORA_HANDLING_H

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
    uint8_t* data;
};

void lora_handling_message_received(void* parameters);


#endif /*LORA_HANDLING_H*/