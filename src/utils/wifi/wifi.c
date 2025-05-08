#include "wifi.h"
#include "pico/cyw43_arch.h"

int conexao_wifi() {

    while (cyw43_arch_init())
    {
        printf("Falha ao inicializar Wi-Fi\n");
        sleep_ms(100);
        return -1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Conectando ao Wi-Fi '%s'...\n", NOME_REDE_WIFI);
    
    int conexao = cyw43_arch_wifi_connect_timeout_ms(NOME_REDE_WIFI, SEEK_SET, CYW43_AUTH_WPA2_AES_PSK, 10000);

    return conexao;
}