# Membros:

HENRIQUE PARRA – RM551973  
ROBERTO OLIVEIRA – RM551460   
TONY WILLIAN SEGALIN – RM550667

# Problema
Usinas solares frequentemente enfrentam queda de desempenho por fatores como aquecimento excessivo, variação de luminosidade ou falhas que passam despercebidas. Sem um acompanhamento contínuo, esses desvios podem resultar em desperdício de energia e redução da vida útil dos equipamentos. Diante disso, surge a necessidade de um sistema acessível e confiável que permita monitorar remotamente parâmetros críticos — como temperatura, intensidade luminosa e eficiência dos painéis — oferecendo informações precisas para decisões rápidas e manutenção preventiva.

# Solução

a solução é um ecossistema IoT completo baseado em um ESP32 integrado a sensores DHT22 (temperatura e umidade), LDR (intensidade luminosa) e um potenciômetro para simular variações de eficiência. Esses dados são transmitidos continuamente através do protocolo MQTT para um broker, onde são processados e exibidos em tempo real em um dashboard interativo no Node-RED. A solução proporciona visualização clara, comunicação leve e uma base sólida para futuras expansões, como alertas automáticos, armazenamento em nuvem ou análise preditiva.

# Dependências

Bibliotecas:
- WiFi.h
- PubSubClient.h
- DHT.h

# Simulação Wokwi

https://wokwi.com/projects/447406414735547393 

# Video Explicativo

https://youtu.be/rH6Scso4AfI

# MQTT
Tópico utilizado: usina/monitoramento
Broker: test.mosquitto.org
Porta: 1883

# Funcionamento dos LEDs

🔴 Vermelho: superaquecimento
🟡 Amarelo: baixa eficiência
🔵 Azul: baixa energia
🟢 Verde: tudo normal