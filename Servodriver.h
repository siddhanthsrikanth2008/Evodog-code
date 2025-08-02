#ifndef _SERVO_DRIVER_H_
#define _SERVO_DRIVER_H_

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 544 // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH 2400 // the longest pulse sent to a servo

//https://forums.adafruit.com/viewtopic.php?f=31&t=96423
//CaIc PW Driver parameters
//50 pulses per second
#define SERVO_FREQ 50
#define NUM_INCREMENTS 4096
#define ONE_SEC_US 1000000 //six zeros
#define PWM_PERIOD ONE_SEC_US / SERVO_FREQ
#define US_PER_INCR ((float)PWM_PERIOD / (float)NUM_INCREMENTS)
#define SERVO_MIN (MIN_PULSE_WIDTH / US_PER_INCR)
#define SERVO_MAX (MAX_PULSE_WIDTH / US_PER_INCR)

float mapf( float x,
            float in_min,
            float in_max,
            float out_min,
            float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

class ServoDriver
{
  public:
  void gotoPos( int servonum, float deg )
  {
    int pulselen = mapf( deg, 0, 180, SERVO_MIN,SERVO_MAX);
    pwm.setPWM(servonum, 0, pulselen);
  }
  void stop( int servonum )
  {
    pwm.setPWM(servonum, 0, 0);  
  }
 
  void setup()
  {
    pwm.begin();
    Wire.setClock(400000L);//five zeros
      //pwm.setOscillatorFrequency(27000000);//six zeros
    pwm.setPWMFreq(SERVO_FREQ); //Analog Servos run at ~50Hz
    delay(10);
  }
 
};
//---------------------------
#endif //_SERVO_DRIVER_H
