# 📟 Simulação TRIA TAG – Controle de LED, Buzina, LCD e EEPROM

Este projeto é uma simulação no **Wokwi** utilizando o microcontrolador **ESP32**, com o objetivo de integrar múltiplos periféricos (LED, buzina, botões, LCD) e armazenar informações de forma persistente na **EEPROM**.

---

## 🚀 Tecnologias Utilizadas
- **ESP32** – Microcontrolador principal.
- **Wokwi** – Simulador online para prototipagem rápida de sistemas embarcados.
- **C++ (Arduino)** – Linguagem utilizada no desenvolvimento.
- **Bibliotecas:**
  - [`WiFi.h`](https://www.arduino.cc/en/Reference/WiFi) – Para simulação de conexão Wi-Fi.
  - [`Wire.h`](https://www.arduino.cc/en/reference/wire) – Comunicação I2C.
  - [`LiquidCrystal_I2C.h`](https://github.com/johnrickman/LiquidCrystal_I2C) – Controle simplificado do display LCD via interface I2C.
  - [`EEPROM.h`](https://www.arduino.cc/en/Reference/EEPROM) – Gravação e leitura de dados persistentes na memória.

---

## ❓ Por que usar a biblioteca **LiquidCrystal I2C**
O display LCD 16x2 pode ser controlado diretamente por vários pinos digitais, mas isso consome muitos recursos do microcontrolador.  
A escolha da biblioteca **LiquidCrystal I2C** foi feita porque:
- Utiliza apenas **2 pinos** (SDA e SCL) em vez de 6+ conexões.
- Simplifica o código com comandos diretos (`LCD.init()`, `LCD.print()` etc).
- Permite fácil expansão de periféricos no ESP32 sem ocupar pinos desnecessários.

---

## ⚙️ Funcionalidades
- **LED controlado por botão** (liga/desliga), simulando como será no aplicativo.
- **Buzina ativada por chave/botão**, simulando como será no aplicativo.
- **Armazenamento de dados na EEPROM**:
  - Placa do veículo.
  - Setor correspondente.
- **Exibição no LCD**:
  - Linha 1 → Placa.
  - Linha 2 → Setor.
- **Botão de recuperação** dos dados salvos na EEPROM.
- **Simulação de Wi-Fi** .

---

## 🖥️ Instruções de Uso
1. Abra o projeto no **[Wokwi](https://wokwi.com/)**.  
2. Carregue o código do ESP32 (`.ino` ou `.cpp`) e o arquivo `diagram.json`.  
3. Clique em **Play** ▶ para iniciar a simulação.  
4. Interaja com os botões:
   - **Botão LED** → alterna o estado do LED.  
   - **Botão EEPROM** → lê a placa + setor salvos e exibe no LCD.  
   - **Chave buzina** → alterna buzina ligada/desligada.  
5. Acompanhe as mensagens também pelo **Serial Monitor**.

---

## 📊 Resultados Parciais
Até o momento, o projeto já permite:
- Gravar e recuperar **placa + setor** da EEPROM.
- Mostrar os dados no **LCD** com layout organizado.
- Alternar LED e buzina por botões dedicados.
- Conectar ao Wi-Fi simulado e exibir status no display.

---

## 🎥 Link do Vídeo
[Vídeo apresentação da ideia central do projeto e demonstração funcional](https://www.youtube.com/watch?v=V6_2mS8jhyY)

---

## 📌 AUTORES
Projeto desenvolvido por 

-Alice Nunes - RM 559052

-Guilherme Akira - RM 556128

-Anne Rezendes - RM 556779

---
