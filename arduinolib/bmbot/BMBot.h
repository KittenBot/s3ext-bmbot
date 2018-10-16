#ifndef BMBOT_H
#define BMBOT_H

#include <Arduino.h>

#define PORT_A1 3
#define PORT_A2 9

#define M1 1
#define M2 2

#define LIGHTSENSOR_PIN A1
#define AUDIOSENSOR_PIN A2
#define INFRARX_PIN 10
#define RGB_PIN 10
#define BUTTON_PIN 11
#define LINEFOLLOW_LEFT_PIN 11
#define LINEFOLLOW_RIGHT_PIN 12
#define BUZZER_PIN 11
#define SONIC_TRIG_PIN 12
#define SONIC_ECHO_PIN 11
#define M1_DIR_PIN 7
#define M1_PWM_PIN 6
#define M2_DIR_PIN 4
#define M2_PWM_PIN 5


class BMBot 
{
public:
  BMBot();
  void begin();
  int lightSensor(void);
  int audioSensor(void);
  int infraRx(void);
  void rgbSet(int pixel, int red, int green, int blue);
  int button(void);
  int lineFollower(void);
  void buzzer(int hz, int duration);
  float ultrasonicSensor(void);
  
  void servo(int slot, int degree);
  void motor(int slot, int speed);
  void stop();
  
  bool irEnabled;
	
	
};


#endif //
