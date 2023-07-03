#ifndef __SERVO_HPP__
#define __SERVO_HPP__

//
// servo settings for wheel servos
// The settings are generic for all wheels

// speed range = -1..1 m/s for each motor.
// A motor interface converts the range -1..1 into a speed of -1..1 m/s

#define SP_SPEED    (0.5)       // setpoint speed m/s

#define KFV         (1.0)       // per m/s
#define FV_LOW      (-1.0)      // low limit
#define FV_HIGH     (1.0)       // high limit

#define KD          (10.0)       // per m/s
#define D_LOW       (-1.0)       // low limit
#define D_HIGH      (1.0)       // high limit

#define KP          (50.0)      // per m
#define P_LOW       (-1.0)      // low limit
#define P_HIGH      (1.0)       // high limit

#define KI          (0.1)       // per m.s
#define I_LOW       (-0.9)       // low limit
#define I_HIGH      (0.9)       // high limit

#define PID_LOW     (-1)
#define PID_HIGH    (1)

#endif // __SERVO_HPP__