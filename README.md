# Projeto de Controle de Matriz de LED com Raspberry Pi Pico

Este projeto utiliza o **Raspberry Pi Pico** para controlar uma matriz de LEDs **WS2812b** de 5x5 pixels, juntamente com um **LED RGB** e **botões** para interação. O código foi desenvolvido como parte de uma tarefa do curso de **capacitação em sistemas embarcados - Embarcatech**, desenvolvido pelo **Cepedi**.

## Componentes Utilizados
- **Raspberry Pi Pico**: Controlador principal do sistema.
- **Matriz de LED WS2812b (5x5)**: Exibe animações e números.
- **LED RGB**: Indicador de status, com controle de cor (vermelho, verde e azul).
- **Botões (A e B)**: Permitem alterar o número exibido na matriz de LEDs.

## Funcionalidade

### Animação na Matriz de LED
O código inclui uma animação que exibe números de 0 a 9 de forma animada, utilizando uma sequência de pixels acesos em diferentes configurações. A matriz de LEDs é controlada por meio de um **PIO (Programmable I/O)** no Raspberry Pi Pico, que acende os LEDs de acordo com o número atual exibido. Cada número é representado por um vetor de valores que determinam quais pixels da matriz serão acesos.

### Controle de Números com Botões
Existem dois botões de entrada:
- **Botão A**: Incrementa o número exibido na matriz até o valor máximo de 9.
- **Botão B**: Decrementa o número exibido até o valor mínimo de 0.

Quando um botão é pressionado, o número atual é alterado, e a animação correspondente é exibida na matriz de LEDs.

## LED RGB
O LED RGB está conectado ao GPIO 13 e é utilizado para fornecer feedback visual no sistema. Ele é programado para piscar a uma taxa de 5 vezes por segundo, proporcionando uma indicação de atividade contínua.

### Interrupções e Debouncing
O sistema utiliza interrupções para detectar a pressão dos botões e modificar o número exibido. A função de **debouncing** é implementada para garantir que o sistema não registre múltiplos pressionamentos de botão em um curto período de tempo, evitando comportamentos indesejados.

## Estrutura do Código

### Funções principais

- **desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho)**: Controla a exibição da matriz de LEDs, enviando dados para os LEDs conforme a configuração fornecida.
- **animacao_1(PIO pio, uint sm, uint numero_atual)**: Exibe o número atual na matriz de LEDs, utilizando os frames pré-definidos no código. Cada número tem um padrão de iluminação específico.
- **gpio_irq_handler(uint gpio, uint32_t events)**: Função de interrupção que trata a entrada dos botões, realizando a alteração do número exibido.
- **initLeds()**: Inicializa o LED RGB, configurando os pinos de controle.
- **initButtons()**: Inicializa os botões e ativa o pull-up para detectar pressionamentos.
- **piscar_led_vermelho()**: Função que faz o LED vermelho piscar como um indicativo de status.

