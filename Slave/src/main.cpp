#include <Arduino.h>

#include "ABSensorBlock.hpp"

#include <iostream>

ABSensorBlock* fr(nullptr);
ABSensorBlock* fl(nullptr);
ABSensorBlock* br(nullptr);
ABSensorBlock* bl(nullptr);

void setup() {
  Serial.begin(115200);
  bl = new ABSensorBlock(17, 16);
  fl = new ABSensorBlock(26, 25);
  fr = new ABSensorBlock(13, 4);
  br = new ABSensorBlock(12, 14);
}

void loop() {
  // std::cout << "FR: " << fr->getPosition() << std::endl;
  // std::cout << "FL: " << fl->getPosition() << std::endl;
  // std::cout << "BR: " << br->getPosition() << std::endl;
  // std::cout << "BL: " << bl->getPosition() << std::endl;
  std::cout << fl->getPosition() << ", " << fr->getPosition() << ", " << bl->getPosition() << ", " << br->getPosition() << std::endl;
  delay(1000);
}