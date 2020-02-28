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

//button reading
int buttonRead = LOW;

//reaction time 
unsigned long startTime; //time led was turned on
unsigned long reactionTime; 

//flags
int isLedOn = 0; //button reading is taken only when LED is on

void setup() {
  Serial.begin(9600); // send and receive at 9600 baud
  
  //setting pin modes for button
  pinMode(BUTTON_PIN,INPUT);
}



void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()>0){

    //first check if previous event was responded to
    checkFailedToDetect(incoming);   
    
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
          reactionTime = lastDebounceTime - startTime;
          Serial.println(incoming+":"+reactionTime);
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
void checkFailedToDetect(String incoming){ 
    if(isLedOn == 1){
      reactionTime = micros() - startTime;
      Serial.println("Failed to detect "+incoming+":"+reactionTime);
      Serial.flush();
    }
}

int setUp(String incoming){
  if(incoming == "0"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "1"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "2"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "3"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "4"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "#"){
    Serial.print("#");
    Serial.flush();
    switchOffLeds();
  }
}


//this works with the serial monitor
// "\n" needed
int test(String incoming){
  Serial.println(incoming);
  Serial.flush();

  if(incoming == "0\n"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "1\n"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "2\n"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "3\n"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "4\n"){   
    //start timer -  records current time 
    startTime = micros();
    Serial.print("$");
    Serial.flush();
    isLedOn = 1;
  }else if(incoming == "#\n"){
    Serial.print("#");
    Serial.flush();
    switchOffLeds();
  }
}
