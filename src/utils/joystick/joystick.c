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

    if (x > JOYSTICK_LIMITE_SUPERIOR && y > JOYSTICK_LIMITE_SUPERIOR)
    {
        return "Nordeste";
    } 
    else if (x > JOYSTICK_LIMITE_SUPERIOR && y < JOYSTICK_LIMITE_INFERIOR)
    {
        return "Sudeste";
    }
    else if (x < JOYSTICK_LIMITE_INFERIOR && y > JOYSTICK_LIMITE_SUPERIOR)
    {
        return "Noroeste";
    }
    else if (x < JOYSTICK_LIMITE_INFERIOR && y < JOYSTICK_LIMITE_INFERIOR)
    {
        return "Sudoeste";
    }
    else if (x > JOYSTICK_LIMITE_SUPERIOR)
    {
        return "Leste";
    }
    else if (x < JOYSTICK_LIMITE_INFERIOR)
    {
        return "Oeste";
    }
    else if (y > JOYSTICK_LIMITE_SUPERIOR)
    {
        return "Norte";
    }
    else if (y < JOYSTICK_LIMITE_INFERIOR)
    {
        return "Sul";
    }
    else
    {
        return "Centro";
    }
}