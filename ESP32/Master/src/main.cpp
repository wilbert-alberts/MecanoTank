#include <Arduino.h>
#include <iostream>

#include "Debugpin.hpp"

#include "Sequencer.hpp"
#include "SequencerSW.hpp"
#include "SequencerHW.hpp"

#include "SG_MeaSystem.hpp"
#include "SG_RawSensor.hpp"
#include "SG_MotorIntegration.hpp"
#include "SG_SingleMotorInterface.hpp"

#include "Tracer.hpp"

#define REDBUTTONPIN (35)

void traceConsumer(void *obj);
void waitUntilStarted(uint8_t pin);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(DEBUGPIN, OUTPUT);
  pinMode(REDBUTTONPIN, INPUT);

  std::cout << "Push button" << std::endl;

  // waitUntilStarted(REDBUTTONPIN);

  std::cout << "Starting" << std::endl;

  // SG_RawSensor *sg = new SG_RawSensor(1.0);
  // SG_MeaSystem* sg = new SG_MeaSystem(1.0);
  // SG_MotorIntegration *sg = new SG_MotorIntegration(1.0, REDBUTTONPIN);

  SG_QuadMotorInterface* sg = new SG_QuadMotorInterface(1.0);
  Sequencer *seq = new SequencerHW(sg);
  seq->start();

  std::cout << "5 seconds to enable motor interface." << std::endl;
  sleep(5);
  sg->setFL(-0.5);
  sg->setFR(-0.25);
  sg->setBL(0.25);
  sg->setBR(0.5);
  sg->enable();
  std::cout << "Enabled, we have lift of." << std::endl;


  // xTaskCreate(traceConsumer,
  //             "traceConsumer",
  //             1024, seq->getTracer(), 0, NULL);

  // sleep(2);
  // Serial.print("Traceables: ");
  // Serial.println(seq->getTracer()->getTraceNames().c_str());

  // sleep(3);
  // // seq->getTracer()->setBufferSize(1);
  // seq->getTracer()->startTracing();
  // sleep(3);
  // seq->getTracer()->stopTracing();

  while (1)
    ;
}

void waitUntilStarted(uint8_t pin)
{
  while (digitalRead(REDBUTTONPIN))
    ;
}

/* Task to be created. */
// void traceConsumer(void *obj)
// {
//   Serial.println("traceConsumer started");
//   Tracer *tracer = (Tracer *)obj;
//   while (1)
//   {
//     auto r = tracer->popTrace(portMAX_DELAY);
//     std::for_each(r.begin(), r.end(),
//                   [](double r)
//                   {
//                     Serial.print(r);
//                     Serial.println(' ');
//                   });
//     Serial.println();
//   }
// }

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Loop.");
  sleep(10);
}