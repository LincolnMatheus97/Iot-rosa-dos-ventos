#ifndef CLIENTE_HTTP_H
#define CLIENTE_HTTP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/cyw43_arch.h"
#include "lwip/dns.h"
#include "lwip/ip_addr.h"
#include "lwip/tcp.h"

#define PROXY_HOST "maglev.proxy.rlwy.net"
#define PROXY_PORT 48443

typedef struct{
    char direcao[20];
    int joy_x, joy_y;
} StatusJoystick;

void enviar_dados_para_nuvem(const StatusJoystick* dados_a_enviar);

#endif
