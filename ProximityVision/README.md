# 👓 ObjectVision Pro

> Sistema de detección de proximidad por vibración integrado en lentes — Arduino Nano + HC-SR04

---

## 🌱 Origen del proyecto — Versión 2

Este proyecto es la **segunda versión** de una idea propia. En la **v1** tomé unos lentes normales y pegué los componentes directamente con silicón — funcionaba, pero el resultado era voluminoso, poco estético y difícil de replicar.

Así que decidí rediseñarlo desde cero: **modelar el armazón en 3D** pensado específicamente para alojar la electrónica de forma limpia y compacta. Sin silicón, sin cables sueltos — ensamble limpio por presión.

🎬 **Video del proceso completo:** [@ellygmr en TikTok](https://www.tiktok.com/@ellygmr/video/7645145178122177812)
🖨️ **Modelo STL en MakerWorld:** [ProximityVision en MakerWorld](https://makerworld.com/es/models/2861372-proximityvision)

---

## ¿Qué hace ObjectVision Pro?

**ObjectVision Pro** es un sistema de detección de objetos basado en **Arduino Nano** y el sensor ultrasónico **HC-SR04**. Utiliza **vibración** como método de alerta para indicar la proximidad de obstáculos en tiempo real.

Cuando un objeto se encuentra a **menos de 1 metro** (ajustable), el sistema activa un **motor vibrador** para advertir al usuario de forma discreta y sin necesidad de audio ni pantalla.

**Propósito principal:** funcionar como asistencia de detección de proximidad integrada en lentes inteligentes o dispositivos portátiles wearable.

---

## 🗂️ Estructura del repositorio

```
objectvision-pro/
├── README.md
├── diagrama.png                 ← Esquema visual de conexiones
├── diagrama.txt                 ← Componentes utilizados y función de cada uno
├── imagenes/
│   ├── v1_silicone.jpg          ← Primera versión con silicón
│   └── v2_modelo3d.jpg          ← Armazón impreso
└── codigo/
    └── objectvision_pro.ino     ← Código principal para Arduino IDE
```

---

## 🔧 Hardware

| Componente | Descripción |
|---|---|
| Arduino Nano | Microcontrolador principal |
| HC-SR04 | Sensor ultrasónico de distancia |
| Motor vibrador | Alerta háptica (3V, estilo celular) |
| Batería LiPo 3.7V | Alimentación portátil |
| MT3608 (Step-up boost) | Elevador de voltaje 3.7V → 5V |

### ¿Por qué el elevador de voltaje?

La batería LiPo entrega **3.7V**, pero el Arduino Nano y el sensor HC-SR04 requieren **5V** para operar correctamente. El módulo MT3608 regula y eleva el voltaje de forma eficiente, permitiendo alimentar todo el sistema desde una sola celda de litio.

---

## 📐 Diagrama de circuito

```
LiPo 3.7V
    │
    ▼
MT3608 (3.7V → 5V)
    │
    ├──── VIN ──→ Arduino Nano
    │
    │     D9  ──→ TRIG  (HC-SR04)
    │     D10 ──→ ECHO  (HC-SR04)
    │     D3  ──→ Motor vibrador (+)
    │
    └──── GND común (Arduino + sensor + motor + boost)
```

> El diagrama visual está en `diagrama.png` y la descripción de cada componente en `diagrama.txt`

---

## 💻 Código

El archivo `.ino` está en la carpeta `codigo/`. Ábrelo directamente con el **Arduino IDE**.

```cpp
#define TRIG 9
#define ECHO 10
#define MOTOR 3

long duracion;
int distancia;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(MOTOR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Pulso ultrasónico
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Leer eco
  duracion = pulseIn(ECHO, HIGH);

  // Calcular distancia
  distancia = duracion * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Vibra si está a MENOS de 1 metro
  if (distancia <= 100) {
    digitalWrite(MOTOR, HIGH);
    Serial.println("VIBRANDO");
  } else {
    digitalWrite(MOTOR, LOW);
  }

  delay(100);
}
```

### ⚙️ Ajuste de distancia de alerta

Cambia el umbral en la línea `if (distancia <= 100)` según tu necesidad:

| Umbral | Uso recomendado |
|---|---|
| `100` cm (default) | Detección general de obstáculos |
| `30` cm | Espacios reducidos, navegación cercana |
| `10` cm | Máxima precisión — objetos muy próximos |

---

## 🚀 Cómo armarlo

1. Imprime el armazón desde [MakerWorld](https://makerworld.com/es/models/2861372-proximityvision)
2. Conecta los componentes según el diagrama en `imagenes/circuito.jpg`
3. Abre `codigo/objectvision_pro.ino` en el **Arduino IDE**
4. Selecciona la placa **Arduino Nano** y el puerto correcto
5. Sube el código
6. Abre el **Monitor Serial** a 9600 baudios para verificar lecturas
7. Ensambla todo en el armazón por presión

---

## 🧩 Próximos pasos

- [ ] Vibración proporcional a la distancia con PWM
- [ ] Optimizar consumo para mayor duración de batería
- [ ] Versión con Bluetooth para configurar el umbral desde el celular

---

## 📄 Licencia

MIT — libre de usar, modificar y compartir.

---

Sígueme en redes **@ellygmr** para ver el proceso completo y más proyectos.

_v2 — de silicón y cables sueltos a modelo 3D propio_ ✌️
