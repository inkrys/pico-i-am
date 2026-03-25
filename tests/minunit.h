#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <dbg_helperz.h>
#include <stdlib.h>

#define mu_suite_start() char *message = NULL

#define mu_assert(test, message, ...) if (!(test)) {\
    log_err(message, ##__VA_ARGS__); return message; }
#define mu_run_test(test) debug("\n-----%s", " " #test); \
    message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
    stdio_init_all();\
start:\
    printf("Starting test application.\n");\
    do {\
        sleep_ms(1000);\
    } while(stdio_usb_connected() == false);\
    printf("Connected to USB host.\n");\
    pico_set_led(false);\
    printf("----\nRUNNING all tests");\
    char *result = all_tests();\
    if (result != 0) {\
        printf("FAILED: %s\n", result);\
    }\
    else {\
        printf("ALL TESTS PASSED\n");\
    }\
    printf("Tests run: %d\n", tests_run);\
    do {\
        puts("Tests run finished.\n");\
        sleep_ms(5000);\
    } while(stdio_usb_connected() == true);\
    goto start;\
}\

int tests_run = 0;

#endif
