#include<Servo.h>

Servo motor;
double background, LDR, diferencia, ini=30, fin=60;

void get_background(){
  background = 0;
  for(int i=0; i<40; i++){
    background += analogRead(A0);
    delay(100);
  }
  background /= 30;
  Serial.println(background);
}

void presiona_boton(){
  delay(40);
  motor.write(fin);
  delay(200);
  motor.write(ini);
  delay(100); 
}

void setup() {
  Serial.begin(9600);
  
  pinMode(A0, INPUT);
  motor.attach(6);
  motor.write(ini);
  
  get_background();
  delay(3000);
  presiona_boton();
}

void loop() {
  // put your main code here, to run repeatedly:
  LDR = analogRead(A0);
  Serial.println(LDR);
  diferencia = background-LDR;
  if(diferencia<-32){
    presiona_boton();
  }
}
