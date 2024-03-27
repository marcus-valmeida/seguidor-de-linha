int sensorD = 11;
int sensorM = 12;
int sensorE = 13;


int PWM_B = 3;
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int PWM_A = 8;

int sensor[3] = {0,0,0};
int velocidade = 255;

int Ki = 0;
int Kp = 35;
int Kd = 35;
int I = 0, P = 0, D = 0, PID = 0;
int veloeq = 0, velodir = 0;
int erro = 0, erro_anterior = 0;



void setup() {

  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  pinMode(sensorD, INPUT);
  pinMode(sensorM, INPUT);
  pinMode(sensorE, INPUT);

}
/*void curva_90_direita(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(PWM_A, 0.8*velocidade);
  analogWrite(PWM_B, 0.1*velocidade);

}

void curva_90_esquerda(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(PWM_A, 0.1*velocidade);
  analogWrite(PWM_B, 0.8*velocidade);
}*/
/*
void parada(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
*/
void calculo_erro(){
  if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0)){// linha reta , erro = 0
    (erro = 0);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] ==1)){// leve curva para direita , erro = 2
    (erro = 2);
  }
  else if((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0)){ // leve curva para esquerda , erro = -2
    (erro = -2);
  }
  else if((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] ==1)){ //  erro = 1
    (erro = 1);
  }
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0)){ // erro = -1
    (erro = -1);
  }
}

void calculo_do_PID(){
  if (erro == 0){
    //caso esteja no caso ideal.
    I = 0;
  }
  P = erro;
  I = I + erro;

  if(I > 255){
    // caso o erro esteja acima da velocidade maxima.
    I = 255;
  }

  else if (I < -255){
    // caso para o erro não ultrapassar o minimo possivel.
    I = -255;
  }
  // Realizando o calculo.
  D = erro - erro_anterior;
  PID = (Kp*P) + (Ki*I) + (Kd*D);
  erro_anterior = erro;
}

void controle_motores(){
  if (PID >= 0){
    veloeq = velocidade;
    velodir = velocidade - PID;
  }
  else{
    veloeq = velocidade + PID;
    velodir = velocidade;
  }

  digitalWrite (IN1, HIGH);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN1, HIGH);
  analogWrite (PWM_A, velocidade);
  analogWrite (PWM_B, HIGH);
}

void loop() {

  sensor[0] = digitalRead(sensorE);
  sensor[1] = digitalRead(sensorM);
  sensor[2] = digitalRead(sensorD);

  Serial.print(" e ");
  Serial.print(sensor[0]);
  Serial.print(" m ");
  Serial.print(sensor[1]);
  Serial.print(" d ");
  Serial.println(sensor[2]);

  calculo_erro();
  calculo_do_PID();
  controle_motores();
  

}
