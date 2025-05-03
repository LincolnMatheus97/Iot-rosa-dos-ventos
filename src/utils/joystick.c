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