#define pinSensorD 11
#define pinSensorE 12
#define pinSensorM 10

#define pinMotorE1 3 
#define pinMotorE2 5 
#define pinMotorD1 6
#define pinMotorD2 9

#define velocidade 220
#define velocidade_curva 200

void setup() {
  
  Serial.begin(9600);
  pinMode(pinSensorD, INPUT);
  pinMode(pinSensorE, INPUT);
  pinMode(pinSensorM, INPUT);

  pinMode(pinMotorD1, OUTPUT);
  pinMode(pinMotorD2, OUTPUT);
  pinMode(pinMotorE1, OUTPUT);
  pinMode(pinMotorE2, OUTPUT);
}

void loop() {
  bool estadoM = !digitalRead(pinSensorM);
  bool estadoD = !digitalRead(pinSensorD);
  bool estadoE = !digitalRead(pinSensorE);
  Serial.print("d ");
  Serial.print(estadoD);
  Serial.print(" m ");
  Serial.print(estadoM);
  Serial.print(" e ");
  Serial.println(estadoE);

  
  if (estadoD && estadoE && !estadoM) {
     digitalWrite(pinMotorD2, LOW); 
     analogWrite(pinMotorD1, velocidade);
     digitalWrite(pinMotorE1, LOW);
     analogWrite(pinMotorE2, velocidade);
  }

  if (!estadoD && !estadoE && !estadoM) {
     delay(1000);
     if(estadoD && estadoE && estadoM){
      digitalWrite(pinMotorD1, LOW);
      digitalWrite(pinMotorD2, LOW);
      digitalWrite(pinMotorE1, LOW);
      digitalWrite(pinMotorE2, LOW);
     }
  }

  if (!estadoD && estadoE && !estadoM) {
     digitalWrite(pinMotorE1, LOW);
     analogWrite(pinMotorE2, velocidade_curva);
     digitalWrite(pinMotorD1, LOW);
     analogWrite(pinMotorD2, velocidade_curva);
  }

  if (estadoD && !estadoE && !estadoM) {
     digitalWrite(pinMotorD2, LOW);
     analogWrite(pinMotorD1, velocidade_curva);
     digitalWrite(pinMotorE2, LOW);
     analogWrite(pinMotorE1, velocidade_curva);
  }
  
}