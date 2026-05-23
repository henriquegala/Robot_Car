// ==========================================
// PROJETO: Rover DETI 01 - Teste de Bancada
// ==========================================

// Pinos do Motor Esquerdo (Motor 1)
const int IN1 = 23;
const int IN2 = 22;
const int EN1 = 21; // Controlo de Velocidade (PWM) do Motor Esquerdo

// Pinos do Motor Direito (Motor 2)
const int IN3 = 19;
const int IN4 = 18;
const int EN2 = 5;  // Controlo de Velocidade (PWM) do Motor Direito

void setup() {
  // Configura todos os pinos de controlo como saídas
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);

  // Inicializa a comunicação Serial para debug na consola
  Serial.begin(115200);
  Serial.println("======================================");
  Serial.println(" Rover DETI 01 - Firmware Iniciado!  ");
  Serial.println("======================================");
}

void loop() {
  // 1. Mover para a frente a velocidade média (150 de 255) por 3 segundos
  Serial.println("[AÇÃO] A mover para a FRENTE...");
  moverFrente(150);
  delay(3000);

  // 2. Parar por 2 segundos
  Serial.println("[AÇÃO] PARADO.");
  parar();
  delay(2000);

  // 3. Mover para trás a velocidade mais lenta (100 de 255) por 3 segundos
  Serial.println("[AÇÃO] A mover para TRÁS...");
  moverTras(100);
  delay(3000);

  // 4. Parar por 2 segundos
  Serial.println("[AÇÃO] PARADO.");
  parar();
  delay(2000);
}

// --- FUNÇÕES DE CONTROLO DE MOVIMENTO ---

void moverFrente(int velocidade) {
  // Motor Esquerdo 
  digitalWrite(IN1, LOW);  // Invertido
  digitalWrite(IN2, HIGH); // Invertido
  analogWrite(EN1, velocidade);

  // Motor Direito 
  digitalWrite(IN3, HIGH); // Invertido
  digitalWrite(IN4, LOW);  // Invertido
  analogWrite(EN2, velocidade);
}

void moverTras(int velocidade) {
  // Motor Esquerdo 
  digitalWrite(IN1, HIGH); // Invertido
  digitalWrite(IN2, LOW);  // Invertido
  analogWrite(EN1, velocidade);

  // Motor Direito 
  digitalWrite(IN3, LOW);  // Invertido
  digitalWrite(IN4, HIGH); // Invertido
  analogWrite(EN2, velocidade);
}

void parar() {
  // Desliga os sinais lógicos e corta o PWM
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN2, 0);
}