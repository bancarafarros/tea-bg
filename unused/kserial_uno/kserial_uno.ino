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
//  baca permintaan dari nodemcu
  String minta = "";
  
  while(Serial.available() > 0) {
    minta += char(Serial.read());
  }

//buang spasi data yang diterima
  minta.trim();

//  kondisi kirim data atau tidak
  if (minta == "YA") {
    kirimData();
  }

//kosongkan variabel minta
  minta = "";
  delay(1000);
}

void kirimData() {
  Serial.println("bismillah");
//  baca nilai sensor
  aer = analogRead(A1);
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.println("AER = ");
  Serial.println(aer);
  Serial.print("Suhu = ");
  Serial.println(temperature);
  Serial.print("Kelembababan = ");
  Serial.println(humidity);
  delay(1000);
  String dataKirim = String(aer) + "#" + String(temperature) + "#" + String(humidity);
  Serial.println(dataKirim);
}
