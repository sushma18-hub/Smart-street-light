

double startTime = 0;               //Initialising the start time
double endTime = 0;                 //Initialising the end time
double timeTakenInSeconds = 0;      //Difference between start and end time in seconds
double speedOfObject = 0;           //Holds the value distance divided by time taken (speed)
const double distance = 0.15;       // Distance between the two sensors is set to 1 metre
int executed = 0;                   //Flag to run the code in the loop only once. When set to 1, code in the loop is not executed.
const int trigpin1= 1;              //start ultrasonic trigger pin
const int echopin1= 2;              //start ultrasonic echo pin
const int trigpin2= 3;              //stop ultrasonic trigger pin
const int echopin2= 4;              //stop ultrasonic echo pin
long duration1;                     //Ultrasonic duration
long duration2;
int distance1;                      //Ultrasonic distance
int distance2;  
int dist1 = 500;
int dist2 = 500;
double speed1=0;
int pirPin = 7;  
int bulb = 10;
int dim = 5;                        //dim state led pin
int bulb1_2 = 11;
int bulb3_4 = 12;
int bulb5_6 = 9;
const int ledPin = 13;
const int ldrPin = A0;              //LDR pin analog input pin

void setup() {

  Serial.begin(9600);
  //Sets the pin modes of sensors and LEDs
  pinMode(trigpin1,OUTPUT);  
  pinMode(echopin1,INPUT);
  pinMode(trigpin2,OUTPUT);  
  pinMode(echopin2,INPUT); 
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(bulb, OUTPUT);
  pinMode(dim, OUTPUT);
  pinMode(bulb1_2, OUTPUT);
  pinMode(bulb3_4, OUTPUT);
  pinMode(bulb5_6, OUTPUT);  
}

//Initialising variables
unsigned long StartTime = 0;
int n=1;
int flag=0;
int pirStat=0;
int started=0;
int starting =0;

void loop(){
  pirStat = digitalRead(pirPin);
  int ldrStatus = analogRead(ldrPin);
   Serial.println(ldrStatus);
   if (ldrStatus <= 20)                 //Checks for light intensity
   {
    digitalWrite(dim, HIGH);            //Dim lights are turned on
    if(started==0 && flag==0)
     
    {Serial.println("ON");
    }
    digitalWrite(ledPin, HIGH);
    
    if(pirStat == HIGH){                //check if motion is detected
        starting=1;
      }
      else{starting = 0;}
       
        if (starting == HIGH)
        {
          
          Serial.println("detected by PIR");
          digitalWrite(bulb, HIGH);
          start();
          delay(1000);
          stop1();
          dist1=start();                //returns distance data from first ultrasonic
          dist2 = stop1();              //returns distance data from second ultrasonic
          Serial.print("start");
          Serial.println(dist1);
          Serial.print("stop");
          Serial.println(dist2);
          flag=1;
                if(dist1 < 40 && flag==1)  //checks if the vehicle is within a particular threshold at first ultrasonic
                { 
                     Serial.println(" ***************************************************************** ");
                     Serial.println("STARTED");
                     Serial.println(" ******************************************************************* ");
                     StartTime = millis();
                     Serial.print("-------------------------------------");
                     Serial.print(" time: ");
                     Serial.println(startTime/1000);
                     started = 1;
                }
                if(dist2 < 40 && started==1)  //checks if the vehicle is within a particular threshold at second ultrasonic
                {
                     Serial.println(" ********************************************************* ");
                     Serial.println("STOPPED");
                     Serial.println(" ********************************************************* ");
                     unsigned long CurrentTime = millis();
                     unsigned long ElapsedTime = CurrentTime - StartTime;
                     Serial.print("-------------------------------------");
                     Serial.print(" time: ");
                     Serial.println( ElapsedTime/1000);
                     speed1 = 3.1/(ElapsedTime/1000);
                     Serial.println("---------------------");
                     Serial.print(speed1);
                     Serial.println("m/sec");
                     digitalWrite(bulb, LOW);
                     StartTime = 0;
                     flag=0;
                     started = 0;
                     starting=0;
                     lights();                        
                }  
         }
   }
     
       else
            {
                 digitalWrite(dim, LOW);
                 Serial.println("OFF");
                 digitalWrite(ledPin, LOW);
                 digitalWrite(bulb, LOW);
                 digitalWrite(bulb1_2, LOW);
                 digitalWrite(bulb3_4, LOW);
                 digitalWrite(bulb5_6, LOW);
                 starting = 0;                
            }    
            
        }

       
// User defined function definition 
int start(){                              // function that returns distance value of first ultrasonic sensor
    digitalWrite(trigpin1,HIGH);  
    delayMicroseconds(10);  
    digitalWrite(trigpin1,LOW);  
    duration1=pulseIn(echopin1,HIGH);  
    distance1 = (duration1*0.034)/2;
    Serial.print("----------------11iteration ");
    Serial.println(n++);
    
    Serial.print("start ");
    Serial.println(distance1);
    return distance1;
  }
  
int stop1(){                              // function that returns distance value of second ultrasonic sensor
    digitalWrite(trigpin2,HIGH);  
    delayMicroseconds(10);  
    digitalWrite(trigpin2,LOW);  
    duration2=pulseIn(echopin2,HIGH);  
    distance2 = (duration2*0.034)/2;
    Serial.print("stop ");                //Turn on the LED
    Serial.println(distance2);
    Serial.println("-----------------------end ");
    return distance2;
    
  }

void slow(){                              //function that is called when the vehicle is slow
    Serial.println("Vehicle is in slow speed");
    digitalWrite(bulb, HIGH);
    delay(2500);                          //delay of 2.5 seconds between two poles
    digitalWrite(bulb1_2, HIGH);
    delay(2500);
    digitalWrite(bulb3_4, HIGH);
    delay(2500);
    digitalWrite(bulb5_6, HIGH);
    
    delay(8500);                          //delay of 8.5 seconds after which the lights start to turn off
    
    digitalWrite(bulb, LOW);
    delay(2500);
    digitalWrite(bulb1_2, LOW);
    delay(2500);
    digitalWrite(bulb3_4, LOW);
    delay(2500);
    digitalWrite(bulb5_6, LOW);
  }

void fast(){                              //function that is called when the vehicle is fast
    Serial.println("Vehicle is in fast speed");
    digitalWrite(bulb, HIGH);
    delay(500);                           //delay of 0.5 seconds between two poles
    digitalWrite(bulb1_2, HIGH);
    delay(500);
    digitalWrite(bulb3_4, HIGH);
    delay(500);
    digitalWrite(bulb5_6, HIGH);
    
    delay(3000);                          //delay of 3 seconds after which the lights start to turn off
    
    digitalWrite(bulb, LOW);
    delay(500);
    digitalWrite(bulb1_2, LOW);
    delay(500);
    digitalWrite(bulb3_4, LOW);
    delay(500);
    digitalWrite(bulb5_6, LOW);
  }    


void lights(){                            //function that controls rate of turning on lights
    if(speed1<1 && speed1>0){
                        slow();
                        }
    else if(speed1>1) {
                        fast();
                      }
