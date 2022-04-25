//INTEGRANTES
//MARIO RENE TEYUL COC 201503740
//RICARDO CARDONA MINERA 201504084
//CLASE SISTEMAS DE CONTROL
//ING. INGRID LOUKOTA

//banderas
int estado;
int estado1;
bool statusgiro = 0;
bool statusrampa = 0;
bool statusrampa1 = 0;
bool statusButton = 0;

// Pines utilizados
#define LEDVERDE 2
#define LEDAMARILLO 3
#define LEDROJO 4
//TIERRA AMARILLO
#define TRIGGER 5 //AZUL
#define ECHO 6    //VERDE
//VCC MORADO
#define ELECTRO 12
const int pulsador1 = 8;
const int pulsador2 = 11;
const int giroA = 9;
const int giroH = 10;


// Constantes para calcular la distancia
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 24.0;
const float umbral2 = 18;
const float umbral3 = 12.0;
const float umbral4 = 3.20;
const float umbral5 = 30.0;
const float umbral6 = 31.0;
const float umbral7 = 22.0;

void setup()
{
   // Iniciamos el monitor serie
  Serial.begin(9600);

  // Modo entrada/salida de los pines
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARILLO, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ELECTRO, OUTPUT);
  pinMode(giroA, OUTPUT);
  pinMode(giroH, OUTPUT);
  pinMode(pulsador1, INPUT);
  pinMode(pulsador2, INPUT);
  digitalWrite(giroA, LOW);
  digitalWrite(giroH, LOW);

// Apagamos todos los LEDs
  apagarLEDs();
  apagarMOTOR();
}

void loop()
{
// Preparamos el sensor de ultrasonidos
iniciarTrigger();
  
// Obtenemos la distancia
float distancia = calcularDistancia();

//apagamos los led y motor
  apagarLEDs();
  apagarMOTOR();



// Lanzamos alerta si estamos dentro del rango 
estado = digitalRead(pulsador1);
if(estado == LOW)
  {
   statusrampa = !statusrampa;
   statusrampa1 = 0;
  }

if (statusrampa ==1)
{
  alertas(distancia);
  analogWrite(giroH,0); 
}

estado1 = digitalRead(pulsador2);

if(estado1 == LOW)
  {
  statusrampa1 = !statusrampa1;
  statusrampa = 0;
  }
if (statusrampa1 ==1)
  {
   alertas1(distancia);
   analogWrite(giroA,0); 
  }
  
}

void apagarLEDs()
{
  // Apagamos todos los LEDs
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARILLO, LOW);
  digitalWrite(LEDROJO, LOW);
  digitalWrite(ELECTRO, HIGH);

}

void apagarMOTOR()
{
    analogWrite(giroA,0);     
    analogWrite(giroH,0); 
}

void alertas(float distancia)
{

//statusButton = digitalRead(onoff);

  if (distancia >= umbral1)
  {
    analogWrite(giroA,0);     
    analogWrite(giroH,0); 
    digitalWrite(ELECTRO, HIGH);
    //digitalWrite(LEDROJO, HIGH); 
    statusrampa1 = 0; 
    }
    
  else if (distancia < umbral1 && distancia >= umbral2)  
  { 
    // Encendemos el LED ROJO  y comienza a bajar la plataforma
    digitalWrite(LEDROJO, HIGH);
    analogWrite(giroA,121);     
    digitalWrite(ELECTRO, LOW);
    Serial.println("BAJA LA RAMPA CON UN CLICLO DE TRABAJO AL 100% Y ENCLAVA EL ELECTROIMAN");
    statusrampa1 = 0;
  }

  else if (distancia < umbral2 && distancia >= umbral3)  
  {
    // Encendemos el LED AZUL  y sigue bajando la plataforma
    digitalWrite(LEDAMARILLO, HIGH);
    analogWrite(giroA,50);  
    digitalWrite(ELECTRO, LOW); 
    Serial.println("BAJA LA RAMPA CON UN CLICLO DE TRABAJO AL 50% Y ENCLAVA EL ELECTROIMAN");
    statusrampa1 = 0;
  }

   else if (distancia < umbral3 && distancia >= umbral4)  
  {
    // Encendemos el LED AZUL  y sigue bajando la plataforma
    digitalWrite(LEDAMARILLO, HIGH);
    analogWrite(giroA,50);   
    digitalWrite(ELECTRO, LOW);
    Serial.println("BAJA LA RAMPA CON UN CLICLO DE TRABAJO AL 25& Y ENCLAVA EL ELECTROIMAN%");
    statusrampa1 = 0;
  }

   if (distancia <= umbral4)
  {
    // Encendemos el verde , y la plataforma eta lista para subir al individuo
    digitalWrite(LEDVERDE, HIGH);
    analogWrite(giroA,0);   
    digitalWrite(ELECTRO, HIGH);   
    Serial.println("SE DETIENE LA RAMPA CON UN CLICLO DE TRABAJO AL 0 Y DESENCLAVA EL ELECTROIMAN%");
    apagarMOTOR();
    apagarLEDs();
    statusrampa =0;
  }



}

void alertas1(float distancia)
{

//statusButton = digitalRead(onoff);

  if (distancia > umbral6)
  {
    analogWrite(giroA,0);     
    analogWrite(giroH,255); 
    statusrampa = 0;

  }
    else if (distancia > umbral6 )
  {
    // Encendemos el verde , y la plataforma eta lista para subir al individuo
    digitalWrite(LEDROJO, HIGH);  
    analogWrite(giroH,255);
    digitalWrite(ELECTRO, LOW);
    Serial.println("SUBE LA RAMPA CON UN CLICLO DE TRABAJO AL 100% Y ENCLAVA EL ELECTROIMAN");
    statusrampa = 0;
  }
    else if (distancia < umbral4 )
  {
    // Encendemos el verde , y la plataforma eta lista para subir al individuo
    digitalWrite(LEDROJO, HIGH);  
    analogWrite(giroH,255);
    digitalWrite(ELECTRO, LOW);
    Serial.println("SUBE LA RAMPA CON UN CLICLO DE TRABAJO AL 100% Y ENCLAVA EL ELECTROIMAN");
    statusrampa = 0;
  }
   else if (distancia < umbral3 && distancia >= umbral4)  
  {
    // Encendemos el LED AZUL  y sigue bajando la plataforma
    digitalWrite(LEDAMARILLO, HIGH);  
    analogWrite(giroH,191);
    digitalWrite(ELECTRO, LOW);
    Serial.println("SUBE LA RAMPA CON UN CLICLO DE TRABAJO AL 50% Y ENCLAVA EL ELECTROIMAN");
    statusrampa = 0;
  }
  else if (distancia < umbral2 && distancia >= umbral3)  
  {
    // Encendemos el LED AZUL  y sigue bajando la plataforma
    digitalWrite(LEDAMARILLO, HIGH);    
    analogWrite(giroH,191);
    digitalWrite(ELECTRO, LOW);
    Serial.println("SUBE LA RAMPA CON UN CLICLO DE TRABAJO AL 25% Y ENCLAVA EL ELECTROIMAN");
    statusrampa = 0;
  }
  else if (distancia < umbral7 && distancia >= umbral2)  
  {
    // Encendemos el LED AZUL  y sigue bajando la plataforma
    digitalWrite(LEDAMARILLO, HIGH);    
    analogWrite(giroH,191);
    digitalWrite(ELECTRO, LOW);
    Serial.println("SUBE LA RAMPA CON UN CLICLO DE TRABAJO AL 5% Y ENCLAVA EL ELECTROIMAN");
    statusrampa = 0;
    
  }
   else if (distancia >umbral7 && distancia < umbral6)  
  {
    // Encendemos el LED VERDE  y SE PUEDE bajar la PERSONA
    digitalWrite(LEDVERDE, HIGH); 
    analogWrite(giroH,0);
    digitalWrite(ELECTRO, HIGH);   
    Serial.println("SE DETIENE LA RAMPA CON UN CLICLO DE TRABAJO AL 0 Y DESENCLAVA EL ELECTROIMAN%");
    apagarMOTOR();
    apagarLEDs();
    statusrampa1 = 0;
    
  }




}

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
