int ledpin = 13;
int sigpin = 11;
int value = 0;

void setup(){
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);

}

void loop(){
  value = digitalRead(sigpin);

  if(value == HIGH){
    digitalWrite(ledpin, HIGH);
    Serial.write("preto");
    printf("preto");
  }
  else{
    digitalWrite(ledpin, LOW);
    Serial.write("branco");
    printf("branco");
  }
}
