#include "BMBot.h"
#include "ServoTimer2.h"
#include "IRremote.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel rgbled(15,RGB_PIN);
ServoTimer2 sv;
IRrecv irrecv;
decode_results results;

BMBot::BMBot(){
  	irEnabled = false;
	rgbled.begin();
	pinMode(M1_DIR_PIN,OUTPUT);
	pinMode(M2_DIR_PIN,OUTPUT);
}

void BMBot::begin(void){

}

int BMBot::lightSensor(void){
  
	return analogRead(LIGHTSENSOR_PIN);
}

int BMBot::audioSensor(void){
	
    return analogRead(AUDIOSENSOR_PIN);
}

//int BMBot::infraRx(void){
//	int ret = -1;
//	if(!irEnabled){
//		irrecv.attach(INFRARX_PIN);
//		irrecv.enableIRIn();
//		irEnabled = true;
//	}
//	if (irrecv.decode(&results)) {
//      if (results.value != 0xffffffff) {
//        ret = results.value;
//      }
//      irrecv.resume(); // Receive the next value
//    }
//	return ret;
//}

int ret = -1;
int ret_f = -1;

int BMBot::infraRx(void){
	if(!irEnabled){
		irrecv.attach(INFRARX_PIN);
		irrecv.enableIRIn();
		irEnabled = true;
	}
	else delay(1);
	
	if (irrecv.decode(&results)) {
      if (results.value != 0xffffffff) {
        ret_f = results.value;
        ret = ret_f;
      }
      else
      {
		  ret = ret_f; 	
      }
      irrecv.resume(); // Receive the next value
    }
    else ret = -1;
    
	return ret;
}

void BMBot::rgbSet(int pix, int red, int green, int blue){
	if(pix==0){
		for(int i=0;i<16;i++){
			rgbled.setPixelColor(i, red, green, blue);
		}
	}else{
		rgbled.setPixelColor(pix-1, red, green, blue);
	}
	rgbled.show();
}

int BMBot::button(void){
	pinMode(BUTTON_PIN,INPUT);
	return digitalRead(BUTTON_PIN);
}

int BMBot::lineFollower(void){
	pinMode(LINEFOLLOW_LEFT_PIN,INPUT);
	pinMode(LINEFOLLOW_RIGHT_PIN,INPUT);
	int ret = digitalRead(LINEFOLLOW_LEFT_PIN);
	ret |= digitalRead(LINEFOLLOW_RIGHT_PIN)<<4;
    return ret;
}

void BMBot::buzzer(int hz, int duration){
	tone(BUZZER_PIN,hz,duration);
	
}

float BMBot::ultrasonicSensor(void){
	int duration;
	float distance;
	pinMode(SONIC_TRIG_PIN, OUTPUT);
	pinMode(SONIC_ECHO_PIN, INPUT);
	// Clears the trigPin
	digitalWrite(SONIC_TRIG_PIN, LOW);
	delayMicroseconds(2);
	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(SONIC_TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(SONIC_TRIG_PIN, LOW);
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(SONIC_ECHO_PIN, HIGH);
	// Calculating the distance
	distance= duration*0.034/2;
	return distance;
}

void BMBot::servo(int slot, int degree){
	if(slot==0){
		slot = PORT_A1;
	}else{
		slot = PORT_A2;
	}
	sv.attach(slot);
	sv.write(degree);
}

void BMBot::motor(int slot, int speed){
	if(slot==M1){
		analogWrite(M1_PWM_PIN,abs(speed));
		digitalWrite(M1_DIR_PIN,speed>=0?1:0);
	}else if(slot==M2){
        analogWrite(M2_PWM_PIN,abs(speed));
		digitalWrite(M2_DIR_PIN,speed>=0?1:0);
	}else if(slot==0){
		analogWrite(M2_PWM_PIN,abs(speed));
		digitalWrite(M2_DIR_PIN,speed>=0?0:1);
		analogWrite(M1_PWM_PIN,abs(speed));
		digitalWrite(M1_DIR_PIN,speed>=0?1:0);
	}
	
}

void BMBot::stop(void){
	analogWrite(M1_PWM_PIN,0);
	analogWrite(M2_PWM_PIN,0);
}

