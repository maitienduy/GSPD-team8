int ir_sensor = A0; //conncect D-sensor to Analog pin A0
void setup() {
//initialize serial communications at 9600 bps
Serial.begin(9600);
}
     
void loop() {
int sensor_value = analogRead(ir_sensor);  //read the sensor value
int distance_cm = pow(3027.4/sensor_value, 1.2134); //convert readings to distance(cm)
Serial.println(distance_cm); //print the sensor value
delay(500); //delay 500ms (0.5 second)
}

