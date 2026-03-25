#ifndef _pico_i_am_h_
#define _pico_i_am_h_

#include <pico/stdlib.h>
#include <stdio.h>
#include <dbg_helperz.h>
#include <stdint.h>
#include <mqtt_interface.h>
#include <wizchip_conf.h>
#include <time.h>

enum pico_i_am_ConnState {ERROR, CONNECTED, DISCONNECTED, LINK_DOWN};

struct pico_i_am_ConnData{
    enum pico_i_am_ConnState state;
    Network network;
};


/**
 * @brief Manages connection to TCP server
 * @param net_info : network info
 * @return Pointer to a connected network 
 */
Network *pico_i_am_manage_conn(wiz_NetInfo net_info);

/**
 * @brief Initializes network connection with network data and socket.
 * @param n - network settings
 * @param sn - MQTT socket used for this connection
 * @return - 
 */
struct pico_i_am_ConnData *pico_i_am_init_conn(const Network n, const int sn);


/**
 * @brief Initializes wiznet chip and pico board
 * @return 0 if OK, -1 if error
 */
int pico_i_am_setup_wXXXX_evb_pico(void);

/**
 * @brief Access to the millisecond timer value.
 * @returns current value of timer in millisecond
 */
time_t millis(void);
#endif