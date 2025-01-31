#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//Arquivo PIO - Configuração da Matriz de LED 
#include "ws2812.pio.h";

// Número de LEDs
#define NUM_PIXELS 25

// Pino de saída
#define OUT_PIN 7

void initMatrizLed(){

    PIO pio = pio0; 
    bool ok;

    // Configuração do clock para 128 MHz
    ok = set_sys_clock_khz(128000, false);
    stdio_init_all();

    printf("Iniciando a transmissão PIO\n");
    if (ok) printf("Clock set to %ld Hz\n", clock_get_hz(clk_sys));

    // Configuração da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);
}