#include <Arduino.h>
#include "esp_sleep.h"

// PINES
const uint8_t PIN_LED_ESTADO = 2;    // LED indicador (activo / dormido)

// TIEMPOS 
const uint32_t TIEMPO_ACTIVO_MS   = 8000;              // 8 s de tarea activa
const uint64_t TIEMPO_SLEEP_US    = 12ULL * 1000000ULL; // 12 s de light sleep

uint32_t contadorCiclos = 0;

void configurarPines();
void faseActiva();
void prepararYdormir();
void reportarCausaDespertar();
void parpadear(uint8_t veces, uint16_t msDelay);

void setup() {
  Serial.begin(115200);
  delay(300);
  configurarPines();

  Serial.println(" Sistema de gestion de energia - ESP32 Light Sleep");
}

void loop() {
  contadorCiclos++;
  Serial.printf("\n--- Ciclo #%u ---\n", contadorCiclos);

  faseActiva();          // 1. tarea activa
  prepararYdormir();     // 2. entra a Light Sleep real
  reportarCausaDespertar(); // 3. informa por qué despertó
}

void configurarPines() {
  pinMode(PIN_LED_ESTADO, OUTPUT);
  digitalWrite(PIN_LED_ESTADO, LOW);
}

// Simula la tarea "productiva" del sistema mientras está despierto
void faseActiva() {
  Serial.println("[ACTIVO] Ejecutando tarea principal...");
  uint32_t inicio = millis();

  while (millis() - inicio < TIEMPO_ACTIVO_MS) {
    digitalWrite(PIN_LED_ESTADO, HIGH);
    delay(150);
    digitalWrite(PIN_LED_ESTADO, LOW);
    delay(150);
  }
  Serial.println("[ACTIVO] Tarea finalizada.");
}

// Configura la fuente de despertar (temporizador) y entra en Light Sleep real
void prepararYdormir() {
  Serial.println("[SLEEP] Configurando temporizador de despertar...");

  // Despertar por temporizador RTC
  esp_sleep_enable_timer_wakeup(TIEMPO_SLEEP_US);

  Serial.println("[SLEEP] Entrando en LIGHT SLEEP...");
  Serial.flush(); // asegura que el UART termine de enviar antes de dormir

  esp_light_sleep_start();   // aquí realmente se suspende la CPU

  // La ejecución continúa exactamente aquí al despertar
  Serial.println("[WAKE] CPU reactivada.");
}

// Usa la API oficial para confirmar que el despertar vino del temporizador
void reportarCausaDespertar() {
  esp_sleep_wakeup_cause_t causa = esp_sleep_get_wakeup_cause();

  if (causa == ESP_SLEEP_WAKEUP_TIMER) {
    Serial.println("[CAUSA] Despertar por TEMPORIZADOR (timer RTC).");
    parpadear(1, 400);
  } else {
    Serial.printf("[CAUSA] Otra causa inesperada (%d).\n", causa);
  }
}

void parpadear(uint8_t veces, uint16_t msDelay) {
  for (uint8_t i = 0; i < veces; i++) {
    digitalWrite(PIN_LED_ESTADO, HIGH);
    delay(msDelay);
    digitalWrite(PIN_LED_ESTADO, LOW);
    delay(msDelay);
  }
}
