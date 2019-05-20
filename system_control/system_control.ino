char currentInput;
bool newData = false;
bool pumpOn = false;

const char TURN_PUMP_ON = '1';
const char TURN_PUMP_OFF = '0';

const int PUMP_SWITCH_PIN = 30;

unsigned long lightTriggerTime;

bool isLightOn = false;

void setup() 
{
  Serial.begin(9600);
  pinMode(PUMP_SWITCH_PIN, OUTPUT);
  digitalWrite(PUMP_SWITCH_PIN, LOW);
  Serial.println("Starting program.");

  lightTriggerTime = millis();
}

void loop() 
{
//  checkInput();
//  if(!newData) {
//    return;
//  }
//
//  switch(currentInput) {
//    case TURN_PUMP_ON:
//      Serial.println("Turning pump on.");
//      digitalWrite(PUMP_SWITCH_PIN, HIGH);
//      break;
//    case TURN_PUMP_OFF:
//      Serial.println("Turning pump off.");
//      digitalWrite(PUMP_SWITCH_PIN, LOW);
//      break;
//    default:
//      Serial.println("Invalid option.");
//      break;
//  }

  unsigned long currentTime = millis();

  Serial.print("currentTime: ");
  Serial.println(currentTime);
  Serial.print("getSeconds(5): ");
  Serial.println(getSeconds(5));
  Serial.print("lightTriggerTime: ");
  Serial.println(lightTriggerTime);

  if(currentTime > getSeconds(5) && currentTime - getSeconds(5) >= lightTriggerTime) {
    Serial.println("Triggering light.");
    triggerLight();
    lightTriggerTime = currentTime;
  }

  newData = false;
}

void checkInput() {
  if(Serial.available() > 0) {
    currentInput = Serial.read();
    Serial.println("current Input: ");
    Serial.println(currentInput);
    newData = true;
  }
}

int getSeconds(int numberOfSeconds) {
  return numberOfSeconds * 1000;
}

void triggerLight() {
  isLightOn = !isLightOn;
  digitalWrite(PUMP_SWITCH_PIN, isLightOn);
}
