#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define VRX_JOYSTICK 27
#define VRY_JOYSTICK 26
#define JOYSTICK_LIMITE_SUPERIOR 80 
#define JOYSTICK_LIMITE_INFERIOR 20

void inicializar_adc();
uint8_t leitura_joystick_x();
uint8_t leitura_joystick_y();
const char* verificar_movimento();

#endif