#include <SimpleDHT.h>
 
// for DHT22, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT22 = 2;
int LDRpin = A0;
int moisturePin =A1;
int bluePin = 13;
int greenPin = 12;
int redPin = 11;
SimpleDHT22 dht22(pinDHT22);
int LDRValue = 0;     // result of reading the analog pin
int moistureValue = 0;
const int AirValue = 575;
const int WaterValue = 340;// reference readings for dry air, and glass of water
const int lowWater = 496;
const int highWater = 418;
void setup() {
  Serial.begin(9600);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
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
  LDRValue = analogRead(LDRpin);// read the value from the LDR
  moistureValue = analogRead(moisturePin);
  //Serial.print("{ timestamp: time");
  Serial.print("{temp:");
  Serial.print((float)temperature); Serial.print(", humidity: ");
  Serial.print((float)humidity); Serial.print(", soilmoisture: ");
  Serial.print(moistureValue); //read capacitance register 
  Serial.print(", lightsensor:"); 
  Serial.print(LDRValue);Serial.print("}");
  Serial.println("");// print the value to the serial port
  if(moistureValue > lowWater){
      digitalWrite(redPin, HIGH);
      digitalWrite(bluePin,LOW);
      digitalWrite(greenPin,LOW);
      
   }
   if(moistureValue < highWater){
      digitalWrite(redPin, LOW);
      digitalWrite(bluePin,HIGH);
      digitalWrite(greenPin,LOW);
   }
   if(moistureValue > highWater && moistureValue < lowWater){
      digitalWrite(redPin, LOW);
      digitalWrite(bluePin,LOW);
      digitalWrite(greenPin,HIGH);
   } 
  delay(3000);
}
