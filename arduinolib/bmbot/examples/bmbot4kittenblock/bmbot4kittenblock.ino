#include <Wire.h>
#include <EEPROM.h>

#include "BMBot.h"

#define FIRMWARE "BMBot V1.0\r\n"

BMBot bmbot;

void echoVersion() {
  Serial.print("M0 ");
  Serial.print(FIRMWARE);
}

void doSoftReset() {
  asm volatile ("  jmp 0");
}

void doRgb(char * cmd){
  int pix, r, g, b;
  sscanf(cmd, "%d %d %d %d\n", &pix, &r, &g, &b);
  bmbot.rgbSet(pix,r,g,b);
}

void doBuzzer(char * cmd){
  int hz,t;
  sscanf(cmd,"%d %d\n",&hz,&t);
  bmbot.buzzer(hz, t);
}

void doServo(char * cmd){
  int slot,degree;
  sscanf(cmd,"%d %d\n",&slot,&degree);  
  bmbot.servo(slot, degree);
}

void doMotor(char * cmd){
  int slot, speed;
  sscanf(cmd,"%d %d\n",&slot,&speed);
  bmbot.motor(slot, speed);
}

void parseMcode(char * cmd) {
  int code;
  char * tmp;
  code = atoi(cmd);
  cmd = strtok_r(cmd, " ", &tmp);

  switch (code) {
    case 0:
      echoVersion();
      break;
    case 301: // light sensor A1
      Serial.print("M301 ");
      Serial.println(bmbot.lightSensor());
      break;
    case 302: // audio sensor A2
      Serial.print("M302 ");
      Serial.println(bmbot.audioSensor());
      break;
    case 303: // infra rx D10
      Serial.print("M303 ");
      Serial.println(bmbot.infraRx());
      break;
    case 304: // rgb D10
      doRgb(tmp);
      break;
    case 305: // button D11
      Serial.print("M305 ");
      Serial.println(bmbot.button());
      break;
    case 306: // line follow D11 D12
      Serial.print("M306 ");
      Serial.println(bmbot.lineFollower());
      break;
    case 307: // buzzer D11
      doBuzzer(tmp);
      break;
    case 308: // ultrasonic D11 D12
      Serial.print("M308 ");
      Serial.println(bmbot.ultrasonicSensor());
      break;
    case 309: // servo
      doServo(tmp);
      break;
    case 310: // motor
      doMotor(tmp);
      break;
    case 999:
      doSoftReset();
      break;
  }

}

void parseCmd(char * cmd) {
  if (cmd[0] == 'G') { // gcode

  } else if (cmd[0] == 'M') { // mcode
    parseMcode(cmd + 1);
  }
  Serial.println("OK");
}

void setup(){
  Serial.begin(115200);
  echoVersion();
  bmbot.begin();
}

char buf[64];
int8_t bufindex;

void loop(){
  while (Serial.available()) {
    char c = Serial.read();
    buf[bufindex++] = c;
    if (c == '\n') {
      buf[bufindex] = '\0';
      parseCmd(buf);
      memset(buf, 0, 64);
      bufindex = 0;
    }
    if (bufindex >= 64) {
      bufindex = 0;
    }
  }
}

