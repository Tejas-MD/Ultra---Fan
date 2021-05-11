#include <Arduino.h>

const int fanRelay = 25;
double lastRecordedOffTime,lastRecordedOnTime = 0;

bool overRideOn = false;
const int touchPin = 4; 
int touchValue;
int threshold = 30;   // Normal value = 65


void timeBasedFan()
{
  if(millis() - lastRecordedOffTime > 300000 && millis() - lastRecordedOffTime < 320000 ) // Switch on fan after 5 minutes of being switched off
  {     
    digitalWrite(fanRelay, LOW);
    lastRecordedOnTime = millis();
  }

  if(millis() - lastRecordedOnTime > 30000 && millis() - lastRecordedOnTime < 32000 ) // Switch Off fan after 30 seconds of being switched on 
    {
      digitalWrite(fanRelay, HIGH);
      lastRecordedOffTime = millis();
    }
}

void isTouched(){
  if(touchRead(touchPin) < threshold)
  {
    delay(1000); // Debounce Delay
      if(touchRead(touchPin) < threshold)
      {
        if(overRideOn)
        {
          overRideOn = false;
          digitalWrite(fanRelay, HIGH);
          Serial.println("OverRide ON Mode: Disabled, Turning OFF Fan");
          Serial.println("Going back to timed mode.");
        }
        else{
        overRideOn = true;
        digitalWrite(fanRelay, LOW);
        Serial.println("OverRide ON Mode, Turning ON Fan");
        }
      }

  }
}


void setup() {
  pinMode (fanRelay, OUTPUT);
  digitalWrite(fanRelay, HIGH);
  Serial.begin(9600);
}

void loop() {

  // touchValue = touchRead(touchPin);
  // Serial.println(touchValue);
  isTouched();

  if(overRideOn != true)
    timeBasedFan();

  delay(600);
}