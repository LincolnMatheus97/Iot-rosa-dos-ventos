#ifndef CLIENTE_HTTP_H
#define CLIENTE_HTTP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/cyw43_arch.h"
#include "lwip/dns.h"
#include "lwip/ip_addr.h"
#include "lwip/tcp.h"
#include "src/utils/joystick.h"

#define PROXY_HOST "maglev.proxy.rlwy.net"
#define PROXY_PORT 48443

void enviar_dados_para_nuvem();

#endif
