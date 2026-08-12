// ==========================================
// PROJETO: Rover DETI 01 - Teste do Sensor Ultrassónico
// ==========================================

const int TRIG_PIN = 25; // Pino de disparo (Trigger) -> Saída da ESP32
const int ECHO_PIN = 26; // Pino de retorno (Echo) -> Entrada da ESP32 (Com Divisor de Tensão!)

void setup() {
  Serial.begin(115200);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Garante que o pino Trig começa em estado baixo
  digitalWrite(TRIG_PIN, LOW);
  
  Serial.println("\n--------------------------------------");
  Serial.println(" Teste do Sensor HC-SR04 Iniciado!   ");
  Serial.println("--------------------------------------");
}

void loop() {
  // 1. Envia um pulso de trigger de 10 microsegundos
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 2. Mede a duração do pulso de retorno (Echo) em microsegundos
  long duracao = pulseIn(ECHO_PIN, HIGH);

  // 3. Calcula a distância em centímetros
  // Velocidade do som na atmosfera: ~343 m/s (0.0343 cm/us)
  // Fórmula: Distância = (Tempo * 0.0343) / 2 (dividido por 2 porque o som vai e volta)
  float distancia = (duracao * 0.0343) / 2.0;

  // 4. Imprime no Serial Monitor
  Serial.print("Distancia: ");
  if (distancia >= 400 || distancia <= 2) {
    Serial.println("Fora de alcance (mecanicamente instavel)");
  } else {
    Serial.print(distancia);
    Serial.println(" cm");
  }

  delay(500); // Medição a cada meio segundo para facilitar a leitura
}