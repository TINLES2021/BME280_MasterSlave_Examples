#include <Wire.h>

#define MY_ADDR 0x90

void setup()
{
  Wire.begin(MY_ADDR);         
  Wire.onReceive(receiveBME280Data); 
  Serial.begin(115200);          
}

// function to convert an array of 4 bytes to a single float
float byteArrToFloat(byte b[]){
  float f;
  for(int i = 0; i < 4; i++){
  }
  f = *(float *)b;
  return f;
}

void loop()
{
}

// function that executes whenever data is received from master
void receiveBME280Data()
{
  byte heightDiff[4];
  while(Wire.available())
  {
    Serial.println("hi");
    for(int i = 0; i < sizeof(float); i++){
      heightDiff[i] = Wire.read();
    }
    float altitude = byteArrToFloat(heightDiff);
    Serial.println(altitude);
  }
}
