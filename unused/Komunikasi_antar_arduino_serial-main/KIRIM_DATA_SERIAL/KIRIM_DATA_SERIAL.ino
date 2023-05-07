//Transmitter Code
#include <SoftwareSerial.h>
SoftwareSerial link(2, 3); // Rx, Tx

#include <DHT.h>

//konfigurasi untuk sensor DHT
#define DHT_PIN 8
#define DHTTYPE DHT11

//buat variabel untuk sensor DHT
DHT dht(DHT_PIN, DHTTYPE);

//variabel untuk menampung nilai sensor
int ldr;
float humidity, temperature;

//int text = 333;
//int isikanData1 = 999;
//int isikanData2 = 949;
 
void setup() {
    link.begin(9600);
    Serial.begin(9600);
    dht.begin();
}
 
void loop() {
  //baca nilai sensor LDR
  ldr = analogRead(0);
  //baca temperature dan humidity
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  //sediakan variabel penampung data yang akan dikirim
  String datakirim = String(ldr) + "#" + String(temperature) + "#" + String(humidity);
  //kirim data
  link.println(datakirim);
  
//  link.print("*");
//  link.print(isikanData1);
//  link.print(",");
//  link.print(isikanData2);
//  link.println("#");
  delay(1000);
}
