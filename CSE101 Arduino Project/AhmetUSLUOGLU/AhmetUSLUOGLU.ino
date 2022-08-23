
// Defining pins which connects parts as names for easier use.
#define led       2          
#define button_1  4
#define button_2  6
#define buzzer    8

// Defining notes frequencies as names for easier use.
#define do_ 261
#define re 294
#define mi 329
#define fa 349
#define sol 392
#define la 440
#define si 493
#define DO_ 523

int song[] = {mi,mi,fa,sol,sol,fa,mi,re,do_,do_,re,mi,mi,re,re,mi,mi,fa,sol,sol,fa, mi, re, do_, do_,
              re, mi, re, do_, do_, /*re, re, mi, do_, re, mi, fa, mi, do_, re, mi, fa, mi, re, do_ ,
              re, sol, mi, mi, mi, fa, sol, sol, fa, mi, re, do_, do_, re, mi, re, do_, do_*/};

void setup() 
{
  // Setting up buzzer and led as output , and buttons as input.
  pinMode(buzzer, OUTPUT);
  pinMode(button_1,INPUT);
  pinMode(button_2,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  char select = '0';              
  if( Serial.available())
  {
    select = Serial.read();         // Reads users input from terminal then goes to corresponding case (function).

    switch(select)
    {
      case '1':
        digitalWrite(led,HIGH);     
        break;               
      
      case '2':
        digitalWrite(led,LOW);
        break;
      
      case '3':
        for(int i=0;i<3;i++)
        {         
          digitalWrite(led,HIGH);   
          delay(500);
          digitalWrite(led,LOW);   
          delay(500);
        } 
        break;
      
      case '4':
        Square();
        break;
      
      case '5':
        Button(); 
        break;

       case '6':
        Buzzer();
        break;
    }
  }
}     

void Square()
{
  int number = 0;
  while(number == 0)
  {
     if(Serial.available()) 
     {  
        // Recieves number from terminal as string and converts it to integer then return the square result.     
        String num = Serial.readString();               
        number = num.toInt();       
        number = number * number;       
        Serial.println(number);     
        number = 1;
     }
  }
}

void Button()
{
  int state = 0;
  int quit = 0;  
  while(1)
  {
    // Reads both buttons and stores the value to variables.
    state = digitalRead(button_1);
    quit = digitalRead(button_2);
    
    // When quit is high it means red button is pushed thus arduino sends '2' and breaks loop.
    if (quit == HIGH)
    {
      Serial.println(2);
      delay(100);
      break;
    }
    
    // When state is 'HIGH' it means blue button is pushed thus arduino sends '1' and resets 'state' to 0.
    if(state == HIGH) 
    {            
      Serial.println(1);
      delay(150);
      Serial.println(0);
      digitalWrite(led, HIGH);
      delay(150);     
    } 
    // Leds turns on at every button pushed.
    delay(50);     
    digitalWrite(led, LOW);
  }
}

void Buzzer() 
{
  // Goes as much as the number of notes in the song and waits a bit at every turn. 
  for (int i = 0; i < sizeof(song)/sizeof(int); i++) 
  {
    tone(buzzer, song[i]);
    delay(350);
  }
  noTone(buzzer);
  delay(500);
}
/**/