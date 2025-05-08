#include "joystick.h"

/**
 * @brief Inicializa o ADC para leitura do joystick.
 * @note Configura os pinos do joystick como entradas analógicas.
 */
void inicializar_adc() 
{
    adc_init();
    adc_gpio_init(VRX_JOYSTICK);
    adc_gpio_init(VRY_JOYSTICK);
}

/**
 * @brief Lê o valor do joystick na direção X.
 * @return Valor lido (0-100) representando a posição do joystick na direção X.
 * @note O valor é normalizado para a faixa de 0 a 100.
 *       O valor máximo do ADC é 4095, então a leitura é multiplicada por 100 e dividida por 4095.
 */
uint8_t leitura_joystick_x()
{
    adc_select_input(1);
    return adc_read() * 100 / 4095;
}

/**
 * @brief Lê o valor do joystick na direção Y.
 * @return Valor lido (0-100) representando a posição do joystick na direção Y.
 * @note O valor é normalizado para a faixa de 0 a 100.
 *       O valor máximo do ADC é 4095, então a leitura é multiplicada por 100 e dividida por 4095.
 */
uint8_t leitura_joystick_y()
{
    adc_select_input(0);
    return adc_read() * 100 / 4095;
}

/**
 * @brief Verifica a direção do movimento do joystick.
 * @return String representando a direção do movimento (Norte, Sul, Leste, Oeste, etc.).
 * @note O joystick é dividido em 9 regiões: Centro, Norte, Sul, Leste, Oeste e as diagonais.
 *       As regiões são definidas por limites superiores e inferiores, que são constantes.
 */
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