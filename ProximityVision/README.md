# 👓 ObjectVision Pro

> Sistema de detección de proximidad por vibración para lentes inteligentes — Arduino Nano + HC-SR04

---

## 🌱 Origen del proyecto — Versión 2

Este proyecto es la **segunda versión** de una idea que nació de mi propio reel. En la **v1** tomé unos lentes normales y pegué los componentes directamente con silicón — funcionaba, pero el resultado era voluminoso, poco estético y difícil de replicar.

Así que decidí rediseñarlo desde cero: **modelar el armazón en 3D** pensado específicamente para alojar la electrónica de forma limpia y compacta. Esta es esa versión.

🎬 **Reel original (v1):** _[tu enlace aquí]_
🔗 **Modelo 3D en Tinkercad:** _[enlace próximamente]_

---

## ¿Qué hace ObjectVision Pro?

**ObjectVision Pro** es un sistema de detección de objetos basado en **Arduino Nano** y el sensor ultrasónico **HC-SR04**. Utiliza **vibración** como método de alerta para indicar la proximidad de obstáculos en tiempo real.

Cuando un objeto se encuentra a **menos de 1 metro** (ajustable), el sistema activa un **motor vibrador** para advertir al usuario de forma discreta y sin necesidad de audio ni pantalla.

**Propósito principal:** funcionar como asistencia de detección de proximidad integrada en lentes inteligentes o dispositivos portátiles wearable.

---

## 🔧 Hardware

| Componente | Descripción |
|---|---|
| Arduino Nano | Microcontrolador principal |
| HC-SR04 | Sensor ultrasónico de distancia |
| Motor vibrador | Alerta háptica (3V, estilo celular) |
| Batería LiPo 3.7V | Alimentación portátil |
| MT3608 (Step-up boost) | Elevador de voltaje 3.7V → 5V |
| Transistor NPN 2N2222 | Control del motor desde pin digital |
| Resistencia 1kΩ | Limitadora de corriente en base del transistor |
| Diodo 1N4007 | Flyback para proteger el Arduino del motor |

### ¿Por qué el elevador de voltaje?

La batería LiPo entrega **3.7V**, pero el Arduino Nano y el sensor HC-SR04 requieren **5V** para operar correctamente. El módulo MT3608 regula y eleva el voltaje de forma eficiente, permitiendo que todo el sistema sea alimentado desde una sola celda de litio.

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
    │     D3  ──→ 1kΩ → Base NPN → Motor vibrador
    │
    └──── GND común (Arduino + sensor + motor + boost)
```

Diodo 1N4007 en paralelo al motor (cátodo al positivo) para protección flyback.

---

## 💻 Código

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

Puedes cambiar el umbral en la línea `if (distancia <= 100)` según tu necesidad:

| Umbral | Uso recomendado |
|---|---|
| `100` cm (default) | Detección general de obstáculos |
| `30` cm | Espacios reducidos, navegación cercana |
| `10` cm | Máxima precisión — objetos muy próximos |

Los valores de **30 cm y 10 cm** son especialmente útiles para tareas de precisión o entornos con muchos objetos alrededor, ya que reducen las alertas falsas por el ambiente.

---

## 🗂️ Estructura del repositorio

```
objectvision-pro/
├── README.md
├── objectvision_pro.ino      ← Código principal
├── circuit/
│   └── diagram.png           ← Esquema de conexiones
└── model_3d/
    └── tinkercad_link.txt    ← Enlace al modelo en Tinkercad
```

---

## 🚀 Cómo usarlo

1. Clona este repositorio
2. Abre `objectvision_pro.ino` en el **Arduino IDE**
3. Conecta el Arduino Nano por USB
4. Selecciona la placa **Arduino Nano** y el puerto correcto
5. Sube el código
6. Abre el **Monitor Serial** a 9600 baudios para ver lecturas en tiempo real
7. Ajusta el umbral de distancia según tu caso de uso

---

## 🧩 Próximos pasos

- [ ] Publicar modelo 3D en Tinkercad
- [ ] Agregar modo de vibración por pulsos (intensidad variable según distancia)
- [ ] Explorar integración con PWM para vibración proporcional
- [ ] Optimizar consumo de energía para mayor duración de batería
- [ ] Versión con Bluetooth para configuración desde el celular

---

## 📄 Licencia

MIT — libre de usar, modificar y compartir.

---

_v2 — de silicón y cables sueltos a modelo 3D propio_ ✌️
