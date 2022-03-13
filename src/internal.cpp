/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */

#include "internal.hpp"
#include <Arduino.h>
#include <FreeRTOS.h>
#include "task.h"
#include <avr/wdt.h>

/*
 * Specifics parameters for each light.
 */
struct ctxt_t {
    uint8_t type;
    uint8_t status;
    uint32_t id;
};

struct ctxt_t ctxt;

void internal_config_light_type(uint8_t type) {
    ctxt.type = type;
}

uint8_t internal_config_get_self_id(void) {
    return ctxt.id;
}

uint8_t internal_config_get_light_type(void) {
    return ctxt.type;
}

uint8_t internal_report(void) {

    struct report_t report;
    uint8_t light_type = ctxt.type;
    uint8_t id = ctxt.id;
    float battery_lvl;

    /*
     *Check niveau de batterie < 3V
     */
    battery_lvl = analogRead(BATPORT);
    battery_lvl *=2;
    battery_lvl *= 3.3;
    battery_lvl /= 1024;
    
    if(battery_lvl < 3.1) ctxt.status = BATTERY_ERROR;
    else ctxt.status = OK;


    /*
     *Check LED
     */
    

    /*
     * Envoi de la reponse OK si tout est OK
     */
    if( light_type == POINT ) return ctxt.status;
    

    /*
     *Si c'esun un noeud => Renvoyer les ids des lampes KO
     */
    if( light_type == NODE ) {
        
    }
    
}

struct report_t internal_detailed_report(void) {
    struct report_t report;
    float battery_lvl, battery_current_value;


    battery_lvl = analogRead(BATPORT);
    //battery_lvl *=2;
    battery_lvl *= 3.3;
    battery_lvl /= 1024;

    report.battery_level = battery_lvl;

    /*Calculation of current. the *1000 is to have it in mA. */
    battery_current_value = ((battery_lvl / (float)1) / (float)220) * (float)1000;
    report.battery_current = battery_current_value;

    Serial.print("[DEBUG] - Battery Level: ");
    Serial.println(report.battery_level);

    return report;

}

void internal_reset(void) {
    
    Serial.println("[SYSTEM] - Restarting...");
    wdt_enable(WDTO_15MS);
    while(1) {}
}

uint8_t internal_launch_config(void* parameters) {
    
    ctxt.id = 0;
    ctxt.type = POINT;
    ctxt.id = 23;

    return 0;
}