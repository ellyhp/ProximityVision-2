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

  // Vibra si está a MENOS de 30 cm
  if (distancia <= 30) {

    digitalWrite(MOTOR, HIGH);

    Serial.println("VIBRANDO");

  } else {

    digitalWrite(MOTOR, LOW);

  }

  delay(100);
}
```
