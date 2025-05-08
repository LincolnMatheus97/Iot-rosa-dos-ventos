#include "joystick.h"

void inicializar_adc() 
{
    adc_init();
    adc_gpio_init(VRX_JOYSTICK);
    adc_gpio_init(VRY_JOYSTICK);
}

uint8_t leitura_joystick_x()
{
    adc_select_input(1);
    return adc_read() * 100 / 4095;
}

uint8_t leitura_joystick_y()
{
    adc_select_input(0);
    return adc_read() * 100 / 4095;
}

const char* verificar_movimento() 
{
    uint8_t x = leitura_joystick_x();
    uint8_t y = leitura_joystick_y();

    static const char* direcoes[3][3] =
    {
        {"Sudoeste", "Oeste", "Noroeste"},
        {"Sul", "Centro", "Norte"},
        {"Sudeste", "Leste", "Nordeste"},
    };

    int indice_x;
    if (x < JOYSTICK_LIMITE_INFERIOR) {
        indice_x = 0; // Oeste
    } else if (x > JOYSTICK_LIMITE_SUPERIOR) {
        indice_x = 2; // Leste
    } else {
        indice_x = 1; // Centro
    }

    int indice_y;
    if (y < JOYSTICK_LIMITE_INFERIOR) {
        indice_y = 0; // Sul
    } else if (y > JOYSTICK_LIMITE_SUPERIOR) {
        indice_y = 2; // Norte
    } else {
        indice_y = 1; // Centro
    }

    return direcoes[indice_x][indice_y];
}