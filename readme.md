
# 🧭 IoT Rosa dos Ventos com Placa BitDogLab (Raspberry Pi Pico W)

**Esta é uma aplicação embarcada desenvolvida como parte da Tarefa Prática da Unidade 2 – Capítulo 3 ("Aplicações com Microcontroladores") da Residência Tecnológica em Sistemas Embarcados.**

O objetivo é utilizar a placa BitDogLab (com o Raspberry Pi Pico W) para capturar e interpretar os dados de um joystick, representar uma "Rosa dos Ventos" e transmitir essas informações para a nuvem. A aplicação reforça conceitos de conectividade Wi-Fi, interação com periféricos (display OLED, ADC), e integração com uma API Web hospedada na Railway.

---

## 🎯 Funcionalidades Principais:

* **Leitura do Joystick:** Captura os valores dos eixos X e Y do joystick analógico da placa BitDogLab.
* **Interpretação da "Rosa dos Ventos":** Converte as leituras do joystick em direções cardeais (Norte, Sul, Leste, Oeste, Nordeste, Sudeste, Noroeste, Sudoeste e Centro).
* **Display OLED Local:** Apresenta o status atual do joystick (coordenadas X, Y e direção) no display OLED integrado à BitDogLab.
* **Conectividade Wi-Fi:** Utiliza o módulo Wi-Fi do Raspberry Pi Pico W na BitDogLab para se conectar à rede e à internet.
* **Envio de Dados para Nuvem:** Transmite os dados do joystick (X, Y e direção) para uma API REST na nuvem (hospedada na Railway) via HTTP POST sempre que uma nova direção é detectada.

---

## 🛠️ Hardware Utilizado:

* **Placa de Desenvolvimento:** BitDogLab (com Raspberry Pi Pico W embarcado).
* **Sensor de Entrada:** Joystick analógico integrado à BitDogLab.
* **Display:** Display OLED I2C 128x64 integrado à BitDogLab.

---

## 📁 Estrutura do Projeto:

```
iot-rosa-dos-ventos/
├── lib/                            // Arquivos de bibliotecas externas
│   ├── ssd1306/                    // Biblioteca para o display OLED      
│   │   ├── font.h                  
│   │   ├── ssd1306.c               
│   │   └── sdd1306.h               
├── src/                            // Código fonte do projeto
│   ├── connection/                 // Código fonte para conexão com a API
│   │   ├── cliente_http.c
│   │   └── cliente_http.h
│   ├── utils/                      // Código fonte para funções utilitárias
│   │   ├── displayOLED/            // Código fonte para o display OLED
│   │   │   ├── displayOLED.c
│   │   │   └── displayOLED.h
│   │   ├── joystick/               // Código fonte para o joystick     
│   │   │   ├── joystick.c
│   │   │   └── joystick.h
│   │   ├── wifi/                   // Código fonte para conexão Wi-Fi 
│   │   │   ├── wifi.c
│   │   │   └── wifi.h
│   └── iot_rosa_dos_ventos.c       // Código principal do projeto
├── .gitignore
├── CMakeLists.txt
├── pico_sdk_import.cmake
└── README.md
```

---

## ☁️ Comunicação com a Nuvem (API via Proxy Railway).

A placa BitDogLab envia os dados para uma API Flask hospedada na plataforma Railway, utilizando um **proxy direto por host e porta**.

### 🔌 Como funciona:

- O Railway fornece um **host e uma porta TCP** dedicados (ex: `containers.up.railway.app:12345`) para que dispositivos externos possam se comunicar diretamente com a aplicação, mesmo sem HTTPS.
- A placa envia as requisições HTTP diretamente para esse host, usando o caminho `/dados`.

### 📌 Exemplo de configuração:
```c
#define HOST "containers.up.railway.app"
#define PORTA 12345
```

> ⚠️ A API está preparada para receber esses dados e retransmiti-los via WebSocket em tempo real para dashboards HTML acessados via navegador.

Essa abordagem é ideal para microcontroladores como o Raspberry Pi Pico W, que têm suporte limitado para conexões HTTPS.

---

## 🔐 Por que HTTP e não HTTPS na BitDogLab?

Implementar HTTPS diretamente no microcontrolador é custoso. A plataforma Railway atua como um **proxy reverso**, permitindo que a placa use **HTTP** simples enquanto a comunicação com o usuário final (navegador) permanece segura via **HTTPS**.

---

## 🚀 Como Compilar, Configurar e Gravar na sua Placa.

Este projeto usa o **Pico SDK versão 1.5.1** e deve ser importado corretamente para compilar.

### 📥 Passos para usar:

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/LincolnMatheus97/Iot-rosa-do-ventos.git
   cd Iot-rosa-dos-ventos
   ```

2. **Importe no VS Code com a extensão "Raspeberry Pi Pico Project":**
   - Abra o VS Code
   - Vá na extensão, clice em Import Project
   - Selecione o diretorio aonde esta o repositório clonado
   - Altere a versar para **1.5.1**, e clique em create

3. **Configure a conexão Wi-Fi**
   - No arquivo `wifi.h`, altere os seguintes campos:
     ```c
     #define NOME_REDE_WIFI "SEU_SSID"
     #define SENHA_REDE_WIFI "SUA_SENHA"
     ```

4. **Compile:**
   - Pressione `Ctrl + Shift + B` para compilar
   - O arquivo `.uf2` será gerado automaticamente na pasta `build/`

5. **Grave na BitDogLab:**
   - Pressione e segure o botão `BOOTSEL` enquanto conecta a placa ao computador
   - Solte o botão após a montagem como unidade USB
   - Copie o arquivo `.uf2` para dentro da unidade

---

## 👨‍💻 Autor.

* Lincoln Matheus Costa Campelo Pinho
* [Meu Perfil no GitHub!](https://github.com/LincolnMatheus97)