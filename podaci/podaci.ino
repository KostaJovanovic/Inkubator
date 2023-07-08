#include <dht.h>
#define dht_pin 4// DHT11 data pin connected to Arduino
#define SERIAL_PIN  Serial

// Variables to store elapsed time
unsigned long startTime;
unsigned long elapsedTime;

dht DHT;

void setup() {
  Serial.begin(9600);
  Serial.println("test test 123123123\n");
  delay(1000);//Wait before accessing Sensor
  startTime = millis();
}

void loop() {
  DHT.read11(dht_pin);
  int current_temp = DHT.temperature;
  int current_humi = DHT.humidity;

  // Calculate elapsed time
  elapsedTime = millis() - startTime;

  // Convert milliseconds to hours, minutes, and seconds
  unsigned long seconds = (elapsedTime / 1000) % 60;
  unsigned long minutes = (elapsedTime / (1000 * 60)) % 60;
  unsigned long hours = (elapsedTime / (1000 * 60 * 60));

  Serial.print("Vlažnost : ");
  Serial.print(current_humi);
  Serial.print("%  | ");
  Serial.print("Temperatura : ");
  Serial.print(current_temp);
  Serial.print("°C | ");
  
  // Print elapsed time
  SERIAL_PIN.print("Elapsed Time: ");
  SERIAL_PIN.print(hours);
  SERIAL_PIN.print("h ");
  SERIAL_PIN.print(minutes);
  SERIAL_PIN.print("m ");
  SERIAL_PIN.print(seconds);
  SERIAL_PIN.println("s");
  
  Serial.println(" ");
  delay(1000);
}