# ESP32 - Gestión de Energía (Light Sleep)

Proyecto desarrollado en **PlatformIO** para la Tarea #6 de Sistemas Embebidos.
Implementa el modo **Light Sleep** del ESP32 con despertar automático mediante
temporizador RTC (`esp_sleep_enable_timer_wakeup`).

## Descripción

El sistema alterna entre dos fases:

1. **Fase activa (8 s):** el ESP32 ejecuta una tarea simulada mientras
   parpadea un LED indicador conectado al pin GPIO2.
2. **Light Sleep (hasta 12 s):** la CPU se suspende mediante
   `esp_light_sleep_start()`. Al despertar por el temporizador RTC, el
   sistema confirma la causa con `esp_sleep_get_wakeup_cause()`, parpadea
   una vez el LED y reinicia el ciclo.

Todo el estado del sistema se reporta también por el **monitor serial**
(115200 baudios).

## Estructura del código

```
src/
 └── main.cpp        # Lógica principal (setup, loop y funciones auxiliares)
platformio.ini        # Configuración del entorno ESP32 + Arduino framework
diagram.json           # Diagrama de simulación para Wokwi
```

Funciones principales:

| Función | Propósito |
|---|---|
| `configurarPines()` | Inicializa el LED de estado |
| `faseActiva()` | Ejecuta la tarea activa durante `TIEMPO_ACTIVO_MS` |
| `prepararYdormir()` | Configura el timer de despertar y entra en Light Sleep |
| `reportarCausaDespertar()` | Verifica con la API oficial que el despertar fue por timer |
| `parpadear()` | Función auxiliar de señalización visual |

## Hardware / Simulación

- Placa: ESP32 DevKit C V4
- LED indicador: GPIO2, con resistencia de 220 Ω a GND
- Simulación disponible en Wokwi mediante `diagram.json`

## Instrucciones de compilación y ejecución

### Requisitos
- [Visual Studio Code](https://code.visualstudio.com/)
- Extensión [PlatformIO IDE](https://platformio.org/platformio-ide)

### Pasos

1. Clonar este repositorio:
   ```bash
   git clone <URL_DEL_REPOSITORIO>
   ```
2. Abrir la carpeta del proyecto en VS Code con PlatformIO instalado.
3. Compilar el proyecto:
   - Click en el ícono de "Build" (✔) en la barra inferior de PlatformIO, o
   - `pio run` desde la terminal.
4. **Simulación en Wokwi:** abrir `diagram.json` con la extensión Wokwi para
   VS Code y ejecutar la simulación directamente (no requiere hardware).
5. **Hardware real (opcional):** conectar el ESP32 por USB, seleccionar el
   puerto correcto y subir el firmware:
   - Click en "Upload" (→) en PlatformIO, o
   - `pio run --target upload`
6. Abrir el monitor serial a 115200 baudios para ver el comportamiento del
   sistema:
   - `pio device monitor`

## Autor

Jhony Choez
