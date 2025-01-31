#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

// Arquivo de configuração da Matriz de LED 5x5 - Arquivo PIO 
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

extern void animacao_1(PIO pio, uint sm);

// Variáveis globais
static volatile uint32_t last_time = 0;  // Variável para debouce
static volatile uint numero_atual = 0;   // Variável para armazenar o número atual



// Defina 'pio' e 'sm' como variáveis globais
PIO pio = pio0;  
uint sm;

// Acionamento da matriz de LEDs - ws2812b
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) { // Aplica a cor ao padrão
        pio_sm_put_blocking(pio, sm, desenho[24-i]);
    }
}

// Protótipo da função de interrupção
void gpio_irq_handler(uint gpio, uint32_t events);


// Funções de inicialização dos LEDs e botões
void initLeds() {
    gpio_init(LED_RED_PIN);    
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);

    gpio_init(LED_BLUE_PIN);    
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT); 

    gpio_init(LED_GREEN_PIN);    
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT); 
}

void initButtons() {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);             
    gpio_set_dir(BUTTON_B, GPIO_IN); 
    gpio_pull_up(BUTTON_B);
}

// Função para piscar o LED vermelho
void piscar_led_vermelho() {
    for (int i = 0; i < 5; i++) {
        gpio_put(LED_RED_PIN, 1);  // Acende o LED vermelho
        sleep_ms(100);              // Mantém o LED aceso por 100ms
        gpio_put(LED_RED_PIN, 0);  // Apaga o LED vermelho
        sleep_ms(100);              // Mantém o LED apagado por 100ms
    }
}

// Função principal
int main() {
    stdio_init_all();

    bool ok;

    ok = set_sys_clock_khz(128000, false);

    // Configuração da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    // Inicializa LEDs e botões
    initLeds();
    initButtons();

    // Configura interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Loop principal
    while (true) {
        piscar_led_vermelho();  // Pisca o LED vermelho a cada 1 segundo
        sleep_ms(1000);
    }
}

// Função de interrupção para tratar os botões
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = time_us_32();

    // Verifica se o tempo de debouncing passou
    if (current_time - last_time > 200000) {  // 200ms para debouncing
        last_time = current_time;

        if (gpio == BUTTON_A) {
            numero_atual++;
            printf("Botão A pressionado. ");
            printf("Número atual: %d\n", numero_atual);
        }
        if (gpio == BUTTON_B) {
            --numero_atual;
            printf("Botão B pressionado. ");
            printf("Número atual: %d\n", numero_atual);
        }

        //desenhar_numero_na_matriz_de_leds(r, g, b, numero_atual);
        animacao_1(pio, sm);
    }
}
