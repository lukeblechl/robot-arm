#include <Wire.h>
#include <Servo.h>
#include <L3G.h>

Servo servoX;
Servo servoY;
Servo servoZ;
L3G gyro;

int   delayTime  = 2;
int   lastX      = 0;
int   thisX      = 0;
int   lastY      = 0;
int   thisY      = 0;
int   lastZ      = 0;
int   thisZ      = 0;
float servoPosX  = 90;
float servoPosY  = 90;
float servoPosZ  = 120;
int   sX         = 90;
int   sY         = 90;
int   sZ         = 90;
float stepsX     = .8;
float stepsY     = .2;
float stepsZ     = .9;
int   maxPosX    = 180 - stepsX;
int   maxPosY    = 180 - stepsY;
int   maxPosZ    = 180;
int   minPosX    = stepsX;
int   minPosY    = stepsY;
int   minPosZ    = 10;
int   threshhold = 500;

void setup() {
  //Serial.begin(19200);
  Wire.begin();

  if (!gyro.init())
  {
    while (1);
  }

  gyro.enableDefault();
  
  delay(1500);
  
  servoX.attach(9);
  // servoX.write(90);
  delay(200);
  
  servoY.attach(10);
  // servoY.write(90);
  delay(200);
  
  servoZ.attach(11);
  // servoY.write(90);
  delay(200);  
  
}

void loop() {
  gyro.read();
  thisX = (int)gyro.g.x;
  thisY = (int)gyro.g.y;
  thisZ = (int)gyro.g.z;

  if (thisX > threshhold) {
    if(servoPosX < maxPosX) { 
      servoPosX = servoPosX + stepsX;
    }
  } else if (thisX < -(threshhold)) {
    if(servoPosX > minPosX) { 
      servoPosX = servoPosX - stepsX;
    }
  }
  
  if (thisY > threshhold) {
    if(servoPosY > minPosY) { 
      servoPosY = servoPosY - stepsY;
    }    
  } else if (thisY < -(threshhold)) {
    if(servoPosY < maxPosY) { 
      servoPosY = servoPosY + stepsY;
    }
  }
  
  if (thisZ > threshhold) {
    if(servoPosZ < maxPosZ) { 
      servoPosZ = servoPosZ + stepsZ;
    }
  } else if (thisZ < -(threshhold)) {
    if(servoPosZ > minPosZ) { 
      servoPosZ = servoPosZ - stepsZ;
    }
  }    

  sX = (int)servoPosX;
  sY = (int)servoPosY;
  sZ = (int)servoPosZ;
  
  servoX.write(sX);
  delay(delayTime);
  
  servoY.write(sY);
  delay(delayTime);
  
  servoZ.write(sZ);
  delay(delayTime);  
}
