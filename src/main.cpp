#include <Arduino.h>
#include "Controller.hpp"
#include "SG_MeaSystem.hpp"
#include "SG_RawSensor.hpp"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  SG_RawSensor* sg = new SG_RawSensor(1.0);
  Controller* ctrl = new Controller(1.0, sg->getSequence());
  ctrl->start();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello world.");
  sleep(10);
}