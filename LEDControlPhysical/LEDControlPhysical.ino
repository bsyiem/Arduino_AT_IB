//setting pins
//LED pins
const int LED_ZERO = 12;
const int LED_ONE = 11;
const int LED_TWO = 10;
const int LED_THREE = 9;
const int LED_FOUR = 8;

//button pin
const int BUTTON_PIN = 2;


//setting states
//int ledState0 = LOW;
//int ledState1 = LOW;
//int ledState2 = LOW;
//int ledState3 = LOW;
//int ledState4 = LOW;
int buttonState = LOW;
int lastButtonState = LOW;

//debounce times
// button presses can flicker, if the state has been constant for more than the debounceDelay, then we assume a definite button press
unsigned long lastDebounceTime = 0; //the last time the outut pin was toggled
long debounceDelay = 20000; //20millisecond

//Serial input
String incoming = "";
String previousIncoming = ""; //in case of missed event

//button reading
int buttonRead = LOW;

//reaction time 
unsigned long startTime; //time led was turned on
unsigned long reactionTime; 

//flags
int isLedOn = 0; //button reading is taken only when LED is on
//int isMissed = 0; //send failed to detect event if this is true

void setup() {
  Serial.begin(9600); // send and receive at 9600 baud

  //setting pin modes for led
  pinMode(LED_ZERO,OUTPUT);
  pinMode(LED_ONE,OUTPUT);
  pinMode(LED_TWO,OUTPUT);
  pinMode(LED_THREE,OUTPUT);
  pinMode(LED_FOUR,OUTPUT);

  //setting pin modes for button
  pinMode(BUTTON_PIN,INPUT);

  //set init led states
  digitalWrite(LED_ZERO,LOW);
  digitalWrite(LED_ONE,LOW);
  digitalWrite(LED_TWO,LOW);
  digitalWrite(LED_THREE,LOW);
  digitalWrite(LED_FOUR,LOW);
}



void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()>0){

    //set previousIncoming to last incoming
    previousIncoming = incoming;
//    checkFailedToDetect(incoming);   
    
    //read message
    incoming = Serial.readString();

    setUpLed(incoming);
//    test(incoming);
  }

  if(isLedOn == 1){
    buttonRead = digitalRead(BUTTON_PIN);  
  }
  
  if(buttonRead != lastButtonState){
    //reset debounce time
    lastDebounceTime = micros();
  }

  if((micros() - lastDebounceTime) > debounceDelay){
      //reading is stable
      if(buttonRead != buttonState){
        buttonState = buttonRead;
        
        //record the reaction time.
        if(buttonState == HIGH){
          switchOffLeds();
          reactionTime = lastDebounceTime - startTime;
          Serial.println(incoming+","+reactionTime);
          Serial.flush();
        }
      }
  } 

  lastButtonState = buttonRead;
}

void switchOffLeds(){
  digitalWrite(LED_ZERO,LOW);
  digitalWrite(LED_ONE,LOW);
  digitalWrite(LED_TWO,LOW);
  digitalWrite(LED_THREE,LOW);
  digitalWrite(LED_FOUR,LOW);
  isLedOn = 0;
}


//if participant failed to detect LED and new LED event received
//if true send "failed to detect"
//void checkFailedToDetect(String incoming){ 
//    if(isLedOn == 1){
//      reactionTime = micros() - startTime;
//      Serial.println("Failed to detect "+incoming+":"+reactionTime);
//      Serial.flush();
//    }
//}


//if participant failed to detect LED and new LED event received
//if true send "failed to detect"
void checkFailedToDetect(String previousIncoming){
  //  if and led is on then there is a missed event, send failed to detect with max reaction time allowed
  if(isLedOn == 1){
    reactionTime = micros() - startTime;
    Serial.println(previousIncoming+","+reactionTime+",F");
    Serial.flush();
  }
}

int setUpLed(String incoming){
 
  if(incoming == "0"){   
    checkFailedToDetect(previousIncoming);
    
    //start timer -  records current time 
    startTime = micros();
    //turn on led 0
    digitalWrite(LED_ZERO,HIGH);
    digitalWrite(LED_ONE,LOW);
    digitalWrite(LED_TWO,LOW);
    digitalWrite(LED_THREE,LOW);
    digitalWrite(LED_FOUR,LOW);
    isLedOn = 1;
  }else if(incoming == "1"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros(); 
    //turn on led 1
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_ONE,HIGH);
    digitalWrite(LED_TWO,LOW);
    digitalWrite(LED_THREE,LOW);
    digitalWrite(LED_FOUR,LOW);   
    isLedOn = 1;
  }else if(incoming == "2"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();
    //turn on led 1
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_ONE,LOW);
    digitalWrite(LED_TWO,HIGH);
    digitalWrite(LED_THREE,LOW);
    digitalWrite(LED_FOUR,LOW);  
    isLedOn = 1;
  }else if(incoming == "3"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();
    //turn on led 1
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_ONE,LOW);
    digitalWrite(LED_TWO,LOW);
    digitalWrite(LED_THREE,HIGH);
    digitalWrite(LED_FOUR,LOW);    
    isLedOn = 1;
  }else if(incoming == "4"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();
    //turn on led 1
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_ONE,LOW);
    digitalWrite(LED_TWO,LOW);
    digitalWrite(LED_THREE,LOW);
    digitalWrite(LED_FOUR,HIGH); 
    isLedOn = 1;
  }else if(incoming == "#"){
    checkFailedToDetect(previousIncoming);
    delay(1000);
    // string "#" is sent as a terminating character
    Serial.print("#");
    Serial.flush(); 
    switchOffLeds();
  }
}


//this works with the serial monitor
// "\n" needed
int test(String incoming){
  
  if(incoming == "0\n"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();    
    Serial.println("zero");
    Serial.flush();
    //turn on led 0
    digitalWrite(LED_ZERO,HIGH);
    digitalWrite(LED_ONE,LOW);
    digitalWrite(LED_TWO,LOW);
    digitalWrite(LED_THREE,LOW);
    digitalWrite(LED_FOUR,LOW);
    isLedOn = 1;
  }else if(incoming == "1\n"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();
    Serial.println("one");
    Serial.flush();
    //turn on led 1
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_ONE,HIGH);
    digitalWrite(LED_TWO,LOW);
    digitalWrite(LED_THREE,LOW);
    digitalWrite(LED_FOUR,LOW);   
    isLedOn = 1;
  }else if(incoming == "2\n"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();
    Serial.println("two");
    Serial.flush(); 
    //turn on led 1
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_ONE,LOW);
    digitalWrite(LED_TWO,HIGH);
    digitalWrite(LED_THREE,LOW);
    digitalWrite(LED_FOUR,LOW);  
    isLedOn = 1;
  }else if(incoming == "3\n"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();
    Serial.println("three");
    Serial.flush(); 
    //turn on led 1
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_ONE,LOW);
    digitalWrite(LED_TWO,LOW);
    digitalWrite(LED_THREE,HIGH);
    digitalWrite(LED_FOUR,LOW);    
    isLedOn = 1;
  }else if(incoming == "4\n"){
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();
    Serial.println("four");
    Serial.flush();
    //turn on led 1
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_ONE,LOW);
    digitalWrite(LED_TWO,LOW);
    digitalWrite(LED_THREE,LOW);
    digitalWrite(LED_FOUR,HIGH); 
    isLedOn = 1;
  }else if(incoming == "#\n"){
    checkFailedToDetect(previousIncoming);
    delay(1000);
    // string "#" is sent as a terminating character
    Serial.print("#");
    Serial.flush();
    switchOffLeds(); 
  }
}
