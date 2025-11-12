#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// ------------------- PINOS -------------------
#define DHTPIN 15
#define DHTTYPE DHT22
#define POT_PIN 34
#define LDR_PIN 35

// LEDs
#define LED_VERDE 2
#define LED_AMARELO 4
#define LED_VERMELHO 5
#define LED_AZUL 18

// ------------------- WI-FI -------------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ------------------- MQTT -------------------
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;                // Porta padrão MQTT (sem SSL)
const char* mqtt_client_id = "ESP32SolarBot";
const char* mqtt_topic = "usina/monitoramento";

WiFiClient espClient;
PubSubClient client(espClient);

DHT dht(DHTPIN, DHTTYPE);

// ------------------- FUNÇÕES -------------------
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(mqtt_client_id)) {
      Serial.println("✅ Conectado ao broker MQTT!");
      client.subscribe(mqtt_topic); // se quiser ouvir também
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5s...");
      delay(5000);
    }
  }
}

// ------------------- SETUP -------------------
void setup() {
  Serial.begin(115200);
  dht.begin();

  // LEDs
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  // Desliga todos no início
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AZUL, LOW);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  Serial.println("Sistema iniciado. Aguardando leitura dos sensores...");
}

// ------------------- LOOP -------------------
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura dos sensores
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  int potValue = analogRead(POT_PIN);
  int ldrValue = analogRead(LDR_PIN);

  // Normalizações
  float energia = map(potValue, 0, 4095, 0, 100);
  float eficiencia = map(ldrValue, 0, 4095, 0, 100); // maior luz → maior eficiência

  // Envio MQTT
  char msg[200];
  snprintf(msg, sizeof(msg),
           "{\"temperatura\": %.2f, \"umidade\": %.2f, \"energia\": %.2f, \"eficiencia\": %.2f}",
           temperatura, umidade, energia, eficiencia);

  client.publish(mqtt_topic, msg);
  Serial.println(msg);

  // ---------- LÓGICA DOS LEDS ----------
  // Vermelho: superaquecimento
  // Amarelo: baixa eficiência
  // Azul: baixa energia
  // Verde: tudo ok

  if (temperatura > 45) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AZUL, LOW);
  } else if (eficiencia < 40) {
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AZUL, LOW);
  } else if (energia < 30) {
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AZUL, LOW);
  }

  delay(2000);
}
