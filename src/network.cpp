/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */
#include "network.hpp"
#include "lora_handling.hpp"
#include <FreeRTOS.h>
#include "task.h"
#include <RH_RF95.h>
#include "semphr.h"

static SemaphoreHandle_t mutex;
//#define TO_ASK_ATTENDANCE 2000/portTICK_PERIOD_MS

int start_mesh_initialisation(void) {

    uint8_t power;
    uint8_t ret;

    ret = scan_lights(power);

    if(ret != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int network_initialize_close_points(void) {

}

int scan_lights(uint8_t tx_power) {

    /*Reconfigure the transmition power*/
    lora_change_power(tx_power);

    /*Send a request message to get closest lights id*/
    message_t request;
    request.source_id = internal_config_get_self_id();
    
    if(request.source_id){
        return EXIT_FAILURE;
    }
    
    request.destination_id = UNIVERSAL_CALL;
    request.message_action = ACTION_RQST_ATTENDANCE_ACK;

    lora_send((uint8_t*) &request, sizeof(request));

    return EXIT_SUCCESS;
}

int network_add_a_point(uint32_t id, uint8_t status, uint8_t type) {
    uint8_t index;
    uint8_t placed = -1;

    for(index = 0; ((index < POINT_NB_PER_MESH) && (placed < 0)); index++ )
    {
        if(!T_MESH_POINT[index].id) {
            T_MESH_POINT[index].id = id;
            T_MESH_POINT[index].status = status;
            T_MESH_POINT[index].type = type;
            T_MESH_POINT[index].mesh_id = index;
            placed = index;
        }
    }

    /*Returns 1 if error*/
    return placed;
}

/*TODO: Fonction d'init network pour organiser tout ça.
    -> start mesh init
    -> Réception des ack, attribution des id et renvoi aux points
    -> Une fois le tableau plein,la maille est constituée
    -> A définir: lancement du network init à la réception d'un message ou au démarrage ??
*/