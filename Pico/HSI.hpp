#ifndef __HSI_HPP__
#define __HSI_HPP__

// --------------- WHEELS ----------------

#define SERVO_FREQUENCY         (100.0)
#define SERVO_PERIOD            (1/SERVO_FREQUENCY)

#define INCREMENTS_PER_METER    (13560.0)
#define METERS_PER_INCREMENT    (1/INCREMENTS_PER_METER)

#define PIN_OUT_FRONT_LEFT_DIR  19
#define PIN_OUT_FRONT_LEFT_PWM  18
#define PIN_IN_FRONT_LEFT_A     13
#define PIN_IN_FRONT_LEFT_B     12

#define PIN_OUT_FRONT_RIGHT_DIR 21
#define PIN_OUT_FRONT_RIGHT_PWM 20
#define PIN_IN_FRONT_RIGHT_A    9
#define PIN_IN_FRONT_RIGHT_B    8

#define PIN_OUT_BACK_LEFT_DIR   17
#define PIN_OUT_BACK_LEFT_PWM   16
#define PIN_IN_BACK_LEFT_A      14
#define PIN_IN_BACK_LEFT_B      15

#define PIN_OUT_BACK_RIGHT_DIR  26
#define PIN_OUT_BACK_RIGHT_PWM  22
#define PIN_IN_BACK_RIGHT_A     11
#define PIN_IN_BACK_RIGHT_B     10

#define PIN_OUT_CS_CAMERA_LEFT  27
#define PIN_OUT_CS_CAMERA_RIGHT 5

#define PIN_OUT_DEBUG           7 // red led and scope out
#define PIN_IN_START            6 // needs pullup

// Battery Voltage ADC
// #include "hardware/adc.h"
//     adc_gpio_init     (PIN_IN_BAT_VOLT);
//     adc_select_input  (BAT_VOLT_ADC_INPUT);
//     float batVolts = BATTERY_VOLT_PER_BIT * adc_read ();


#define PIN_IN_BAT_VOLT            28
#define BAT_VOLT_ADC_INPUT         2
#define BATTERY_VOLT_PER_BIT      (12.67f / (1<<12)) 
#define BATTERY_MIN_VOLTS         (9.0)
#define BATTERY_NOMINAL_VOLTS     (11.0)
#define BATTERY_DROP_COMPENSATION (-0.4)

#define BAT_AVG_TIME              (0.1) // Seconds

#endif
