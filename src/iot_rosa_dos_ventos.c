#include <stdio.h>
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "joystick.h"
#include "cliente_http.h"
#include "wifi.h"
#include "displayOLED.h"

char direcao_anterior[20] = "";
int joy_x_anterior = -1; 
int joy_y_anterior = -1;

StatusJoystick *status_joystick = NULL;

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

void atualizar_status_no_display(int valor_x, int valor_y, const char* direcao)
{
    limpar_display();

    escrever_display("Status Joystick", 22, 0, 1);

    char dados_joystick[40];
    snprintf(dados_joystick, sizeof(dados_joystick), "X:%d Y:%d - %s", valor_x, valor_y, direcao);
    escrever_display(dados_joystick, 5, 32, 1);

    mostrar_display();
}

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
        cyw43_arch_poll();

        const char* direcao_atual_const = verificar_movimento();
        int joy_x_atual = leitura_joystick_x();
        int joy_y_atual = leitura_joystick_y();
        
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

    cyw43_arch_deinit();
    return 0;
}
