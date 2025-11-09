# 🚀 **Projeto TRIA TAG – Monitoramento Inteligente de Motocicletas (ESP32 + IoT)**

Este projeto simula um **sistema IoT de monitoramento veicular** desenvolvido com o **ESP32**, integrando **Thinger.io**, **EEPROM**, **controle de LED e buzina**, e **coleta de métricas de uso**.  
A proposta visa **monitorar motos dentro de um pátio**, **acompanhar seu funcionamento**, e **enviar dados em tempo real** para a nuvem — apoiando o desafio proposto pela **Mottu** e **FIAP**.

---

## ⚙️ **Principais Funcionalidades**
- 🟢 **Controle remoto de LED e buzina** via **Thinger.io** ou por botões físicos.  
- 💾 **Armazenamento persistente (EEPROM)** de:
  - Placa da moto.
  - Latitude e longitude do local.  
- 🌐 **Conexão Wi-Fi** e integração direta com o **Thinger.io**.  
- 📈 **Métricas automáticas**:
  - Tempo total de LED ligado.
  - Tempo total de buzina acionada.
  - Número de ativações de cada componente.
- 🛰️ **Simulação de GPS dinâmico** — altera a localização se o veículo estiver “em deslocamento”.  
- 🔔 **Transmissão em tempo real** de informações para o painel IoT.

---

## 🧩 **Tecnologias e Bibliotecas Utilizadas**
| Biblioteca | Função |
|-------------|--------|
| **WiFi.h** | Conexão do ESP32 à rede Wi-Fi |
| **Wire.h** | Comunicação I²C |
| **LiquidCrystal_I2C.h** | Controle de display LCD via interface I²C |
| **EEPROM.h** | Armazenamento persistente de dados (placa e coordenadas) |
| **ThingerESP32.h** | Integração com a plataforma IoT Thinger.io |

---

## 🌍 **Integração com Thinger.io**

A integração com o **[Thinger.io](https://thinger.io)** permite **monitorar, controlar e coletar dados** do sistema em tempo real.  
Os recursos criados no código correspondem aos seguintes controles e sensores:

| Recurso | Tipo | Descrição |
|----------|------|-----------|
| `placa` | Leitura | Retorna a placa salva na EEPROM |
| `led` | Entrada/Saída | Liga/desliga o LED e transmite seu estado |
| `buzina` | Entrada/Saída | Liga/desliga a buzina e transmite seu estado |
| `metricas` | Leitura | Retorna contadores e tempos de uso de LED e buzina |
| `gps` | Leitura | Retorna latitude, longitude e status (“Em deslocamento” ou “Parado na oficina”) |

---

## 🔌 **Estrutura de Hardware (Simulação Wokwi)**
| Componente | Pino ESP32 | Descrição |
|-------------|-------------|-----------|
| LED | 19 | Indica estado ativo/inativo |
| Botão LED | 18 | Alterna manualmente o LED |
| Botão EEPROM | 17 | Aciona leitura/gravação de dados |
| Chave buzina | 4 | Alterna buzina ligada/desligada |
| Buzzer | 16 | Sinal sonoro da moto |
| Display LCD (I2C) | SDA/SCL | Exibe status e dados da moto |

---

## 🧠 **Lógica de Funcionamento**
1. **Inicialização:**  
   - O ESP32 conecta-se ao Wi-Fi e ao Thinger.io.  
   - A placa, latitude e longitude são gravadas na EEPROM.  
2. **Controle Local e Remoto:**  
   - Botões físicos e interface Thinger.io controlam o LED e a buzina.  
3. **Métricas Inteligentes:**  
   - Cada acionamento é contabilizado, e o tempo de uso total é calculado automaticamente.  
4. **Simulação GPS:**  
   - Quando LED ou buzina estão ligados, a posição varia levemente para simular movimento.  
5. **Monitoramento IoT:**  
   - Todos os dados são enviados ao Thinger.io em tempo real.

---

## 🖥️ **Como Executar no Wokwi**
1. Acesse o [Wokwi ESP32 Simulator](https://wokwi.com).  
2. Crie um novo projeto com o **ESP32 Dev Module**.  
3. Adicione o código principal e o `diagram.json`.  
4. Monte os componentes conforme a tabela de hardware.  
5. Clique em ▶ **Play** para iniciar a simulação.  
6. Veja as mensagens no **Serial Monitor** e monitore o dispositivo via **Thinger.io Dashboard**.

---

## 📊 **Resultados Obtidos**
✅ Sistema IoT funcional e responsivo.  
✅ Dados persistentes mesmo após reinicialização.  
✅ Comunicação estável e confiável com Thinger.io.  
✅ Métricas automáticas de uso de LED e buzina.  
✅ Simulação GPS com comportamento dinâmico e realista.

---

## 👨‍💻 **Equipe do Projeto**
| Nome | RM | Função |
|------|----|--------|
| **Alice Nunes** | 559052 | Desenvolvimento ESP32 / Integração IoT |
| **Guilherme Akira** | 556128 | Lógica de Negócio e Integração com Thinger.io |
| **Anne Rezendes** | 556779 | Documentação e Interface IoT |

---

## 🎥 **Demonstração em Vídeo**
[Assista à apresentação e funcionamento do projeto no YouTube](https://www.youtube.com/watch?v=V6_2mS8jhyY)

---

## 🧭 **Próximos Passos**
- Implementar **alertas automáticos de status** no painel IoT.  
- Integrar com o **banco de dados do sistema web**.  
- Adicionar **geofencing** e alertas MQTT em tempo real.  
- Criar **dashboard avançado** com gráficos e histórico de métricas.
