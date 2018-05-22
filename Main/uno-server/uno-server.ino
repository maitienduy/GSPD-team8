#include "DHT.h"
#include <ctype.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_SI1145.h"

Adafruit_SI1145 uv = Adafruit_SI1145(); //connect the UV sensor SCL to A5, SDA to A4
#define DHTPIN 7     // what digital pin we're connected DHT22 to
#define DHTTYPE DHT22   //define the type of DHT sensor
#define BUFFER_SIZE 64
DHT dht(DHTPIN, DHTTYPE);
/*Buffer setup*/
char inData[BUFFER_SIZE];
/*bluetooth setup*/
SoftwareSerial serial_connection(10, 11);//From bluetoothmodule, connect TX to 10 and RX to 11 in arduino

void setup() {
  Serial.begin(9600);
  serial_connection.begin(9600);//Initialize communications with the bluetooth module
  serial_connection.println("Ready!!!");//Send something to just starting the  comms. Can not be seen.
  Serial.println("Started");//Tell the serial monitor that the sketch has started.
  dht.begin();
  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }
}

void loop() {
  // delay for preparing the sensor
 delay(5000);
 /*sending*/
 serial_connection.print("{ humiditi: ");/*sending humidity data*/
 serial_connection.println(hum());
 serial_connection.print("temprature: ");/*sending temp data*/
 serial_connection.println(temp());
  serial_connection.print("UVindex: ");/*sending UV data*/
 serial_connection.println(getuv());
 serial_connection.println("}");
 /*receiving*/
 int i=0;
 byte byte_count=serial_connection.available();//This gets the number of bytes that were sent by the python script
    for(i=0;i<byte_count;i++)//Handle the number of incoming bytes
    {
    inData[i]=serial_connection.read();
    }
    byte_count = 0;
    Serial.println(inData);
    //Print to the monitor what was detected
}
/* read DHT22 sensor */
float hum(){
  float h = dht.readHumidity();
  if (isnan(h)) {
  Serial.println("Failed to read from DHT sensor!");
    }
  return h;
}
float temp(){
  float t = dht.readTemperature();
  if (isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
    }
  return t;
}
/* read UV sensor */
float getuv(){
 // Serial.print("Vis: "); Serial.println(uv.readVisible());
 // Serial.print("IR: "); Serial.println(uv.readIR()); 
  float UVindex = uv.readUV();
  // the index is multiplied by 100 so to get the
  // integer index, divide by 100!
  UVindex /= 100.0;  
  Serial.print("UV: ");  Serial.println(UVindex);
  return UVindex;
}

