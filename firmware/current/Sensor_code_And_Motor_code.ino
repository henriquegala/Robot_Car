#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Rover_DETI_01";
const char* password = "deti-rover-ua";

WebServer server(80);

// Pinos dos Motores
const int IN1 = 23; const int IN2 = 22; const int EN1 = 21;
const int IN3 = 19; const int IN4 = 18; const int EN2 = 5;

// Pinos do Sensor Ultrassónico
const int TRIG_PIN = 25;
const int ECHO_PIN = 26;

// Variáveis de Estado Globais
bool modoAutonomo = false;
float distanciaAtual = 100.0;
unsigned long tempoUltimaLeitura = 0;
const unsigned long intervaloLeitura = 100; // Ler sensor a cada 100ms (não-bloqueante)

// ==========================================
// INTERFACE WEB ATUALIZADA (Com Telemetria e Modo Auto)
// ==========================================
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Rover DETI 01 - Consola</title>
  <style>
    body { font-family: 'Segoe UI', Arial, sans-serif; text-align: center; background-color: #121212; color: #ffffff; margin: 0; padding: 20px; user-select: none; -webkit-user-select: none; }
    h1 { color: #4CAF50; margin-bottom: 5px; }
    p { color: #888; margin-top: 0; font-size: 14px; }
    
    /* Painel de Telemetria */
    .telemetria-panel { background-color: #1e1e1e; border: 1px solid #333; border-radius: 15px; padding: 15px; max-width: 300px; margin: 20px auto; font-family: monospace; font-size: 16px; color: #00FF00; }
    
    .controls-container { display: flex; justify-content: space-around; max-width: 500px; margin: 20px auto; }
    .column { display: flex; flex-direction: column; align-items: center; gap: 15px; }
    .column-title { color: #888; font-weight: bold; font-size: 14px; }

    .btn { background-color: #1e1e1e; color: #4CAF50; border: 2px solid #4CAF50; border-radius: 20px; width: 85px; height: 90px; font-size: 32px; font-weight: bold; cursor: pointer; outline: none; transition: all 0.1s ease; display: flex; align-items: center; justify-content: center; }
    .btn:active { background-color: #4CAF50; color: #121212; transform: scale(0.95); }
    
    /* Botão de Modo Autónomo */
    .btn-auto { background-color: #1e1e1e; color: #ff9800; border: 2px solid #ff9800; border-radius: 15px; width: 200px; height: 50px; font-size: 16px; font-weight: bold; margin: 20px auto; cursor: pointer; transition: all 0.1s ease; }
    .btn-auto.active { background-color: #ff9800; color: #121212; }
  </style>
</head>
<body>
  <h1>Rover DETI 01</h1>
  <p>Consola de Controlo Integrada</p>
  
  <!-- Painel de Leitura do Sensor em Tempo Real -->
  <div class="telemetria-panel" id="distancia-display">Obstáculo: -- cm</div>
  
  <div class="controls-container">
    <div class="column">
      <div class="column-title">ESQUERDA</div>
      <button class="btn" onmousedown="motor('L', 'frente')" ontouchstart="motor('L', 'frente')" onmouseup="motor('L', 'parar')" ontouchend="motor('L', 'parar')">▲</button>
      <button class="btn" onmousedown="motor('L', 'tras')" ontouchstart="motor('L', 'tras')" onmouseup="motor('L', 'parar')" ontouchend="motor('L', 'parar')">▼</button>
    </div>
    
    <div class="column">
      <div class="column-title">DIREITA</div>
      <button class="btn" onmousedown="motor('R', 'frente')" ontouchstart="motor('R', 'frente')" onmouseup="motor('R', 'parar')" ontouchend="motor('R', 'parar')">▲</button>
      <button class="btn" onmousedown="motor('R', 'tras')" ontouchstart="motor('R', 'tras')" onmouseup="motor('R', 'parar')" ontouchend="motor('R', 'parar')">▼</button>
    </div>
  </div>

  <button class="btn-auto" id="auto-btn" onclick="ativarAutonomo()">MODO AUTÓNOMO</button>

  <script>
    let autoAtivo = false;

    function motor(lado, acao) {
      if (autoAtivo) {
        // Se usarmos controlo manual, o modo autónomo desliga-se visualmente
        autoAtivo = false;
        document.getElementById('auto-btn').classList.remove('active');
      }
      fetch('/control?motor=' + lado + '&dir=' + acao);
    }

    function ativarAutonomo() {
      autoAtivo = !autoAtivo;
      const btn = document.getElementById('auto-btn');
      if (autoAtivo) {
        btn.classList.add('active');
        fetch('/setmode?mode=auto');
      } else {
        btn.classList.remove('active');
        fetch('/setmode?mode=manual');
      }
    }

    // Pedir a distância à ESP32 a cada 400ms para atualizar o painel
    setInterval(() => {
      fetch('/getdist')
        .then(response => response.text())
        .then(data => {
          document.getElementById('distancia-display').innerText = "Obstaculo: " + data + " cm";
        })
        .catch(err => console.error("Erro na telemetria:", err));
    }, 400);
  </script>
</body>
</html>
)rawliteral";

// --- FUNÇÃO DE LEITURA DO SENSOR ---
float obterDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // pulseIn com timeout de 25000us (~4.2 metros max) para evitar bloqueio do servidor
  long duracao = pulseIn(ECHO_PIN, HIGH, 25000); 
  if (duracao == 0) return 400.0; // Se falhar ou estiver fora de alcance, assume 4 metros
  
  return (duracao * 0.0343) / 2.0;
}

// --- DRIVERS DOS MOTORES (Calibrados) ---
void controlarEsquerdo(String dir, int vel) {
  if (dir == "frente") {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); analogWrite(EN1, vel);
  } else if (dir == "tras") {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  analogWrite(EN1, vel);
  } else {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  analogWrite(EN1, 0);
  }
}

void controlarDireito(String dir, int vel) {
  if (dir == "frente") {
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  analogWrite(EN2, vel);
  } else if (dir == "tras") {
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); analogWrite(EN2, vel);
  } else {
    digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  analogWrite(EN2, 0);
  }
}

void pararTudo() {
  controlarEsquerdo("parar", 0);
  controlarDireito("parar", 0);
}

// ==========================================
// CONFIGURAÇÃO E LOOP
// ==========================================

void setup() {
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(EN1, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(EN2, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  
  pararTudo();
  digitalWrite(TRIG_PIN, LOW);

  WiFi.softAP(ssid, password);
  Serial.println("\nRover DETI - Firmware Integrado!");
  Serial.print("Acede a: http://");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.send(200, "text/html", index_html);
  });

  // Rota de controlo manual (Se acedida, desliga o modo autónomo imediatamente)
  server.on("/control", []() {
    modoAutonomo = false; // Override de segurança!
    if (server.hasArg("motor") && server.hasArg("dir")) {
      String motor = server.arg("motor");
      String direcao = server.arg("dir");
      if (motor == "L") controlarEsquerdo(direcao, 150);
      if (motor == "R") controlarDireito(direcao, 150);
      server.send(200, "text/plain", "OK");
    }
  });

  // Rota para alternar entre Manual e Autónomo
  server.on("/setmode", []() {
    if (server.hasArg("mode")) {
      String mode = server.arg("mode");
      if (mode == "auto") {
        modoAutonomo = true;
        Serial.println("[SISTEMA] Modo AUTÓNOMO Ativado!");
      } else {
        modoAutonomo = false;
        pararTudo();
        Serial.println("[SISTEMA] Retornado ao modo MANUAL.");
      }
      server.send(200, "text/plain", "OK");
    }
  });

  // Rota para o browser ler a distância atual (Telemetria)
  server.on("/getdist", []() {
    server.send(200, "text/plain", String(distanciaAtual, 1));
  });

  server.begin();
}

void loop() {
  server.handleClient();

  unsigned long tempoAtual = millis();
  
  // Executa a leitura do sensor a cada 100ms de forma não-bloqueante
  if (tempoAtual - tempoUltimaLeitura >= intervaloLeitura) {
    tempoUltimaLeitura = tempoAtual;
    distanciaAtual = obterDistancia();
  }

  // LÓGICA DE DECISÃO DO MODO AUTÓNOMO
  if (modoAutonomo) {
    if (distanciaAtual < 20.0) {
      // OBSTÁCULO DETETADO! (Menos de 20cm)
      Serial.print("[AUTÓNOMO] Obstáculo! Distância: ");
      Serial.print(distanciaAtual);
      Serial.println(" cm. A desviar...");
      
      // Gira no próprio eixo para a direita para procurar caminho livre
      controlarEsquerdo("frente", 140);
      controlarDireito("tras", 140);
    } else {
      // CAMINHO LIVRE
      controlarEsquerdo("frente", 130);
      controlarDireito("frente", 130);
    }
  }
}