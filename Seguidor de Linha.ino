// Identificando os Sensores.
int sensor0 = 12;
int sensor1 = 11;
int sensor2 = 10;
int sensor3 = 9;
int sensor4 = 8;


// Identificando os motores.
int IN1 = 3;
int IN2 = 4;
int IN3 = 5;
int IN4 = 6;

// Identificação da Matriz que receberá os sensores.
int sensor[5] = {0,0,0,0,0};
//compensacao de peso
int velocidade_esquerda = 120;
int velocidade_direita = velocidade_esquerda*0.78;

// Declaração das variaveis e fator de proporcionalidade do PID.
int Ki = 0;
int Kp = 20;
int Kd = 20;
int I = 0, P = 0, D = 0, PID = 0;
int veloeq = 0, velodir = 0;
int erro = 0, erro_anterior = 0;



void setup() {

 // Serial.begin(9600); --> Usado para impririr resultados, quando tiver fazendo testes, porém isso atrapalha a comunicação causando delay.

  // Declaração dos motores, que possuem caracteristicas de saída de informações.
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // As duas linhas abaixo seria considerada para uso de PWM para controlar melhor a tensão em cada motor.
  // pinMode(PWM_A, OUTPUT);
  // pinMode(PWM_B, OUTPUT);

  // Declaração dos sensores, que possuem caracteristicas de entrada de informações.
  pinMode(sensor0, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  
}
/*
void curva_90_direita(){
  //digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(IN3, velocidade_esquerda);
  analogWrite(IN1, 0*velocidade_direita);
}

void curva_90_esquerda(){
  //digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(IN1, 1*velocidade_direita);
  analogWrite(IN3, 0);
}*/

void calculo_erro(){
  // Aplicando valores para cada erro que supostamente o carro irá entrar, a idéia é que o carro permaneça no erro 0.
  if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0)){// linha reta , erro = 0
    (erro = 0);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 0)){// leve curva para direita
    (erro = 2);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0)){// leve curva para esquerda
    (erro = -2);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0)){// curva media para direita
    (erro = 2);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0)){// curva media para esquerda
    (erro = -2);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1)){// curva media alta para direita
    (erro = 3);
  }
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0)){// curva media alta para esquerda
    (erro = -3);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1)){// curva alta para direita
    (erro = 4);
  }
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0)){// curva alta para esquerda
    (erro = -4);
  }
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0)){// curva muito alta para esquerda
    (erro = -4);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1)){// curva muito alta para direita
    (erro = 4);
  }
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1)){// curva altissima para direita
    (erro = 5);
  }
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0)){// curva altissima para esquerda
   (erro = -5);
  }
  else{
    delay(0);
    
  }
}

void calculo_do_PID(){
     //caso esteja no caso ideal.
  if (erro == 0){
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
  // Aplicando a velocidade(tensão que irão receber) nos motores devido o controle PID.
  if (PID == 0){
    // Caso o PID seja igual a zero o carrinho terá velocidade máxima.
    veloeq = velocidade_esquerda*1.2;
    velodir = velocidade_direita*1.2;
  }
  else if (PID >){
    veloeq = velocidade_esquerda;
    velodir = velocidade_direita - PID;
  }
  else{
    veloeq = velocidade_esquerda + PID;
    velodir = velocidade_direita;
  }
  // Inserindo as informações nos motores.
  //digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  //digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (IN3, veloeq);
  analogWrite (IN1, velodir);
}

void loop() {
  // Realizando as leituras dos sensores no loop.
  sensor[0] = digitalRead(sensor0);
  sensor[1] = digitalRead(sensor1);
  sensor[2] = digitalRead(sensor2);
  sensor[3] = digitalRead(sensor3);
  sensor[4] = digitalRead(sensor4);
  /*
  Print para ser usado nos testes de velocidade.
  Serial.print("E1: ");
  Serial.print(sensor[0]);
  Serial.print("E2: ");
  Serial.print(sensor[1]);
  Serial.print("M: ");
  Serial.print(sensor[2]);
  Serial.print("D2: ");
  Serial.print(sensor[3]);
  Serial.print("D1: ");
  Serial.print(sensor[4]);
  */
 
    // Chamando as funções para controlar o carrinho.
    calculo_erro();
    calculo_do_PID();
    controle_motores();
}
