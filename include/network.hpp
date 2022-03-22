/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */
#ifndef NETWORK_H
#define NETWORK_H

#include "internal.hpp"


#define POINT_NB_PER_MESH 20

typedef struct network_point {
    uint32_t id;
    uint8_t status;
    uint8_t type;
    uint16_t mesh_id;               /*Light id inside the mesh. ID unattributed: 33*/
}t_network_points;

t_network_points T_MESH_POINT[POINT_NB_PER_MESH];

/*
 * Add a light to the network known points
 */
int network_add_a_point(uint32_t id, uint8_t status, uint8_t type);

/*
 * Start mesh recognition. Send a message to clothes lights.
 * Returns 0 if OK
 */
int start_mesh_initialisation(void);

/*
 * Scan lights with a tx power.
 */
int scan_lights(uint8_t tx_power);

/*
 * Check Acknowledges power and pick the 20 closest lights.
 * Returns 0 if OK
 */
int pick_closest_lights(void);

/*
 * Add a light to a mesh.
 * Returns 0 if OK
 */
int add_light_to_the_mesh(int *mesh, int light_id);

/*
 * Send a start signal to a further light node.
 * Returns 0 if OK
 */
int start_next_mesh(void);


#endif /*NETWORK_H*/