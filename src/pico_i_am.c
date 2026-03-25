#include "pico_i_am.h"
#include <wizchip_spi.h>
#include <timer.h>

static struct pico_i_am_ConnData *conn_data;

/* Timer */
static volatile uint32_t g_msec_cnt = 0;

static void repeating_timer_callback(void) {
    g_msec_cnt++;

    MilliTimer_Handler();
}

time_t millis(void) {
    return g_msec_cnt;
}

Network *pico_i_am_manage_conn(wiz_NetInfo net_info)
{
    static enum pico_i_am_ConnState conn_state = DISCONNECTED;
    return NULL;     
}

int pico_i_am_setup_wXXXX_evb_pico(void)
{
    int retval = 0;
    wizchip_spi_initialize();
    wizchip_cris_initialize();

    wizchip_reset();
    retval = wizchip_initialize();
    check(retval == 0, "Wizchip initialization error.");
    wizchip_check();

    wizchip_1ms_timer_initialize(repeating_timer_callback);

    return 0;

error:
    return -1;
}

struct pico_i_am_ConnData *pico_i_am_init_conn(const Network n, const int sn)
{
    // To meet requiremenst of NewNetwork function, need to check socket is valid.
    check((sn >= 0) && (sn <= 7), "Socket must be in range 0..7 ");
    conn_data->state = DISCONNECTED;
    conn_data->network = n;

    // The next call could be read as "creating a new network". In practice it just populates a
    // Network struct with the w5X00_read and w5X00_write functions and the socket.
    NewNetwork(&conn_data->network, sn);
    return conn_data;
error:
    return NULL;
}