#include "internal.hpp"
#include <Arduino.h>
#include <FreeRTOS.h>
#include "task.h"

/*
 * Specifics parameters for each light.
 */
struct ctxt_t {
    uint8_t status;
    uint32_t id;
};

struct ctxt_t ctxt;

void internal_config_light_type(uint8_t type) {
    ctxt.status = type;
}

uint8_t internal_config_get_light_type(void) {
    return ctxt.status;
}

void internal_report(void) {

    uint8_t light_type = ctxt.status;
    uint8_t id = ctxt.id;
    uint32_t battery_lvl;

    /*
     *Check niveau de batterie < 574
     */
    battery_lvl = analogRead(BATPORT);
    Serial.println("Battery: ");
    Serial.print(battery_lvl);
    battery_lvl *=2;
    battery_lvl *= 3.3;
    battery_lvl /= 1024;
    Serial.print(battery_lvl);

    /*
     *Check LED
     */
    

    /*
     *Reponse KO
     */


    /*
     *Si c'esun un noeud => Renvoyer les ids des lampes KO
     */
    
}

void internal_launch_config(void* parameters) {
    
    ctxt.id = 0;
    ctxt.status = POINT;



}