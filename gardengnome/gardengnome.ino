#include <SimpleDHT.h>
#include <I2CSoilMoistureSensor.h> 
#include <Wire.h> 
I2CSoilMoistureSensor sensor(0x60); 
// for DHT22, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT22 = 2;
int LDRpin = A0;
SimpleDHT22 dht22(pinDHT22);
int LDRValue = 0;     // result of reading the analog pin

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  sensor.begin(); // reset sensor 
  delay(1000); // give some time to boot up 
//  Serial.print("I2C Soil Moisture Sensor Address: "); 
//  Serial.println(sensor.getAddress(),HEX); 
//  Serial.print("Sensor Firmware version: "); 
//  Serial.println(sensor.getVersion(),HEX); 
//  Serial.println(); 

}

void loop() {
  // start working...
//  Serial.println("=================================");
//  Serial.println("Sample DHT22...");
  
  // read without samples.
  // @remark We use read2 to get a float data, such as 10.1*C
  //    if user doesn't care about the accurate data, use read to get a byte data, such as 10*C.
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(2000);
    return;
  }
  LDRValue = analogRead(LDRpin); // read the value from the LDR
  //Serial.print("{ timestamp: time");
  Serial.print("{temp:");
  Serial.print((float)temperature); Serial.print(", humidity: ");
  Serial.print((float)humidity); Serial.print(", soilmoisture: ");
  Serial.print(sensor.getCapacitance()); //read capacitance register 
  Serial.print(", lightsensor:"); 
  Serial.print(LDRValue);Serial.print("}");
  Serial.println("");// print the value to the serial port
   
  delay(300000);
}
