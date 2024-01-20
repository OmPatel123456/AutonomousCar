const int echoPin = 6; //declares echo pin on sensor to digital I/O pin 6
const int trigPin = 7; //declares trig pin on sensor to digital I/O pin 7

//const int Left_motorpin2 = 2; //declares one of the left motor controlling pins to digital I/O pin 2
//const int Left_motorpin3 = 3; //declares one of the left motor controlling pins to digital I/O pin 3

int Left_motorpin[] = {2, 3};

//const int Right_motorpin4 = 4; //declares one of the right motor controlling pins to digital I/O pin 4
//const int Right_motorpin5 = 5; //declares one of the left motor controlling pins to digital I/O pin 5

int Right_motorpin[] = {4, 5};

int rand_Direction;// declares variable for randomly generated number for when the car is in a safe position
int rand_Avoid; // declares variable for randomly generated number for when the car is in a not in a safe position
int rand_Delay; //declares variable for randomly generated number for a delay time between car directions

//const int left_LED = 13; //declares variable left car headlight  to digital I/O pin 13
//const int right_LED = 8; //declares variable left car headlight  to digital I/O pin 13

int LEDS[] = {13, 8};

int safe = 20; //sets car's safe position at 20 centimeters

float distance; //declares variable that holds distance between car's sensor and object in decimals
long duration; // declares variable that holds the time the ultrasonic wave reaches the object and comes back to the sensor in microseconds


// function that chooses a random direction when the car is in a safe position(takes a randomly generated number)
void randomizeDrive(int rand)
{
  
  if (rand == 1){ // block for forwards direction
    
    Serial.println("Driving Forwards"); //prints to serial monitor
    
    digitalWrite(Left_motorpin[0], LOW); //rotates left motor clockwise
    digitalWrite(Left_motorpin[1], HIGH);
       
    digitalWrite(Right_motorpin[0], LOW); //roates right motor clockwise
    digitalWrite(Right_motorpin[1], HIGH);
  
    // block for leftwards direction
  } else if (rand == 2) 
  { 
    
    Serial.println("Driving Leftwards");
    
    for (int x = 0; x < 3; x++){ // blinks left headlight 3 times 
      
      digitalWrite(LEDS[0], HIGH); // sends 5V to left LED
      delay(200); // delay for 200 ms
      digitalWrite(LEDS[0], LOW); // sends 0V to left LED
      delay(200);
    }
    
    //stops left motor rotation
    for (int n = 0; n < 2; n++){
      
      digitalWrite(Left_motorpin[n], LOW); 
    }
    
    //rotates right motor counter-clockwise
    digitalWrite(Right_motorpin[1], LOW); 
    digitalWrite(Right_motorpin[0], HIGH);
  
    // block for rightwards direction
  } else if (rand == 3){ 
    
    Serial.println("Driving Rightwards");
    
    for (int x = 0; x < 3; x++){ //blinks right headlight 3 times
      
      digitalWrite(LEDS[1], HIGH); // sends 5V to right LED
      delay(200);
      digitalWrite(LEDS[1], LOW); // sends 0V to left LED
      delay(200);
    }
    
    // stops right motor rotation
    for (int q = 0; q < 2; q++){
      
      digitalWrite(Right_motorpin[q], LOW); 
    }
    
    // rotates left motor clockwise
    digitalWrite(Left_motorpin[1], HIGH);
    digitalWrite(Left_motorpin[0], LOW);
  }
}

// function for moving car in a backwards direction
void backwards(){ 
  
  Serial.println("Driving Backwards");
  
  // rotates left motor counter-clockwise
  digitalWrite(Left_motorpin[1], LOW);
  digitalWrite(Left_motorpin[0], HIGH);
    
  // rotates right motor counter-clockwise
  digitalWrite(Right_motorpin[1], LOW); 
  digitalWrite(Right_motorpin[0], HIGH);
}

// fucntion that stops all motor(no direction)
void halt(){
    
  // stops left motor direction
  for (int p = 0; p < 2; p++){
    
    digitalWrite(Left_motorpin[p], LOW);
  }
  
  // stops left motor direction
  for (int v = 0; v < 2; v++){
    
    digitalWrite(Right_motorpin[v], LOW);
  }     
}
 

void setup() {

pinMode(trigPin, OUTPUT); // declares pin 7 as an OUTPUT pin

  for (int i = 0; i < 2; i++){ 
    
    pinMode(Left_motorpin[i], OUTPUT); // declares both left motor pins as OUTPUT
    pinMode(Right_motorpin[i], OUTPUT); // declares both right motor pins as OUTPUT
  }
  
  for (int e = 0; e < 2; e++){
                                                  
    pinMode(LEDS[e], OUTPUT); // declares both right and left LEDs as OUTPUT
  }                                                  
pinMode(echoPin, INPUT); // delclares pin 6 as an INPUT pin
  
Serial.begin(9600); // connects serial port to computer at 9600 bits
}
 
// loop that runs infinitely
void loop() {
  
// Clears the trigPin condition
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
  
// Sets the trigPin HIGH (ACTIVE) for 10 microseconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
  
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculates the distance(cm)
distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
//Displays the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.print(distance); 
Serial.println(" cm");

rand_Delay = random(500,1501); // randomly generates a delay time from 300 to 1501
  
  // block runs if car is in a safe position
  if (distance >= safe){
    
    rand_Direction = random(1,4); // randomly generates number from 1 to 3 to pick a direction for car to move when it is safe
  
    randomizeDrive(rand_Direction); //calls fucntion to drive randomly while safe and passes it an integer type parameter
    delay(rand_Delay);
  }
  
  // block runs if car is not in a safe position to dodge object
  else if (distance < safe){
    
    Serial.println("Driver is NOT SAFE");
    
    rand_Avoid = random(2,4); // randomly generates the numbers 2 or 3
    
    halt(); // calls function to stop all motors(and directions)
    
    // turns on the headlights as the car comes to a stop
    digitalWrite(LEDS[0], HIGH); 
    digitalWrite(LEDS[1], HIGH);
    
    delay(rand_Delay);
    
    // turns off all headlights as car is not in a stop anymore
    digitalWrite(LEDS[0], LOW);
    digitalWrite(LEDS[1], LOW);
    
    backwards(); // calls fucntion to drive the car in backward direction
    delay(rand_Delay); 
    
    randomizeDrive(rand_Avoid); //calls function to drive randomly and uses randomly generated number to go left or right
    delay(rand_Delay);
  }
}


