#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>

#define RDM_SEALEVELPRESSURE_HPA (1024) // changes daily, keep updating value
#define BME280_ADDR 0x76
#define SLAVE_ADDR 0x90

Adafruit_BME280 bme280;

unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  Serial.println("Master BME280 communication");
  Wire.begin();
  unsigned status;
  status = bme280.begin(BME280_ADDR);
}

// function to calculate absolute difference between altitudes
float calcDifference(float currAltitude){
  float diffConstant = -5.42;             // constant value, for variable - add argument to func calcDifference
  return abs(currAltitude - diffConstant);
}

// transmit BME280 height difference data over I2C line to slave at addr SLAVE_ADDR
void transmitBME280Data(float currAltitude){
  Wire.beginTransmission(SLAVE_ADDR);
  float altitude = calcDifference(currAltitude);
  Serial.println();
  Wire.write((byte*)&altitude, sizeof(altitude));
  Wire.endTransmission();
}

void loop() {
  delayTime = 1000;
  if(bme280.readAltitude(RDM_SEALEVELPRESSURE_HPA)){
      float altitude = bme280.readAltitude(RDM_SEALEVELPRESSURE_HPA);
      Serial.println(bme280.readAltitude(RDM_SEALEVELPRESSURE_HPA));
      transmitBME280Data(altitude);
    delay(delayTime);
  }
}
