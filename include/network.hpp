/*
 * Ce code est la propriété de Léo Branchut. Tous droits réservés.
 */
#ifndef NETWORK_H
#define NETWORK_H

/*
 * Start mesh recognition. Scan closes lights and join them to the mesh.
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