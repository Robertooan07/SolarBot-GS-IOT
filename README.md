# Membros:

HENRIQUE PARRA – RM551973  
ROBERTO OLIVEIRA – RM551460   
TONY WILLIAN SEGALIN – RM550667

# Problema
A baixa eficiência e a falta de monitoramento remoto em usinas solares podem gerar perdas significativas de energia. Este projeto visa criar uma solução IoT para acompanhar temperatura, luminosidade e eficiência em tempo real.

# Solução

Sistema de monitoramento IoT usando ESP32 com sensores DHT22, LDR e potenciômetro, enviando dados via MQTT em tempo real para visualização no Node-RED Dashboard.

# Dependências

Bibliotecas:
- WiFi.h
- PubSubClient.h
- DHT.h

# Simulação Wokwi

https://wokwi.com/projects/305569599398609473 

# Video Explicativo

# MQTT
Tópico utilizado: usina/monitoramento
Broker: test.mosquitto.org
Porta: 1883

# Funcionamento dos LEDs

🔴 Vermelho: superaquecimento
🟡 Amarelo: baixa eficiência
🔵 Azul: baixa energia
🟢 Verde: tudo normal