char currentInput;
bool newData = false;
bool pumpOn = false;

char TURN_PUMP_ON = '1';
char TURN_PUMP_OFF = '0';

int PUMP_SWITCH_PIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(PUMP_SWITCH_PIN, OUTPUT);
  Serial.println("Starting program.");
}

void loop() {
  checkInput();
  if(!newData) {
    continue;
  }

  switch(currentInput) {
    case TURN_PUMP_ON:
      Serial.Println("Turning pump on.");
      digitalWrite(PUMP_SWITCH_PIN, HIGH);
      break;
    case TURN_PUMP_OFF:
      Serial.Println("Turning pump off.");
      digitalWrite(PUMP_SWITCH_PIN, LOW);
      break;
    default:
      Serial.Println("Invalid option.");
      break;
  }
}

void checkInput() {
  if(Serial.available() > 0) {
    currentInput = Serial.read();
    newData = true;
  }
}

void triggerPump() {
  
}
