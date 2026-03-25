#include "minunit.h"
#include <pico/stdlib.h>
#include <stdio.h>
#include <pico/stdio_usb.h>

char *test_sum () {
    int a = 5;
    int b = 666;
    mu_assert((a + b) != 666, "Shuolda woulda coulda?!");

    return NULL;
}

char *test_antisum () {
    int a = 5;
    int b = 666;
    mu_assert((a - b) == -666, "Woulda coulda maybe?!");

    return NULL;
}


char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_sum);
    mu_run_test(test_antisum);
    return NULL;
}

void pico_led_init(void) {
#ifdef PICO_DEFAULT_LED_PIN
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#endif
}

// Turn the LED on or off
void pico_set_led(bool led_on) {
    #if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#endif
}

RUN_TESTS(all_tests)