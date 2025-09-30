#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>   // Biblioteca para usar a EEPROM

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

String placaDaMoto = "FIA2025";  // Placa a ser salva
#define EEPROM_SIZE 64            // Tamanho da EEPROM (mínimo 64 bytes)

#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     0
#define UTC_OFFSET_DST 0



#define led 19
#define botao 18
#define botaoEeprom 17

int chavePin = 4; 
int buzzerPin = 16; 
int estadochave = 0; 

bool buzinaState = false; 
bool ledState = false;  

// Função para salvar a placa na EEPROM
void salvarPlaca(String placa) {
  for (int i = 0; i < placa.length(); i++) {
    EEPROM.write(i, placa[i]);  
  }
  EEPROM.write(placa.length(), '\0'); 
  EEPROM.commit(); 
}

// Função para recuperar a placa da EEPROM
String lerPlaca() {
  char placaLida[20]; 
  int i = 0;
  byte b = EEPROM.read(i);
  while (b != '\0' && i < sizeof(placaLida) - 1) {
    placaLida[i] = b;
    i++;
    b = EEPROM.read(i);
  }
  placaLida[i] = '\0'; 
  return String(placaLida);
}

void setup() {
  Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE); 

  pinMode(botaoEeprom, INPUT_PULLUP);  
  pinMode(buzzerPin , OUTPUT); 
  pinMode (chavePin , INPUT); 
  pinMode(botao, INPUT_PULLUP);  
  pinMode(led, OUTPUT);          

  LCD.init();
  LCD.backlight();

  LCD.setCursor(0, 0);
  LCD.print("Ligando...");
  LCD.setCursor(0, 1);
  LCD.print("Esp32");

  delay(2000);

  // Salvar a placa na EEPROM 
  salvarPlaca(placaDaMoto);

  // Ler a placa da EEPROM
  String placaRecuperada = lerPlaca();
  Serial.print("Placa salva na EEPROM: ");
  Serial.println(placaRecuperada);

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Placa:");
  LCD.setCursor(0, 1);
  LCD.print(placaRecuperada);

  delay(2000);

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Conectando...");
  LCD.setCursor(0, 1);
  LCD.print("WiFi");

  WiFi.begin("Wokwi-GUEST", "", 6);  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    attempts++;
    if (attempts > 20) break;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi conectado");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Online");
    LCD.setCursor(0, 1);
    LCD.print(WiFi.localIP());
  } else {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Offline");
    LCD.setCursor(0, 1);
    LCD.print("Erro Conexao");
  }
}

void loop() {
  static bool lastButtonState = HIGH;  
  bool buttonState = digitalRead(botao);  

static int ultimoEstadoEeprom = HIGH; 
int estadoBotaoEeprom = digitalRead(botaoEeprom);

if (ultimoEstadoEeprom == HIGH && estadoBotaoEeprom == LOW) {

  String placaRecuperada = lerPlaca();
  Serial.print("Placa recuperada da EEPROM: ");
  Serial.println(placaRecuperada);

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Placa:");
  LCD.setCursor(0, 1);
  LCD.print(placaRecuperada);
}

ultimoEstadoEeprom = estadoBotaoEeprom;

  // --- BOTÃO DO LED ---
  if (lastButtonState == HIGH && buttonState == LOW) {
    ledState = !ledState;

    if (ledState) {
      digitalWrite(led, HIGH);  
        LCD.clear();
      Serial.println("Led ativado");
      LCD.setCursor(0, 0);
      LCD.print("Led ativado");
    } else {
      digitalWrite(led, LOW); 
        LCD.clear();
      Serial.println("Led desativado");
      LCD.setCursor(0, 0);
      LCD.print("Led desligado");
    }
  }
  lastButtonState = buttonState;

  // --- BOTÃO/CHAVE DA BUZINA ---
  static int lastChaveState = LOW;  
  int chaveAtual = digitalRead(chavePin);

  if (lastChaveState == LOW && chaveAtual == HIGH) {
   
    buzinaState = !buzinaState;

    if (buzinaState) {
      digitalWrite(buzzerPin, HIGH);
        LCD.clear();
      Serial.println("Buzina ativada");
      LCD.setCursor(0, 1);
      LCD.print("Buzina ativada "); 
    } else {
      digitalWrite(buzzerPin, LOW);
        LCD.clear();
      Serial.println("Buzina desativada");
      LCD.setCursor(0, 1);
      LCD.print("Buzina desligada ");
    }
  }

  

  lastChaveState = chaveAtual;

  delay(100);
}
