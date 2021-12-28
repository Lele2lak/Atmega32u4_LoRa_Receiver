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
    
}

void internal_launch_config(void* parameters) {
    
    ctxt.id = 0;
    ctxt.status = POINT;



}