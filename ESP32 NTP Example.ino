#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <ThingerESP32.h>
#include <WebServer.h>

// =====================
// CONFIGURAÇÕES
// =====================
#define EEPROM_SIZE 128
#define USERNAME "alice-santossss"
#define DEVICE_ID "esp-treino-alice-fiap"
#define DEVICE_CREDENTIAL "3Xmq@BJe7CKKy6Gb"

#define SSID "Wokwi-GUEST"
#define SSID_PASSWORD ""

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
WebServer server(80);

String placaDaMoto = "FIA2025";
String latitude = "-23.5226110933519";   
String longitude = "-46.73999745548312";  

#define led 19
#define botao 18
#define botaoEeprom 17
int chavePin = 4;
int buzzerPin = 16;

bool buzinaState = false;
bool ledState = false;

// =====================
// VARIÁVEIS DE MÉTRICAS
// =====================
unsigned long ledLigadoDesde = 0;
unsigned long tempoLedLigadoTotal = 0;
int vezesLedLigou = 0;

unsigned long buzinaLigadaDesde = 0;
unsigned long tempoBuzinaTotal = 0;
int vezesBuzinaLigou = 0;

// =====================
// EEPROM – SALVAR/LEITURA
// =====================
void salvarPlaca(String placa) {
  for (int i = 0; i < placa.length(); i++) EEPROM.write(i, placa[i]);
  EEPROM.write(placa.length(), '\0');
  EEPROM.commit();
}

void salvarLatitude(String lat){
  int base = 50;
  for(int i = 0; i < lat.length(); i++) EEPROM.write(base + i, lat[i]);
  EEPROM.write(base + lat.length(), '\0');
  EEPROM.commit();
}

void salvarLongitude(String lon){
  int base = 70;
  for(int i = 0; i < lon.length(); i++) EEPROM.write(base + i, lon[i]);
  EEPROM.write(base + lon.length(), '\0');
  EEPROM.commit();
}

String lerLatitude(){
  int base = 50;
  char lat[20];
  int i = 0;
  byte b = EEPROM.read(base);
  while(b != '\0' && i < sizeof(lat)-1){
    lat[i++] = b;
    b = EEPROM.read(base+i);
  }
  lat[i] = '\0';
  return String(lat);
}

String lerLongitude(){
  int base = 70;
  char lon[20];
  int i = 0;
  byte b = EEPROM.read(base);
  while(b != '\0' && i < sizeof(lon)-1){
    lon[i++] = b;
    b = EEPROM.read(base+i);
  }
  lon[i] = '\0';
  return String(lon);
}

String lerPlaca() {
  char buf[20];
  int i = 0;
  byte b = EEPROM.read(0);
  while (b != '\0' && i < sizeof(buf)-1) {
    buf[i++] = b;
    b = EEPROM.read(i);
  }
  buf[i] = '\0';
  return String(buf);
}

// =====================
// HANDLER API
// =====================
void handleAPI() {
  String json = "{";
  json += "\"placa\":\"" + lerPlaca() + "\",";
  json += "\"ledState\":" + String(ledState ? "true" : "false") + ",";
  json += "\"vezesLedLigou\":" + String(vezesLedLigou) + ",";
  json += "\"tempoLedLigadoTotal\":" + String(tempoLedLigadoTotal) + ",";
  json += "\"buzinaState\":" + String(buzinaState ? "true" : "false") + ",";
  json += "\"vezesBuzinaLigou\":" + String(vezesBuzinaLigou) + ",";
  json += "\"tempoBuzinaTotal\":" + String(tempoBuzinaTotal) + ",";
  json += "\"latitude\":\"" + latitude + "\",";
  json += "\"longitude\":\"" + longitude + "\"";
  json += "}";
  server.send(200, "application/json", json);
}

// =====================
// SETUP
// =====================
void setup() {
  Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE);

  pinMode(botaoEeprom, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(chavePin, INPUT);
  pinMode(botao, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  delay(1500);

  // Salvar local inicial
  salvarPlaca(placaDaMoto);
  salvarLatitude(latitude);
  salvarLongitude(longitude);

  latitude = lerLatitude();
  longitude = lerLongitude();

  Serial.println("Placa salva: " + lerPlaca());

  // =====================
  // THINGER.IO RESOURCES
  // =====================
  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["placa"] >> [](pson &out){ out = lerPlaca(); };

  thing["led"] << [](pson &in){
    if(in.is_empty()){
      in = ledState;
    } else {
      bool novoEstado = in;
      if (!ledState && novoEstado){
        vezesLedLigou++;
        ledLigadoDesde = millis();
      }
      if (ledState && !novoEstado){
        tempoLedLigadoTotal += (millis() - ledLigadoDesde)/1000;
      }
      ledState = novoEstado;
      digitalWrite(led, ledState ? HIGH : LOW);
    }
  };

  thing["buzina"] << [](pson &in){
    if(in.is_empty()){
      in = buzinaState;
    } else {
      bool novoEstado = in;
      if (!buzinaState && novoEstado){
        vezesBuzinaLigou++;
        buzinaLigadaDesde = millis();
      }
      if (buzinaState && !novoEstado){
        tempoBuzinaTotal += (millis() - buzinaLigadaDesde)/1000;
      }
      buzinaState = novoEstado;
      digitalWrite(buzzerPin, buzinaState ? HIGH : LOW);
    }
  };

  thing["metricas"] >> [](pson &out){
    out["led_tempo_total"] = tempoLedLigadoTotal;
    out["led_vezes"] = vezesLedLigou;
    out["buzina_tempo_total"] = tempoBuzinaTotal;
    out["buzina_vezes"] = vezesBuzinaLigou;
  };

  thing["gps"] >> [](pson &out){
    if (ledState || buzinaState){
      out["status"] = "Em deslocamento";
      out["latitude"] = latitude.toFloat() + 0.0001;
      out["longitude"] = longitude.toFloat() + 0.0001;
    } else {
      out["status"] = "Parado na oficina";
      out["latitude"] = latitude;
      out["longitude"] = longitude;
    }
  };

  // =====================
  // INICIAR WEB SERVER
  // =====================
  server.on("/api", handleAPI);
  server.begin();
}

// =====================
// LOOP
// =====================
void loop() {
  thing.handle();        // mantém Thinger funcionando
  server.handleClient(); // atende requisições API

  // Botão do LED
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(botao);
  if (lastButtonState == HIGH && buttonState == LOW){
    bool novoEstado = !ledState;
    if (!ledState && novoEstado){
      vezesLedLigou++;
      ledLigadoDesde = millis();
    }
    if (ledState && !novoEstado){
      tempoLedLigadoTotal += (millis() - ledLigadoDesde)/1000;
    }
    ledState = novoEstado;
    digitalWrite(led, ledState);
    thing.stream("led");
    thing.stream("gps");
  }
  lastButtonState = buttonState;

  // Chave da Buzina
  static int lastChaveState = LOW;
  int chaveAtual = digitalRead(chavePin);
  if (lastChaveState == LOW && chaveAtual == HIGH){
    bool novoEstado = !buzinaState;
    if (!buzinaState && novoEstado){
      vezesBuzinaLigou++;
      buzinaLigadaDesde = millis();
    }
    if (buzinaState && !novoEstado){
      tempoBuzinaTotal += (millis() - buzinaLigadaDesde)/1000;
    }
    buzinaState = novoEstado;
    digitalWrite(buzzerPin, buzinaState);
    thing.stream("buzina");
    thing.stream("gps");
  }
  lastChaveState = chaveAtual;

  delay(100);
}
