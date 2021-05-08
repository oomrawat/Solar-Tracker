#include <LiquidCrystal.h>  // Including the library file of LCD Display
#include <IRremote.h>       // Including the library file of Infrared Remote
#include <Servo.h>          // Including the library file of Servo Motor 

// Codes of the remote buttons (converted to decimal from hexadecimal)
int codes[] = {0, 2040, 2295, 2550, 2805, 3060, 3315}; 

// Empty strings to print later using the LCD Display
String deg = "";
String intensity = "";

// Declaring all pins for components
int RECV_PIN = 6;         // Pin for IR Sensor (Digital)
int LDR1 = A1;            // Pin for LDR1 on Pin A1 (Analog)
int LDR2 = A0;            // Pin for LDR2 on Pin A0 (Analog)
int servopin = 9;         // Pin for Servo Motor (Digital PWM)
LiquidCrystal lcd(4, 3, 10, 11, 12, 13); // Pins for the LCD Display

IRrecv irrecv(RECV_PIN);
decode_results results;
Servo myservo; 

// Global variables for Servo
int initial_position = 90;   
int error = 5;          


void setup() 
{ 
  lcd.begin(16, 2); // Size of LCD
  lcd.print("SOLAR TRACKER BY");
  lcd.setCursor(0, 1); // Changing line
  lcd.print("  IoT Group 2   ");

  Serial.begin(9600);

  // We take inputs from the LDR's, hence we set them as inputs
  pinMode(LDR1, INPUT);   
  pinMode(LDR2, INPUT);
  
  myservo.attach(servopin); 
  myservo.write(initial_position);   // Move Servo at 90 degree
  
  irrecv.enableIRIn();
  
  delay(2000);           
}  


void loop() 
{
  
  irrecv.resume(); // Accept a value from the remote
  
  // This loop keeps the circuit in automatic mode until a button is pressed
  while(!irrecv.decode(&results))
  {
  automatic();
  } 

  // Checking for which button is pressed, and call the function accordingly
  for (int i=1; i<=6; i++)
  {
    // This recieves and decodes the code receieved from the remote, and convert it to an integer
    if (irrecv.decodedIRData.decodedRawData == codes[i]) 
    {
      servoAction(i); // Calling the function where the motor works
    }
  }

}

// Self defined function
void servoAction(int i)
{   
    int angle = i*30; // Setting the degree according to the button pressed
    deg = ""; // Erase the previous value of deg, to print a new value on LCD
    deg = String(angle); // Store the new value in deg (as a string)
    myservo.write(angle);
    delay(15);

    // Printing on the LCD
    
    lcd.clear();
    lcd.print("   DEGREE:" + deg);
    lcd.setCursor(0, 1);
    lcd.print("  (MANUAL-MODE) "); 
   
    // This loop keeps our Servo at the current position until another button is pressed 

    while(1)
    {
      if (irrecv.decode(&results)) 
      {
        irrecv.resume();   // Receive the next value
      }
      
      if(irrecv.decodedIRData.decodedRawData != codes[i]) 
      {
        for (int j=1; j<=6; j++)
        {
          if(irrecv.decodedIRData.decodedRawData == codes[j])  // Checking which button is pressed
          {
            // Recursion
            servoAction(j); // Calling the same function according to the new button pressed
          }
        }
        // This takes our Servo back to the automatic mode
        break; // Break the while loop, if none of the 6 specified buttons are pressed
      }
    }
}

// Self defined function for automatic mode
void automatic()
{
  int R1 = analogRead(LDR1); // Read LDR 1
  int R2 = analogRead(LDR2); // Read LDR 2
  int diff = abs(R1 - R2);   // Calculating the absolute differece between the intensities 
    
  if((diff <= error)) 
  {  
    // If the difference is less than the error (5), nothing needs to be done
    // It is almost the same
  } 

  // If the difference is greater than the error (5)
  else 
  { 
    // Changes the position of the motor in clockwise direction if condition satisfies   
    if(R1 > R2)
    {
      initial_position = initial_position - 10;  
    }
    
    // Changes the position of the motor in anti-clockwise direction if condition satisfies
    if(R1 < R2) 
    {
      initial_position = initial_position + 10; 
    }
  }
  
  // Emptying the string deg and intensity to store and print a new value

  deg = "";
  deg = String(initial_position);
  
  intensity = "";
  int R = R1 + R2; // Total intensity of light
  intensity = String(R); 
  
  // Printing on the LCD
  
  if (initial_position >= 180) // Maximum value for the servo is 180, can't be higher
  {
     initial_position = 180; 
     lcd.clear();
     lcd.print("   DEGREE: 180"); 
  } 
  
  else if (initial_position <= 0) // Minimum value for the servo is 0, can't be lower
  {
     initial_position = 0;
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

  myservo.write(initial_position); // Set position as calculated on the servo
  delay(10);
}