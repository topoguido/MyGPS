GPS usando TinyGPSPlus

## Guia de conexionado segun `MyGPS.ino`

Este documento describe que hay conectado a cada pin segun el codigo fuente actual.
Cuando algo no aparece conectado de forma explicita pero se puede inferir por la libreria o por el bus usado, queda aclarado como inferencia.

## Resumen de hardware detectado

Segun `MyGPS.ino`, el proyecto usa:

- Un GPS por UART hardware
- Un display LCD por I2C usando `hd44780_I2Cexp`
- Una tarjeta SD por SPI
- Una salida digital de estado en `GPIO13`
- WiFi en modo Access Point

## Pines usados por el codigo

| Pin Wemos | GPIO | Uso segun codigo | Evidencia |
| --- | --- | --- | --- |
| `D1` | `GPIO5` | `SCL` del LCD I2C | `Wire.begin();` + `hd44780_I2Cexp lcd;` + `lcd.begin(20,4);` |
| `D2` | `GPIO4` | `SDA` del LCD I2C | `Wire.begin();` + `hd44780_I2Cexp lcd;` + `lcd.begin(20,4);` |
| `D5` | `GPIO14` | `SCK` de tarjeta SD | `#define SD_SCK_PIN D5` |
| `D6` | `GPIO12` | `MISO` de tarjeta SD | `#define SD_MISO_PIN D6` |
| `D7` | `GPIO13` | `MOSI` de tarjeta SD y salida digital de estado | `#define SD_MOSI_PIN D7` + `pinMode(13, OUTPUT);` |
| `D8` | `GPIO15` | `CS` de tarjeta SD | `#define SD_CS_PIN D8` |
| `RX` | `GPIO3` | UART hardware del GPS | `#define GPS_RX0_PIN RX` + lectura por `Serial.read()` |
| `TX` | `GPIO1` | UART hardware del GPS | `#define GPS_TX0_PIN TX` + `Serial.begin(9600);` |

## Conexionado sugerido por dispositivo

### GPS

El GPS esta conectado a la UART hardware del ESP8266.

| Wemos D1 mini | GPIO | Pin del GPS |
| --- | --- | --- |
| `RX` | `GPIO3` | `TX` |
| `TX` | `GPIO1` | `RX` |
| `3V3` o `5V` | - | `VCC` |
| `GND` | - | `GND` |

Notas:

- El codigo no usa `SoftwareSerial`.
- Los datos GPS se leen con `while (Serial.available() > 0) { gps.encode(Serial.read()); }`.
- Eso implica que el GPS comparte la UART principal con la programacion y la consola serie por USB.

### LCD I2C

El codigo usa un display LCD por I2C con la libreria `hd44780_I2Cexp`.

| Wemos D1 mini | GPIO | Pin del LCD |
| --- | --- | --- |
| `D1` | `GPIO5` | `SCL` |
| `D2` | `GPIO4` | `SDA` |
| `3V3` o `5V` | - | `VCC` |
| `GND` | - | `GND` |

Notas:

- `Wire.begin()` no especifica pines.
- En ESP8266, la inferencia normal es `D2/GPIO4` como `SDA` y `D1/GPIO5` como `SCL`.
- El codigo inicializa un LCD de `20x4` con `lcd.begin(20,4);`.

### Tarjeta SD

El codigo define explicitamente los pines SPI para SD asi:

| Wemos D1 mini | GPIO | Senal SD |
| --- | --- | --- |
| `D5` | `GPIO14` | `SCK` |
| `D6` | `GPIO12` | `MISO` |
| `D7` | `GPIO13` | `MOSI` |
| `D8` | `GPIO15` | `CS` |
| `3V3` o `5V` | - | `VCC` |
| `GND` | - | `GND` |

Notas:

- El codigo hace `SPI.begin();` y luego `SD.begin(SD_CS_PIN)`.
- `SD_CS_PIN` esta definido como `D8`.

### Salida digital de estado

El codigo usa `GPIO13` como salida digital.

| Wemos D1 mini | GPIO | Uso |
| --- | --- | --- |
| `D7` | `GPIO13` | Salida digital de estado |

Notas:

- `pinMode(13, OUTPUT);`
- `digitalWrite(13, HIGH);` cuando hay suficientes satelites
- `digitalWrite(13, LOW);` cuando no hay suficientes satelites
- El codigo no identifica explicitamente que dispositivo hay conectado. Puede ser un LED, transistor, buzzer o similar.



## Riesgo al cargar programas

### UART principal ocupada por el GPS

El codigo usa:

- `RX / GPIO3`
- `TX / GPIO1`

para el GPS.

Eso puede dar problemas al cargar firmware porque esos mismos pines tambien se usan para:

- programacion por USB
- comunicacion con el bootloader
- monitor serie

Si el GPS esta conectado durante la grabacion, puede interferir con la carga del programa. Se recomienda usar un switch para desvincular RX antes de cargar un programa.

### Pin de arranque usado por la SD

El codigo usa:

- `D8 / GPIO15` como `CS` de la SD

`GPIO15` es un pin sensible durante el arranque del ESP8266. Si el hardware conectado a ese pin altera su estado durante el encendido o reset, puede impedir un arranque normal.

## Aclaracion sobre el modo de inicio

El pin que selecciona entre arranque normal y modo `flash` del ESP8266 es `D3 / GPIO0`.

Segun `MyGPS.ino`:

- `D3 / GPIO0` no esta asignado a ningun dispositivo

Sin embargo, los pines que si estan usados y pueden afectar la carga o el arranque son:

- `RX / GPIO3` y `TX / GPIO1` por estar compartidos con la programacion
- `D8 / GPIO15` por estar conectado a la tarjeta SD y ser un pin sensible de arranque

## Diagrama simple

```text
Wemos D1 mini / ESP8266

  D1  (GPIO5)  -----------------> SCL   LCD I2C
  D2  (GPIO4)  -----------------> SDA   LCD I2C

  RX  (GPIO3)  <---------------- TX    GPS
  TX  (GPIO1)  ----------------> RX    GPS

  D5  (GPIO14) ----------------> SCK   SD
  D6  (GPIO12) <---------------- MISO  SD
  D7  (GPIO13) ----------------> MOSI  SD
  D8  (GPIO15) ----------------> CS    SD

  3V3 o 5V     ----------------> VCC   GPS / LCD / SD
  GND          ----------------> GND   GPS / LCD / SD
```

## Resumen rapido

- GPS: `RX/GPIO3` y `TX/GPIO1`
- LCD I2C: `D1/GPIO5` y `D2/GPIO4`
- SD: `D5/GPIO14`, `D6/GPIO12`, `D7/GPIO13`, `D8/GPIO15`
- Salida digital adicional: `D7/GPIO13`
- Pin que selecciona arranque normal o `flash`: `D3/GPIO0`
- En este codigo, `D3/GPIO0` no tiene ningun dispositivo conectado
