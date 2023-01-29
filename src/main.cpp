#include <Arduino.h>

#include "Controller.hpp"
#include "ControllerSW.hpp"
#include "ControllerHW.hpp"
#include "SG_MeaSystem.hpp"
#include "SG_RawSensor.hpp"
#include "Debugpin.hpp"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(DEBUGPIN, OUTPUT);

  // SG_RawSensor* sg = new SG_RawSensor(1.0);
  SG_MeaSystem* mg = new SG_MeaSystem(1.0);
  Controller* ctrl = new ControllerHW(1.0, mg->getSequence());
  ctrl->start();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop.");
  sleep(10);
}