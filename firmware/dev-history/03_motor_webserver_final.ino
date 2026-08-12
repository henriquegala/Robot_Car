#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Rover_DETI_01";
const char* password = "deti-rover-ua";

WebServer server(80);

// Pinos dos Motores
const int IN1 = 23; const int IN2 = 22; const int EN1 = 21;
const int IN3 = 19; const int IN4 = 18; const int EN2 = 5;

// ==========================================
// INTERFACE WEB (Dual Control Panel)
// ==========================================
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Rover DETI 01 - Tank Control</title>
  <style>
    body { font-family: 'Segoe UI', Arial, sans-serif; text-align: center; background-color: #121212; color: #ffffff; margin: 0; padding: 20px; user-select: none; -webkit-user-select: none; }
    h1 { color: #4CAF50; margin-bottom: 5px; }
    p { color: #888; margin-top: 0; font-size: 14px; }
    
    /* Layout de duas colunas (Esquerda e Direita) */
    .controls-container { display: flex; justify-content: space-around; max-width: 500px; margin: 30px auto; }
    .column { display: flex; flex-direction: column; align-items: center; gap: 20px; }
    .column-title { color: #888; font-weight: bold; font-size: 16px; margin-bottom: 5px; }

    /* Botões Verticais tipo Alavanca */
    .btn { background-color: #1e1e1e; color: #4CAF50; border: 2px solid #4CAF50; border-radius: 20px; width: 85px; height: 100px; font-size: 32px; font-weight: bold; cursor: pointer; outline: none; transition: all 0.1s ease; display: flex; align-items: center; justify-content: center; }
    .btn:active { background-color: #4CAF50; color: #121212; transform: scale(0.95); }
  </style>
</head>
<body>
  <h1>Rover DETI 01</h1>
  <p>Modo Tank Steering - Controlo Momentaneo</p>
  
  <div class="controls-container">
    <!-- COLUNA MOTOR ESQUERDO -->
    <div class="column">
      <div class="column-title">ESQUERDA</div>
      <button class="btn" 
              onmousedown="motor('L', 'frente')" ontouchstart="motor('L', 'frente')"
              onmouseup="motor('L', 'parar')" ontouchend="motor('L', 'parar')" onmouseleave="motor('L', 'parar')">▲</button>
      <button class="btn" 
              onmousedown="motor('L', 'tras')" ontouchstart="motor('L', 'tras')"
              onmouseup="motor('L', 'parar')" ontouchend="motor('L', 'parar')" onmouseleave="motor('L', 'parar')">▼</button>
    </div>
    
    <!-- COLUNA MOTOR DIREITO -->
    <div class="column">
      <div class="column-title">DIREITA</div>
      <button class="btn" 
              onmousedown="motor('R', 'frente')" ontouchstart="motor('R', 'frente')"
              onmouseup="motor('R', 'parar')" ontouchend="motor('R', 'parar')" onmouseleave="motor('R', 'parar')">▲</button>
      <button class="btn" 
              onmousedown="motor('R', 'tras')" ontouchstart="motor('R', 'tras')"
              onmouseup="motor('R', 'parar')" ontouchend="motor('R', 'parar')" onmouseleave="motor('R', 'parar')">▼</button>
    </div>
  </div>

  <script>
    // Envia o estado de cada motor de forma assíncrona
    function motor(lado, acao) {
      fetch('/control?motor=' + lado + '&dir=' + acao)
        .then(response => console.log(lado + ' -> ' + acao))
        .catch(error => console.error('Erro:', error));
    }
  </script>
</body>
</html>
)rawliteral";

// --- DRIVERS DE CONTROLO INDEPENDENTE DOS MOTORES ---

void controlarEsquerdo(String dir) {
  if (dir == "frente") {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); analogWrite(EN1, 150);
  } else if (dir == "tras") {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  analogWrite(EN1, 150);
  } else {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  analogWrite(EN1, 0); // Parar
  }
}

void controlarDireito(String dir) {
  if (dir == "frente") {
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  analogWrite(EN2, 150);
  } else if (dir == "tras") {
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); analogWrite(EN2, 150);
  } else {
    digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  analogWrite(EN2, 0); // Parar
  }
}

// ==========================================
// CONFIGURAÇÃO
// ==========================================

void setup() {
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(EN1, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(EN2, OUTPUT);
  
  // Garante que tudo começa desligado
  controlarEsquerdo("parar");
  controlarDireito("parar");

  WiFi.softAP(ssid, password);
  Serial.println("\nRover DETI - Modo Tank Steering Iniciado!");
  Serial.print("Acede a: http://");
  Serial.println(WiFi.softAPIP());

  // Rota para carregar a página
  server.on("/", []() {
    server.send(200, "text/html", index_html);
  });

  // Rota inteligente unificada para controlar os motores por parâmetros de URL
  // Exemplo: /control?motor=L&dir=frente
  server.on("/control", []() {
    if (server.hasArg("motor") && server.hasArg("dir")) {
      String motor = server.arg("motor");
      String direcao = server.arg("dir");
      
      if (motor == "L") {
        controlarEsquerdo(direcao);
      } else if (motor == "R") {
        controlarDireito(direcao);
      }
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Dados Invalidos");
    }
  });

  server.begin();
}

void loop() {
  server.handleClient();
}