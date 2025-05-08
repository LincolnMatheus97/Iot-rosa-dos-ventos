#ifndef DISPLAYOLED_H
#define DISPLAYOLED_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306/ssd1306.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ADD_DISPLAY 0X3C

void inic_barr_i2c();
void inic_display(ssd1306_t *display);
void mostrar_display(ssd1306_t *display, const char* texto);

#endif