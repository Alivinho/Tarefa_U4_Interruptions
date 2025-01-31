#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//Arquivo de configuração da Matriz de LED 5x5 - Arquivo PIO 
#include "pio_matrix.pio.h"

// Matriz LED
#define NUM_PIXELS 25
#define OUT_PIN 7

// Botões
#define BUTTON_A 5
#define BUTTON_B 6

// LED RGB
#define LED_RED_PIN 13
#define LED_BLUE_PIN 12
#define LED_GREEN_PIN 11


void initLeds(){
   gpio_init(LED_RED_PIN);    
   gpio_set_dir(LED_RED_PIN, GPIO_OUT);
   
   gpio_init(LED_BLUE_PIN);    
   gpio_set_dir(LED_BLUE_PIN, GPIO_OUT); 
   
   gpio_init(LED_GREEN_PIN );    
   gpio_set_dir(LED_GREEN_PIN , GPIO_OUT); 
}

void initButtons(){
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);             // Inicializa o botão
    gpio_set_dir(BUTTON_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_B)
}


int main(){
    PIO pio = pio0; 
    bool ok;

    ok = set_sys_clock_khz(128000, false);

    // Configuração da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);


    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
