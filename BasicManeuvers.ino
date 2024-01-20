const int echoPin = 6;
const int trigPin = 7;

const int Left_motorpin2 = 2;
const int Left_motorpin3 = 3;

const int Right_motorpin4 = 4;
const int Right_motorpin5 = 5;

int rand_Direction;
int rand_Avoid;
int rand_Delay;

const int left_LED = 13;
const int LED_delay = 200;
const int right_LED = 8;

int safe = 20;

int distance;
long duration;

void randomizeDrive(int rand)
{
  
  if (rand == 1){ //FORWARDS
    
   // Serial.println("Driving Fowards");
  
    digitalWrite(Left_motorpin2, LOW); //left motor clockwise
    digitalWrite(Left_motorpin3, HIGH);
       
    digitalWrite(Right_motorpin4, LOW); //right motor clockwise
    digitalWrite(Right_motorpin5, HIGH);
  
  } else if (rand == 2)
  { //LEFT
    
  //  Serial.println("Driving Leftwards");
    
    for (int x = 0; x < 3; x++)
    {
      
      digitalWrite(left_LED, HIGH);
      delay(LED_delay);
      digitalWrite(left_LED, LOW);
      delay(LED_delay);
    }
    
    digitalWrite(Left_motorpin3, LOW); 
    digitalWrite(Left_motorpin2, LOW);
    
    digitalWrite(Right_motorpin5, LOW); //right motor counter
    digitalWrite(Right_motorpin4, HIGH);
  
  } else if (rand == 3)
  { //RIGHT
    
   // Serial.println("Driving Rightwards");
    
    for (int x = 0; x < 3; x++)
    {
      
      digitalWrite(right_LED, HIGH);
      delay(LED_delay);
      digitalWrite(right_LED, LOW);
      delay(LED_delay);
    }
    
    digitalWrite(Right_motorpin4, LOW);
    digitalWrite(Right_motorpin5, LOW);
  
    digitalWrite(Left_motorpin3, HIGH); //left motor CLOCK
    digitalWrite(Left_motorpin2, LOW);
  }
}

void backwards(){ 
  
  //Serial.println("Driving Backwards");
  
  digitalWrite(Left_motorpin3, LOW); //left motor counter
  digitalWrite(Left_motorpin2, HIGH);
    
  digitalWrite(Right_motorpin5, LOW); //right motor counter
  digitalWrite(Right_motorpin4, HIGH);
}

void halt(){
  
  digitalWrite(Left_motorpin3, LOW); //left motor counter
  digitalWrite(Left_motorpin2, LOW);
    
  digitalWrite(Right_motorpin5, LOW); //right motor counter
  digitalWrite(Right_motorpin4, LOW);
}
 

void setup() {

pinMode(trigPin, OUTPUT);
pinMode(Left_motorpin2, OUTPUT);
pinMode(Left_motorpin3, OUTPUT);
pinMode(Right_motorpin4, OUTPUT);
pinMode(Right_motorpin5, OUTPUT);
pinMode(echoPin, INPUT);
  
Serial.begin(9600);
}
 

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
// Calculating the distance
distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
// Displays the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance); // add ln
//Serial.println(" cm");
rand_Delay = random(300,1501);
  
  if (distance >= safe){
    
    rand_Direction = random(1,4); //1 - 3
   // Serial.println(rand_Direction);
    
    randomizeDrive(rand_Direction);
    delay(rand_Delay);
  }
  
  else if (distance < safe){
    
    rand_Avoid = random(2,4);
    
    //Serial.print("The randomized number for left/right is: ");
   // Serial.println(rand_Avoid);
    halt();
    delay(rand_Delay);
    backwards();
    delay(rand_Delay);
    randomizeDrive(rand_Avoid);
    delay(rand_Delay);
  }
  
  
}
 

