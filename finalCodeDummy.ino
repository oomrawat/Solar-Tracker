#include <LiquidCrystal.h>
#include <IRremote.h>     //including infrared remote header file
#include <Servo.h>        //including the library of servo motor 

#define codeForZero   3910598400
#define codeForOne    4077715200 
#define codeForTwo    3877175040 
#define codeForThree  2707357440 
#define codeForFour   4144561920
#define codeForFive   3810328320
#define codeForSix    2774204160
#define codeForSeven  3175284480 
#define codeForEight  2907897600 
#define codeForNine   3041591040

String deg = "";
String intensity = "";
int RECV_PIN = 6;         // the pin where you connect the output pin of IR sensor 
IRrecv irrecv(RECV_PIN);
decode_results results;
Servo myservo;             
int initial_position = 90;   
int LDR1 = A0;            //connect The LDR1 on Pin A0
int LDR2 = A1;            //Connect The LDR2 on pin A1
int error = 5;          
int servopin = 9;         //You can change servo just makesure its on arduino's PWM pin
int val;                //rotation angle
bool cwRotation, ccwRotation;  //the states of rotation
LiquidCrystal lcd(4, 3, 10, 11, 12, 13);

void setup() 
{ 
  lcd.begin(16, 2);
  lcd.print("SOLAR TRACKER BY");
  lcd.setCursor(0, 1);
  lcd.print("  IoT Group 2   ");
  Serial.begin(9600);
  myservo.attach(servopin);  
  pinMode(LDR1, INPUT);   
  pinMode(LDR2, INPUT);
  myservo.write(initial_position);   //Move servo at 90 degree
  irrecv.enableIRIn();
  delay(2000);           
}  

void automatic()
{
  int R;
  int R1 = analogRead(LDR1); // read  LDR 1
  int R2 = analogRead(LDR2); // read  LDR 2
  int diff1= abs(R1 - R2);   
  int diff2= abs(R2 - R1);
  
  if((diff1 <= error) || (diff2 <= error)) 
  {
    
  } 

  else 
  {    
    if(R1 > R2)
    {
      initial_position = initial_position - 5;  
    }
    
    if(R1 < R2) 
    {
      initial_position = initial_position + 5; 
    }
  }
  
  R = R1 + R2;
  myservo.write(initial_position);
  deg = "";
  deg = String(initial_position);
  intensity = "";
  intensity = String(R);
  
  if (initial_position >= 180)
  {
  	 lcd.clear();
  	 lcd.print("   DEGREE: 180"); 
  } 
  
  else if (initial_position <= 0)
  {
  	 lcd.clear();
  	 lcd.print("   DEGREE: 0"); 
  }
  
  else
  {
   	lcd.clear();
  	lcd.print("   DEGREE: " + deg); 
  }

  lcd.setCursor(0, 1);
  lcd.print(" INTENSITY: " + intensity);

  delay(100);
}


void loop() 
{
  irrecv.resume();
  
  while(!irrecv.decode(&results))
  {
  automatic();
  } 

  zero:
  if (results.value == codeForZero)  // code for 0 
  {
    myservo.write(0);
    delay(15);
    lcd.clear();
    lcd.print("   DEGREE: 0   ");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForZero) 
      {
        break;
      } 
    }
  }

  one:
  if (results.value == codeForOne)  // code for 1 
  {
    myservo.write(20);
    delay(15);
   	lcd.clear();
    lcd.print("   DEGREE: 20");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
    
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForOne)
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }
        break;
      } 
    }
  }

  two:
  if (results.value == codeForTwo)  // code for 2 
  {
    myservo.write(40);
    delay(15);
    lcd.clear();
    lcd.print("   DEGREE: 40");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForTwo) 
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }

        if(results.value == codeForOne)  // code for 1
        {
          goto one;
        }

        break;
      } 
    }
  }

  three:
  if (results.value == codeForThree)  // code for 3 
  {
    myservo.write(60);
    delay(15);
    lcd.clear();
    lcd.print("   DEGREE: 60");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForThree) 
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }

        if(results.value == codeForOne)  // code for 1
        {
          goto one;
        }

        if(results.value == codeForTwo)  // code for 2
        {
          goto two;
        }

        break;
      } 
    }
  }

  four:
  if (results.value == codeForFour)  // code for 4 
  {
    myservo.write(80);
    delay(15);
    lcd.clear();
    lcd.print("   DEGREE: 80");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForFour)
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }

        if(results.value == codeForOne)  // code for 1
        {
          goto one;
        }

        if(results.value == codeForTwo)  // code for 2
        {
          goto two;
        }
        
        if(results.value == codeForThree)  // code for 3
        {
          goto three;
        }

        break;
      } 
    }
  }

  five:
  if (results.value == codeForFive)  // code for 5 
  {
    myservo.write(100);
    delay(15);
    lcd.clear();
    lcd.print("   DEGREE: 100");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForFive) 
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }

        if(results.value == codeForOne)  // code for 1
        {
          goto one;
        }

        if(results.value == codeForTwo)  // code for 2
        {
          goto two;
        }
        
        if(results.value == codeForThree)  // code for 3
        {
          goto three;
        }
        
        if(results.value == codeForFour)  // code for 4
        {
          goto four;
        }

        break;
      } 
    }
  }

  six:
  if (results.value == codeForSix)  // code for 6 
  {
    myservo.write(120);
    delay(15);
    lcd.clear();
    lcd.print("   DEGREE: 120");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForSix) 
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }

        if(results.value == codeForOne)  // code for 1
        {
          goto one;
        }
        
        if(results.value == codeForTwo)  // code for 2
        {
          goto two;
        }
        
        if(results.value == codeForThree)  // code for 3
        {
          goto three;
        }
        
        if(results.value == codeForFour)  // code for 4
        {
          goto four;
        }
        
        if(results.value == codeForFive)  // code for 5
        {
          goto five;
        }

        break;
      } 
    }
  }

  seven:
  if (results.value == codeForSeven)  // code for 7 
  {
    myservo.write(140);
    delay(15);
   	lcd.clear();
    lcd.print("   DEGREE: 140");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
    
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForSeven) 
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }

        if(results.value == codeForOne)  // code for 1
        {
          goto one;
        }
        
        if(results.value == codeForTwo)  // code for 2
        {
          goto two;
        }
        
        if(results.value == codeForThree)  // code for 3
        {
          goto three;
        }
        
        if(results.value == codeForFour)  // code for 4
        {
          goto four;
        }
        
        if(results.value == codeForFive)  // code for 5
        {
          goto five;
        }
        
        if(results.value == codeForSix)  // code for 6
        {
          goto six;
        }

        break;
      } 
    }
  }

  eight:
  if (results.value == codeForEight)  // code for 8 
  {
    myservo.write(160);
    delay(15);
    lcd.clear();
    lcd.print("   DEGREE: 160");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForEight) 
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }

        if(results.value == codeForOne)  // code for 1
        {
          goto one;
        }
        
        if(results.value == codeForTwo)  // code for 2
        {
          goto two;
        }
        
        if(results.value == codeForThree)  // code for 3
        {
          goto three;
        }
        
        if(results.value == codeForFour)  // code for 4
        {
          goto four;
        }
        
        if(results.value == codeForFive)  // code for 5
        {
          goto five;
        }
        
        if(results.value == codeForSix)  // code for 6
        {
          goto six;
        }
        
        if(results.value == codeForSeven)  // code for 7
        {
          goto seven;
        }

        break;
      } 
    }
  }

  nine:
  if (results.value == codeForNine)  // code for 9 
  {
    myservo.write(180);
    delay(15);
    lcd.clear();
    lcd.print("   DEGREE: 180");
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(results.value != codeForNine) 
      {
        if(results.value == codeForZero)  // code for 0
        {
          goto zero;
        }
        
        if(results.value == codeForOne)  // code for 1
        {
          goto one;
        }
        
        if(results.value == codeForTwo)  // code for 2
        {
          goto two;
        }
        
        if(results.value == codeForThree)  // code for 3
        {
          goto three;
        }
        
        if(results.value == codeForFour)  // code for 4
        {
          goto four;
        }
        
        if(results.value == codeForFive)  // code for 5
        {
          goto five;
        }
        
        if(results.value == 16607383)  // code for 6
        {
          goto six;
        }
        
        if(results.value == codeForSeven)  // code for 7
        {
          goto seven;
        }
        
        if(results.value == codeForEight)  // code for 8
        {
          goto eight;
        }
        
        break;
      } 
    }
  }    
}
