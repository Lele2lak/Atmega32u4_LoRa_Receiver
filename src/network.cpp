/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */
#include "network.hpp"
#include "lora_handling.hpp"
#include <RH_RF95.h>

int start_mesh_initialisation(void) {

    uint8_t power;

    scan_lights(power);

    return 0;
}

int scan_lights(uint8_t tx_power) {

    /*Reconfigure the transmition power*/
    lora_change_power(tx_power);

    /*Send a request message*/
    message_t request;
    request.source_id = internal_config_get_self_id();
    
    if(request.source_id){
        return -1;
    }
    
    request.destination_id = UNIVERSAL_CALL;
    request.message_action = ACTION_RQST_ACK;

    lora_send((uint8_t*) &request, sizeof(request));
}