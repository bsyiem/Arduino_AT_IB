//button pin
const int BUTTON_PIN = 2;

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

//delay for sending in milliseconds - MUST BE ADDED to REACTION TIMES
unsigned long sendDelay = 100;

void setup() {
  Serial.begin(9600); // send and receive at 9600 baud
  
  //setting pin modes for button
  pinMode(BUTTON_PIN,INPUT);
}



void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()>0){

    //set previousIncoming to last incoming
    previousIncoming = incoming;
    
    //first check if previous event was responded to
//    checkFailedToDetect(incoming);   
    
    //read message
    incoming = Serial.readString();

    setUp(incoming);
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
          reactionTime = (lastDebounceTime - startTime) + (sendDelay * 1000);
          Serial.println(incoming+","+reactionTime);
          Serial.flush();
        }
      }
  } 

  lastButtonState = buttonRead;
}

void switchOffLeds(){
  isLedOn = 0;
}


//if participant failed to detect LED and new LED event received
//if true send "failed to detect"
void checkFailedToDetect(String previousIncoming){
  //  if and led is on then there is a missed event, send failed to detect with max reaction time allowed
  if(isLedOn == 1){
    reactionTime = (micros() - startTime) + (sendDelay * 1000);
    Serial.println(previousIncoming+","+reactionTime+",F");
    Serial.flush();
  }
  delay(sendDelay);
}

int setUp(String incoming){
  if(incoming == "0"){   
    checkFailedToDetect(previousIncoming);
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "1"){
    checkFailedToDetect(previousIncoming);   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "2"){
    checkFailedToDetect(previousIncoming);   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "3"){
    checkFailedToDetect(previousIncoming);   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "4"){
    checkFailedToDetect(previousIncoming);   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "#"){
    checkFailedToDetect(previousIncoming);
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
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "1\n"){
    checkFailedToDetect(previousIncoming);   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "2\n"){
    checkFailedToDetect(previousIncoming);   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "3\n"){
    checkFailedToDetect(previousIncoming);   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "4\n"){
    checkFailedToDetect(previousIncoming);   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "#\n"){
    checkFailedToDetect(previousIncoming);
    Serial.print("#");
    Serial.flush();
    switchOffLeds();
  }
}
