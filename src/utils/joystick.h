#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define VRX_JOYSTICK 27
#define VRY_JOYSTICK 26

void inicializar_adc();
uint8_t leitura_joystick_x();
uint8_t leitura_joystick_y();

#endif