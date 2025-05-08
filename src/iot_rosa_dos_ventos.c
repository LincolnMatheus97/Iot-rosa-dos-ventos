/**
 * @file iot_rosa_dos_ventos.c
 * @brief Código principal do projeto IoT Rosa dos Ventos.
 * @author Lincoln Matheus Costa Campelo Pinho
 * @date 2025-05-08
 * @version 1.0
 * @details
 * Este código implementa um sistema IoT que lê os dados de um joystick e envia essas informações para um servidor na nuvem.
 * O sistema utiliza um microcontrolador Raspberry Pi Pico W, que se conecta a uma rede Wi-Fi e envia os dados via HTTP.
 */

// -- INCLUDES --
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// -- INCLUDES DO PROJETO --
#include "joystick.h"
#include "cliente_http.h"
#include "wifi.h"
#include "displayOLED.h"

// -- DECLARAÇÕES  DE VARIAVEIS--
char direcao_anterior[20] = "";     // Variável para armazenar a direção anterior do joystick
int joy_x_anterior = -1;            // Variável para armazenar a leitura anterior do joystick na direção X
int joy_y_anterior = -1;            // Variável para armazenar a leitura anterior do joystick na direção Y

StatusJoystick *status_joystick = NULL;  // Estrutura para armazenar os dados do joystick

/**
 * @brief Inicia a conexão Wi-Fi e exibe o status no display.
 * @return 0 se a conexão for bem-sucedida, -1 caso contrário.
 * @note Inicializa o módulo Wi-Fi, ativa o modo estação e tenta conectar à rede especificada.
 */
int iniciar_conexao_wifi() 
{
    limpar_display();
    escrever_display("Conectando em:", 23, 20, 1);
    escrever_display(NOME_REDE_WIFI, 23, 32, 1);
    mostrar_display();

    int status_conexao = conexao_wifi();

    limpar_display();
    if (status_conexao == 0) {
        escrever_display("CONEXAO ESTABECIDA", 10, 30, 1);
        printf("IP do dispositivo: %s\n", ipaddr_ntoa(&netif_default->ip_addr));
    } else {
        escrever_display("FALHA NA CONEXAO", 10, 30, 1);
    }
    mostrar_display();
    sleep_ms(3000);

    return status_conexao;
}

/**
 * @brief Atualiza o status do joystick no display OLED.
 * @param valor_x Valor lido do joystick na direção X.
 * @param valor_y Valor lido do joystick na direção Y.
 * @param direcao Direção atual do joystick.
 * @note Limpa o display, escreve o status e mostra as informações do joystick.
 *       Utiliza a função de escrita do display para exibir os dados.
 */
void atualizar_status_no_display(int valor_x, int valor_y, const char* direcao)
{
    limpar_display();

    escrever_display("Status Joystick", 22, 0, 1);

    char dados_joystick[40];
    snprintf(dados_joystick, sizeof(dados_joystick), "X:%d Y:%d - %s", valor_x, valor_y, direcao);
    escrever_display(dados_joystick, 5, 32, 1);

    mostrar_display();
}

/**
 * @brief Inicializa os periféricos do sistema.
 * @note Inicializa a comunicação serial, o ADC, o barramento I2C e o display OLED.
 *       Aloca memória para a estrutura StatusJoystick e inicializa seus valores.
 */
void iniciar_perifericos()
{
    stdio_init_all();
    inicializar_adc();
    inic_barr_i2c();
    inic_display();

    status_joystick = (StatusJoystick*)malloc(sizeof(StatusJoystick));
    status_joystick->joy_x = 0;
    status_joystick->joy_y = 0;
    strcpy(status_joystick->direcao, "Centro");
}

/**
 * @brief Função principal do programa.
 * @return 0 se o programa for executado com sucesso.
 * @note Inicializa os periféricos, a conexão Wi-Fi e le os dados do joystick.
 *       Atualiza o status no display e envia os dados para a nuvem.
 *       O loop principal verifica continuamente as leituras do joystick e 
 *       atualiza o display e a nuvem se houver mudança nos status.
 */
int main()
{
    iniciar_perifericos(); 
    sleep_ms(1500);

    iniciar_conexao_wifi();
    
    strcpy(direcao_anterior, verificar_movimento());
    joy_x_anterior = leitura_joystick_x();
    joy_y_anterior = leitura_joystick_y();
    
    atualizar_status_no_display(joy_x_anterior, joy_y_anterior, direcao_anterior);
    
    enviar_dados_para_nuvem(status_joystick);

    while (true)
    {
        cyw43_arch_poll(); // Verifica se há pacotes recebidos e processa-os

        const char* direcao_atual_const = verificar_movimento();
        int joy_x_atual = leitura_joystick_x();
        int joy_y_atual = leitura_joystick_y();
        
        // Verifica se houve mudança na direção ou nas leituras do joystick
        // Se houve mudança, atualiza o status e envia os dados para a nuvem
        if (strcmp(direcao_anterior, direcao_atual_const) != 0 ||
            joy_x_anterior != joy_x_atual ||
            joy_y_anterior != joy_y_atual)
        {
            
            strcpy(status_joystick->direcao, direcao_atual_const);
            status_joystick->joy_x = joy_x_atual;
            status_joystick->joy_y = joy_y_atual;

            atualizar_status_no_display(status_joystick->joy_x, status_joystick->joy_y, status_joystick->direcao);
            
            enviar_dados_para_nuvem(status_joystick);

            // Atualiza os valores anteriores para a próxima comparação
            strcpy(direcao_anterior, status_joystick->direcao);
            joy_x_anterior = status_joystick->joy_x;
            joy_y_anterior = status_joystick->joy_y;
        }
        
        atualizar_status_no_display(joy_x_atual, joy_y_atual, direcao_atual_const);

        sleep_ms(100); 
    }

    cyw43_arch_deinit();  // Desativa o módulo Wi-Fi antes de sair
    free(status_joystick); // Libera a memória alocada para a estrutura StatusJoystick
    return 0;
}
