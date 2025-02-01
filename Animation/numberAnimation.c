#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "pio_matrix.pio.h"

#define NUM_PIXELS 25

// Declaração da função desenhar_matriz
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho);

// Função de animação com 5 frames (efeito de onda)
void animacao_1(PIO pio, uint sm, uint numero_atual) {

    
    const uint32_t numeros[10][NUM_PIXELS] = {
        {
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000, // 0
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
        },
        {
            0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000, // 1
            0x00000000, 0x0000FF00, 0x0000FF00, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000
        },
        {
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, // 2
            0x00000000, 0x00000000, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
        },
        {
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, // 3
            0x00000000, 0x00000000, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
        },
        {
            0x00000000, 0x0000FF00, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, // 4
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000
        },
        {
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, // 5
            0x00000000, 0x0000FF00, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
        },
        {
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, // 6
            0x00000000, 0x0000FF00, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
        },
        {
            0x00000000, 0x0000FF00, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x00000000, 0x00000000, 0x00000000, // 7
            0x00000000, 0x00000000, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
        },
        {
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, // 8
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
        },
         {
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, // 9
            0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
            0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
        }

    };

    // Exibir o "Frame" que corresponde ao numero atual 
    desenhar_matriz(pio, sm, numeros[numero_atual]); 


    
}