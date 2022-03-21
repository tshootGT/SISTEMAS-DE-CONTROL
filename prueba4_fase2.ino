
// Pines utilizados
#define LEDVERDE 2
#define LEDAMARILLO 3
#define LEDROJO 4
#define TRIGGER 5
#define ECHO 6
#define ELECTRO 12


const int pulsador=10;      //señal del boton
const int pulsador1=11;      //push para electroiman
int derecha=8;             //salida al puente h para giro a la derecha (puedes usar cualquier otro pin)
int izquierda=9;          //giro izq
boolean estado_pul=true;   //para guardar el estado del  pulsador (lo inicializo en 1 porque lo tienes pull-up)
boolean estado_ant_pul=true;
int direccion=0;        //con esta variable vamos a controlar el motor     
int val;
int vol;


// Constantes
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 30.0;
const float umbral2 = 15.0;
const float umbral3 = 30.0;
 
void setup() {
  // Iniciamos el monitor serie
  Serial.begin(9600);
 
  // Modo entrada/salida de los pines
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARILLO, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ELECTRO, OUTPUT);

  pinMode(pulsador,INPUT);
  pinMode(pulsador1,INPUT);
  pinMode(derecha,OUTPUT);
  pinMode(izquierda,OUTPUT);
  digitalWrite(derecha,LOW);     //comienza con el motor apagado
  digitalWrite(izquierda,LOW);
  val=digitalRead(pulsador);
  vol=digitalRead(pulsador1);
 
  // Apagamos todos los LEDs
  apagarLEDs();
 
}
 
void loop() {
  // Preparamos el sensor de ultrasonidos
  iniciarTrigger();
 
  // Obtenemos la distancia
  float distancia = calcularDistancia();

  val=digitalRead(pulsador);
  vol=digitalRead(pulsador1);
 
  // Apagamos todos los LEDs
  apagarLEDs();
  motor();


  // Lanzamos alerta si estamos dentro del rango de peligro
  if (distancia < umbral1)
  {
    // Lanzamos alertas
    alertas(distancia);
  }


 
}
 
// Apaga todos los LEDs
void apagarLEDs()
{
  // Apagamos todos los LEDs
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARILLO, LOW);
  digitalWrite(LEDROJO, LOW);
  digitalWrite(ELECTRO, LOW);
}
 
// Función que comprueba si hay que lanzar alguna alerta visual o sonora

void alertas(float distancia)
{

val=digitalRead(pulsador);
estado_pul=digitalRead(pulsador);
  if (distancia < umbral1 && distancia >= umbral2)  
  {

    
    // Encendemos el LED verde y comienza a bajar la plataforma
    digitalWrite(LEDVERDE, HIGH);
    digitalWrite(derecha,HIGH);     
    digitalWrite(izquierda,LOW);
    Serial.println("baja la rampa");
    
    
    while(val ==0){
    digitalWrite(derecha,LOW);     
    digitalWrite(izquierda,LOW);
    Serial.println("se detiene la rampa");
    val=digitalRead(pulsador);      
    delay(100);  
    }
    
  }

  else if (distancia <= umbral2)
  {
    // Encendemos el LED rojo, y no baja la plataforma
    digitalWrite(LEDROJO, HIGH);
        digitalWrite(derecha,LOW);     
    digitalWrite(izquierda,LOW);
    Serial.println("se detiene la rampa");
    
    
  }

}

void motor ()
{
vol=digitalRead(pulsador1);

  if (vol == LOW){

    digitalWrite(ELECTRO, HIGH);
    Serial.println("Electroiman activo, silla de rudas asegurada");
    
    
    }

  else { digitalWrite(ELECTRO,LOW);
}
  
  }
 
// Método que calcula la distancia a la que se encuentra un objeto.
// Devuelve una variable tipo float que contiene la distancia
float calcularDistancia()
{
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH);
 
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);
 
  return distancia;
}



// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2); 
 
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
 
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(TRIGGER, LOW);
}
