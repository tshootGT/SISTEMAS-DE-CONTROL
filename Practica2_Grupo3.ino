//201503740 - MARIO  TEYUL
//201504084 - RICARDO CARDONA

// DECLARACION DE VARIABLES PARA LOS LEDS 

int LED=13;
int SW_SENAL_ANALOGICA=12;
int funcion1;

int LED2=11;
int SW_SENAL_DIGITAL=10;
int funcion2;


// DECLARACION DE VARIABLES PARA EL MOTOR 

int MOTOR= 3 ;     


//DECLARACION DE VARIABLES  LA PRIMERA FUNCION 

  const int potenciometro=A0;                     


//DECLARACION DE VARIABLES PARA LA FUNCION 2


int contador = 0;  //Variable asociada al contador
int push1; //Variable para el antirrebote del pulsador aumentar
int push2; //Variable para el antirrebote del pulsador disminuir

int push_down = 8; //Pulsador conectado al pin 9
int push_up = 9; //Pulsador conectado a pin 10



void setup(){

  
  //LED Y DIP SWITCH
  
  pinMode(LED, OUTPUT);
  pinMode(SW_SENAL_ANALOGICA,INPUT);
  pinMode(LED2, OUTPUT);
  pinMode(SW_SENAL_DIGITAL,INPUT);


 // MOTOR

 pinMode(3,OUTPUT);


 //PUSH BOTTN PARA LA SEGUNDA FUNCION

  pinMode(9, INPUT);  //Pulsador aumentar como entrada digital
  pinMode(10, INPUT); 

 //SERIALPRIN

  Serial.begin(9600);

  }


void loop()
{

//PRIMERA FUNCION 

  funcion1=digitalRead(SW_SENAL_ANALOGICA);
                 //ALMACENAMOS LA LECTURA DEL potenciometroENCIOMETRO
  
  
  if(funcion1==HIGH){
    digitalWrite(LED,HIGH);
    analogWrite(MOTOR,analogRead(potenciometro)/4);
    Serial.println("SEÑAL ANALOGICA");
  }

  else{
    digitalWrite(LED,LOW);
  }
   //SEGUNDA FUNCION
  
  
    funcion2=digitalRead(SW_SENAL_DIGITAL); 
                 
  
  if(funcion2==HIGH){
    digitalWrite(LED2,HIGH); //ENCENDEMOS LED

if (digitalRead(push_up) == LOW)
  {
    push1 = 1;   //Variable del antirrebote que cambia cuando se presiona el pulsador
  }
  if (digitalRead(push_up) == HIGH && push1 == 1)
  {
    push1 = 0;  //Se reinicia la variable antirrebote
    contador++;       //Aumenta el contador
    if (contador > 2)
    {
      contador = 2; //Si el contador esta en 2 y se aumenta, sigue mostrando el 2
    }
  }

  //Condicionales para antirrebote y uso del pulsador disminuir

  if (digitalRead(push_down) == LOW)
  {
    push2 = 1;    //Variable del antirrebote que cambia cuando se presiona el pulsador
  }
  if (digitalRead(push_down) == HIGH && push2 == 1)
  {
    push2 = 0;   //Se reinicia la variable antirrebote
    contador--;        //Disminuye el contador

    if (contador < 0) //Si el contador esta en 0 y se disminuye, sigue mostrando el 0
    {
      contador = 0;
    }
  }

  switch (contador)
  {
    //Dependiendo del contador, se muestra el numero indicado
    //Envia estados (1 y 0) al display dependiendo del numero a mostrar

    case 0:
      analogWrite(MOTOR, 64); //Muestra el numero 0
      Serial.println("SEÑAL DIGITAL A 25%");
      break;

    case 1:
      analogWrite(MOTOR, 128); //Muestra el numero 1
      Serial.println("SEÑAL DIGITAL A 50%");
      break;

    case 2:
      analogWrite(MOTOR, 191); //Muestra el numero 2
      Serial.println("SEÑAL DIGITAL A 75%");
      break;
  }
    
  }
  else{
    digitalWrite(LED2,LOW);
   
  }
}
