#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "ws2812.h" // Biblioteca fictícia para controle dos LEDs WS2812
#include "ws2818b.pio.h" 
#include "desenhos.c"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

#define LED_R 11
#define LED_G 12
#define LED_B 13
#define BUTTON_A 5
#define BUTTON_B 6
#define LED_MATRIX 7

static volatile int number = 0;

void debounce(void) {
    sleep_ms(50); // Simples debouncing via software
}

void display_number(int num) {
    for (int i = 0; i < 25; i++) {
        int x = i % 5;
        int y = i / 5;
        double intensity = numeros[num][i];
        int r = (int)(intensity * 255);
        int g = 0;
        int b = 0;
        ws2812_set_pixel(x, y, r, g, b);
    }
    ws2812_show();
}

void button_a_irq(uint gpio, uint32_t events) {
    debounce();
    number = (number + 1) % 10;
    display_number(number);
}

void button_b_irq(uint gpio, uint32_t events) {
    debounce();
    number = (number - 1 + 10) % 10;
    display_number(number);
}

void setup_gpio() {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_a_irq);
  
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_b_irq);
}

int main() {
    stdio_init_all();
    setup_gpio();
    ws2812_init(LED_MATRIX);
    display_number(number);
    
    while (true) {
        // Tarefa de piscar o LED
        gpio_put(LED_R, 1);
        sleep_ms(100);
        gpio_put(LED_R, 0);
        sleep_ms(100);
        
        tight_loop_contents();
    }
}
