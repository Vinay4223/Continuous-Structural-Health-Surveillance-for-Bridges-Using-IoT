#include <Wire.h>
#include <MPU6050.h>

#define VIB_PIN 2
#define MQ2_PIN A0
#define BUZZER 3

MPU6050 mpu;

void setup() {
  Serial.begin(9600);

  pinMode(VIB_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  Wire.begin();
  mpu.initialize();
}

void loop() {

  int vibration = digitalRead(VIB_PIN);
  int gasValue = analogRead(MQ2_PIN);

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // 🚨 ALERT LOGIC
  if (gasValue > 300 || vibration == 1 || abs(ax) > 8000) {
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  // 📊 SERIAL PLOTTER FORMAT
  Serial.print(gasValue);
  Serial.print(" ");
  Serial.print(vibration * 500);   // scale for visibility
  Serial.print(" ");
  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.println(az);

  delay(100);
}