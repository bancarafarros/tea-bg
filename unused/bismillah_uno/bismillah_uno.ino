//define library dht dan pin
#include <DHT.h>
#define DHT_PIN 7
#define DHTTYPE DHT11

//penampung nilai dht
DHT dht(DHT_PIN, DHTTYPE);
float humidity, temperature;

////penampung nilai ldr
int aer;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  //  baca nilai sensor
  aer = analogRead(A1);
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

//  Serial.print("Aer = ");
//  Serial.println(aer);
//  Serial.print("Suhu = ");
//  Serial.println(temperature);
//  Serial.print("Kelembababan = ");
//  Serial.println(humidity);
//  delay(1000);
  
  String dataKirim = String(aer) + "#" + String(temperature) + "#" + String(humidity);
  
  if(Serial.available() > 0) {
    Serial.println(dataKirim);
  }
  
  delay(3000);
}
