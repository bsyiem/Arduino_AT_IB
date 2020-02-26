//setting pins
//LED pins
const int LED_ZERO = 13;
const int LED_ONE = 12;
const int LED_TWO = 11;
const int LED_THREE = 10;
const int LED_FOUR = 9;

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

//button reading
int buttonRead = LOW;

//reaction time 
unsigned long startTime; //time led was turned on
unsigned long reactionTime; 

//flags
int isLedOn = 0; //button reading is taken only when LED is on

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
    
    //read message
    incoming = Serial.readString();

    setUpLed(incoming);
//    test2(incoming);
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
          Serial.print(reactionTime);
        }
      }
  } 

  lastButtonState = buttonRead;
}

int setUpLed(String incoming){
  if(incoming == "0"){     
//      Serial.print("ZERO");
      //turn on led 0
      digitalWrite(LED_ZERO,HIGH);
      digitalWrite(LED_ONE,LOW);
      digitalWrite(LED_TWO,LOW);
      digitalWrite(LED_THREE,LOW);
      digitalWrite(LED_FOUR,LOW);
      isLedOn = 1;
    }else if(incoming == "1"){    
//      Serial.print("ONE");
      //turn on led 1
      digitalWrite(LED_ZERO,LOW);
      digitalWrite(LED_ONE,HIGH);
      digitalWrite(LED_TWO,LOW);
      digitalWrite(LED_THREE,LOW);
      digitalWrite(LED_FOUR,LOW);   
      isLedOn = 1;
    }else if(incoming == "2"){
//      Serial.print("TWO"); 
      //turn on led 1
      digitalWrite(LED_ZERO,LOW);
      digitalWrite(LED_ONE,LOW);
      digitalWrite(LED_TWO,HIGH);
      digitalWrite(LED_THREE,LOW);
      digitalWrite(LED_FOUR,LOW);  
      isLedOn = 1;
    }else if(incoming == "3"){
//      Serial.print("THREE"); 
      //turn on led 1
      digitalWrite(LED_ZERO,LOW);
      digitalWrite(LED_ONE,LOW);
      digitalWrite(LED_TWO,LOW);
      digitalWrite(LED_THREE,HIGH);
      digitalWrite(LED_FOUR,LOW);    
      isLedOn = 1;
    }else if(incoming == "4"){
//      Serial.print("FOUR");
      //turn on led 1
      digitalWrite(LED_ZERO,LOW);
      digitalWrite(LED_ONE,LOW);
      digitalWrite(LED_TWO,LOW);
      digitalWrite(LED_THREE,LOW);
      digitalWrite(LED_FOUR,HIGH); 
      isLedOn = 1;
    }

    //start timer -  records current time 
    startTime = micros();
}

void test(String incoming){
  String a = "0";
  Serial.println(incoming);

  Serial.println(incoming == "0\n");
  Serial.println(a == "0");
  
  if(incoming == "0"){     
      Serial.print("zero"); 
    }else if(incoming == "1"){    
      Serial.print("one");     
    }else if(incoming == "2"){
      Serial.print("TWO");    
    }else if(incoming == "3"){
      Serial.print("THREE");    
    }else if(incoming == "4"){
      Serial.print("FOUR");
    }
}

int test2(String incoming){
  Serial.println(incoming);

  if(incoming == "0\n"){     
      Serial.print("zero");
      //turn on led 0
      digitalWrite(LED_ZERO,HIGH);
      digitalWrite(LED_ONE,LOW);
      digitalWrite(LED_TWO,LOW);
      digitalWrite(LED_THREE,LOW);
      digitalWrite(LED_FOUR,LOW);
      isLedOn = 1;
    }else if(incoming == "1\n"){    
      Serial.print("one");
      //turn on led 1
      digitalWrite(LED_ZERO,LOW);
      digitalWrite(LED_ONE,HIGH);
      digitalWrite(LED_TWO,LOW);
      digitalWrite(LED_THREE,LOW);
      digitalWrite(LED_FOUR,LOW);   
      isLedOn = 1;
    }else if(incoming == "2\n"){
      Serial.print("two"); 
      //turn on led 1
      digitalWrite(LED_ZERO,LOW);
      digitalWrite(LED_ONE,LOW);
      digitalWrite(LED_TWO,HIGH);
      digitalWrite(LED_THREE,LOW);
      digitalWrite(LED_FOUR,LOW);  
      isLedOn = 1;
    }else if(incoming == "3\n"){
      Serial.print("three"); 
      //turn on led 1
      digitalWrite(LED_ZERO,LOW);
      digitalWrite(LED_ONE,LOW);
      digitalWrite(LED_TWO,LOW);
      digitalWrite(LED_THREE,HIGH);
      digitalWrite(LED_FOUR,LOW);    
      isLedOn = 1;
    }else if(incoming == "4\n"){
      Serial.print("four");
      //turn on led 1
      digitalWrite(LED_ZERO,LOW);
      digitalWrite(LED_ONE,LOW);
      digitalWrite(LED_TWO,LOW);
      digitalWrite(LED_THREE,LOW);
      digitalWrite(LED_FOUR,HIGH); 
      isLedOn = 1;
    }

    //start timer -  records current time 
    startTime = micros();
}

void switchOffLeds(){
  digitalWrite(LED_ZERO,LOW);
  digitalWrite(LED_ONE,LOW);
  digitalWrite(LED_TWO,LOW);
  digitalWrite(LED_THREE,LOW);
  digitalWrite(LED_FOUR,LOW);
}
