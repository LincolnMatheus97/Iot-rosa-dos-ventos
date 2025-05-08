#include "displayOLED.h"

void inic_barr_i2c()
{
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

void inic_display(ssd1306_t *display)
{
    ssd1306_init(display, 128, 64, ADD_DISPLAY, I2C_PORT);
    ssd1306_clear(display);
}

void mostrar_display(ssd1306_t *display, const char* texto)
{
    ssd1306_clear(display);
    ssd1306_draw_string(display, 0, 32, 1, texto);
    ssd1306_show(display);
}