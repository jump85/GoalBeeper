#include "pico/stdlib.h"
#include "pico/sleep.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    printf("Ciao Pico!\n");
    while (true) {
        sleep_ms(1000);
        printf("Ancora sveglio!\n");
    }
}
