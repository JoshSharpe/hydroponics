char currentInput;
bool newData = false;
bool pumpOn = false;

const char TURN_PUMP_ON = '1';
const char TURN_PUMP_OFF = '0';
const char TURN_LIGHTS_ON = '2';
const char TURN_LIGHTS_OFF = '3';

const unsigned long NUMBER_OF_SECONDS_LIGHT = 1800;
const unsigned long NUMBER_OF_SECONDS_PUMP = 1800;

const int PUMP_SWITCH_PIN = 38;
const int LIGHTS_SWITCH_PIN = 36;

unsigned long lightTriggerTime;
unsigned long pumpTriggerTime;

bool isLightOn = true;
bool isPumpOn = true;

void setup() 
{
  Serial.begin(9600);
  pinMode(PUMP_SWITCH_PIN, OUTPUT);
  pinMode(LIGHTS_SWITCH_PIN, OUTPUT);
  digitalWrite(PUMP_SWITCH_PIN, HIGH);
  digitalWrite(LIGHTS_SWITCH_PIN, HIGH);
  Serial.println("Starting program.");

  lightTriggerTime = millis();
  pumpTriggerTime = millis();
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
//      Serial.print("Invalid option. Found: ");
//      Serial.println(currentInput);
//      break;
//  }

  unsigned long currentTime = millis();
  unsigned long elapsedTimeForLights = currentTime - lightTriggerTime;
  unsigned long elapsedTimeForPump = currentTime - pumpTriggerTime;

  Serial.print("elapsedTime: ");
  Serial.println(elapsedTimeForLights);
  Serial.print("NUMBER_OF_SECONDS_LIGHT: ");
  Serial.println(NUMBER_OF_SECONDS_LIGHT);
  Serial.print("NUMBER_OF_SECONDS_LIGHT: * 1000 ");
  Serial.println(NUMBER_OF_SECONDS_LIGHT * 1000);
  Serial.print("getSeconds(NUMBER_OF_SECONDS_LIGHT): ");
  Serial.println(getSeconds(NUMBER_OF_SECONDS_LIGHT));
  Serial.print("lightTriggerTime: ");
  Serial.println(lightTriggerTime);

  if(elapsedTimeForLights > getSeconds(NUMBER_OF_SECONDS_LIGHT)) {
    triggerLight();
    lightTriggerTime = millis();
  }
  
  if(elapsedTimeForPump > getSeconds(NUMBER_OF_SECONDS_PUMP)) {
    triggerPump();
    pumpTriggerTime = millis();
  }
  
//  newData = false;
  delay(1000);
}

void checkInput() {
  if(Serial.available() > 0) {
    currentInput = Serial.read();
    Serial.println("current Input: ");
    Serial.println(currentInput);
    newData = true;
  }
}

unsigned long getSeconds(unsigned long numberOfSeconds) {
  return numberOfSeconds * (unsigned long)1000;
}

void triggerLight() {
  isLightOn = !isLightOn;
  Serial.print("Triggering lights to .");
  Serial.println(isLightOn);
  digitalWrite(LIGHTS_SWITCH_PIN, isLightOn);
}

void triggerPump() {
  isPumpOn = !isPumpOn;
  Serial.print("Triggering pump to .");
  Serial.println(isPumpOn);
  digitalWrite(PUMP_SWITCH_PIN, isPumpOn);
}
