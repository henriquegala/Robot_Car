#include <WiFi.h>
#include <WebServer.h>

// Definições da Rede Wi-Fi da ESP32
const char* ssid = "Rover_DETI_01";      // Nome da rede que vai aparecer no teu telemóvel
const char* password = "deti-rover-ua";  // Palavra-passe da rede (mínimo 8 caracteres)

// Criação do objeto do servidor Web na porta padrão HTTP (80)
WebServer server(80);

// Pinos dos Motores (Mantemos a estrutura da Fase 1)
const int IN1 = 23; const int IN2 = 22; const int EN1 = 21;
const int IN3 = 19; const int IN4 = 18; const int EN2 = 5;

void setup() {
  Serial.begin(115200);
  
  // 1. Configurar Pinos dos Motores
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(EN1, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(EN2, OUTPUT);
  parar(); // Garante que os motores começam desligados

  // 2. Configurar a ESP32 como Access Point (AP)
  Serial.println("\nA configurar o Access Point...");
  WiFi.softAP(ssid, password);

  // O IP padrão de qualquer Access Point ESP32 é 192.168.4.1
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Rede Wi-Fi criada: ");
  Serial.println(ssid);
  Serial.print("Endereço IP do Rover: ");
  Serial.println(IP);

  // 3. Definir as "Rotas" do Servidor
  // Quando alguém aceder à raiz "/" (ex: http://192.168.4.1/), chama a função tratarRaiz
  server.on("/", tratarRaiz);

  // 4. Iniciar o Servidor
  server.begin();
  Serial.println("Servidor Web HTTP iniciado com sucesso!");
}

void loop() {
  // Esta linha é crucial. Ela diz à ESP32 para verificar constantemente 
  // se há novos pedidos de browsers e responder-lhes.
  server.handleClient();
}

// --- FUNÇÃO DE RESPOSTA DO SERVIDOR ---

// Esta função envia uma página de texto simples de volta para o browser do utilizador
void tratarRaiz() {
  // Código HTTP 200 (OK), tipo de conteúdo "text/plain" (texto puro)
  server.send(200, "text/plain", "Ola do Rover DETI 01! O servidor Web esta a funcionar!");
}

// --- FUNÇÃO PARA PARAR MOTORES (SEGURANÇA) ---
void parar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); analogWrite(EN1, 0);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); analogWrite(EN2, 0);
}