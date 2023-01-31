#include <Arduino.h>

#include "Debugpin.hpp"

#include "Sequencer.hpp"
#include "SequencerSW.hpp"
#include "SequencerHW.hpp"

#include "SG_MeaSystem.hpp"
#include "SG_RawSensor.hpp"
#include "SG_MotorIntegration.hpp"

#include "Tracer.hpp"

void traceConsumer(void *obj);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(DEBUGPIN, OUTPUT);

  SG_RawSensor *sg = new SG_RawSensor(1.0);
  // SG_MeaSystem* sg = new SG_MeaSystem(1.0);
  // SG_MotorIntegration* sg = new SG_MotorIntegration(1.0);
  Sequencer *seq = new SequencerHW(sg);
  seq->start();

  xTaskCreate(traceConsumer,
              "traceConsumer",
              1024, seq->getTracer(), 0, NULL);

  sleep(2);
  Serial.print("Traceables: ");
  Serial.println(seq->getTracer()->getTraceNames().c_str());

  sleep(3);
  // seq->getTracer()->setBufferSize(1);
  seq->getTracer()->startTracing();
  sleep(3);
  seq->getTracer()->stopTracing();

  while (1)
    ;
}

/* Task to be created. */
void traceConsumer(void *obj)
{
  Serial.println("traceConsumer started");
  Tracer *tracer = (Tracer *)obj;
  while (1)
  {
    auto r = tracer->popTrace(portMAX_DELAY);
    std::for_each(r.begin(), r.end(),
                  [](double r)
                  {
                    Serial.print(r);
                    Serial.println(' ');
                  });
    Serial.println();
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Loop.");
  sleep(10);
}