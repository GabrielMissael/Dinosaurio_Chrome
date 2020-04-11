//Incluimos esta librería para poder manejar el servomotor
#include<Servo.h>

//Declaramos una variable tipo Servo
Servo motor;

/*
 * LDR --> para guardar el valor leído de la fotorresistencia en cada loop
 * background --> se guarda el valor del fondo del juego (no los obstáculos)
 * Ini, fin --> Angulo inicial y final del servo para hacer click (depende de cómo lo coloques)
 * tiempo_obstaculo --> Delay entre lectura de obstáculo y presionar el botón
 * umbral --> sensibilidad del circuito para presionar botón
*/

double background, LDR, diferencia, ini=30, fin=60, tiempo_obstaculo, umbral = 60;


void get_background(){
  // DESCRIPCION: Esta función obtiene el valor leído de la LDR para el fono del juego
  
  background = 0;

  //Se hace un promedio de 40 lecturas separadas por 0.1 segundos (4 segundos en total)
  for(int i=0; i<40; i++){
    background += analogRead(A0);
    delay(100);
  }
  background /= 40;
  Serial.println(background);
}

void presiona_boton(){
  //DESCRIPCION: Esta función hace presionar el servo
  
  // OJO: El valor de tiempo_obstaculo depende de que tan alejado esta tu LDR del T-rex en la pantalla
  tiempo_obstaculo = 40;
  delay(tiempo_obstaculo);

  //Escribimos las posiciones en el servo
  motor.write(fin);
  // Delay para dejar que el servo termine el movimiento
  delay(200);
  motor.write(ini);

  // Delay para estabilidad
  delay(100); 
}

// Configuración inicial
void setup() {
  // Ponemos la comunicación serial a 9600 baudios
  Serial.begin(9600);

  // El pin A0 (analógico) es de lectura de la LDR
  pinMode(A0, INPUT);

  // La comunicación con el servo es en el puerto 6 (digital)
  motor.attach(6);

  //Colocamos al servo en la posición inicial
  motor.write(ini);

  //Obtenemos valor del background
  get_background();
  delay(3000);

  // Iniciamos el juego
  presiona_boton();
}

void loop() {
  // Leemos valor de la fotorresistencia
  LDR = analogRead(A0);
  Serial.println(LDR);

  // La diferencia entre el background original y el valor leído
  diferencia = background-LDR;

  // Si la diferencia es mayor al umbral de sensibilidad, el T-rex salta :)
  if(abs(diferencia)> umbral){
    presiona_boton();
  }
  
}

