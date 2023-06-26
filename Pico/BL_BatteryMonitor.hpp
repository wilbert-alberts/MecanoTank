//
// BL_BatteryMonitor -- guard battery voltage
//
// 23 May 2023 - benslag
//
// The battery voltage multiplied by the PWM determines
// the speed at which a motor will run.
// By multiplying with the BatFactor the motor speed is compensated
// for varying battery voltages.
// compensatedPWM = nonCompensatedPWM * batFactor;



#ifndef __BatteryMonitor_H__
#define __BatteryMonitor_H__

#include "BL.hpp"

class BatteryMonitor: public Block {
  public:
   BatteryMonitor (const std::string& bn, float _servoFreq);
   ~BatteryMonitor ();
   virtual void calculate(int64_t counter);


   float *getBatFactor ();
   void  sample ();
   float avgVolts ();

  private:
   bool   batteryOK ();
   static int   avgSamples;
   static int   nSamplesA;
   static int   nSamplesB;
   static float sumA;
   static float sumB;
   static bool  inited;
   static float batFactor;
};
#endif
