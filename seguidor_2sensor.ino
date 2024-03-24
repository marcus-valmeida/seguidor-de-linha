#define pinSensorD 11
#define pinSensorE 12

#define pinMotorE1 3 
#define pinMotorE2 5 
#define pinMotorD1 6
#define pinMotorD2 9

#define velocidade 220
#define velocidade_curva 190

void setup() {
  
  Serial.begin(9600);
  pinMode(pinSensorD, INPUT);
  pinMode(pinSensorE, INPUT);

  pinMode(pinMotorD1, OUTPUT);
  pinMode(pinMotorD2, OUTPUT);
  pinMode(pinMotorE1, OUTPUT);
  pinMode(pinMotorE2, OUTPUT);
}

void loop() {
  
  bool estadoD = !digitalRead(pinSensorD);
  bool estadoE = !digitalRead(pinSensorE);
  Serial.print("d ");
  Serial.print(estadoD);
  Serial.print(" e ");
  Serial.println(estadoE);
  if (estadoD && estadoE) {
     digitalWrite(pinMotorD2, LOW); 
     analogWrite(pinMotorD1, velocidade);
     digitalWrite(pinMotorE1, LOW);
     analogWrite(pinMotorE2, velocidade);
  }

  if (!estadoD && !estadoE) {
     digitalWrite(pinMotorD1, LOW);
     digitalWrite(pinMotorD2, LOW);
     digitalWrite(pinMotorE1, LOW);
     digitalWrite(pinMotorE2, LOW);
  }

  if (!estadoD && estadoE) {
     digitalWrite(pinMotorE1, LOW);
     analogWrite(pinMotorE2, velocidade_curva);
     digitalWrite(pinMotorD1, LOW);
     analogWrite(pinMotorD2, velocidade_curva);
  }

  if (estadoD && !estadoE) {
     digitalWrite(pinMotorD2, LOW);
     analogWrite(pinMotorD1, velocidade_curva);
     digitalWrite(pinMotorE2, LOW);
     analogWrite(pinMotorE1, velocidade_curva);
  }
  
}
