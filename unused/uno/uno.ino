//dht11
#include <DHT.h>
DHT dht(7, DHT11); //Pin, Jenis DHT

void setup() {
  Serial.begin(9600);

//  dht11
  dht.begin();

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
//  dht11
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();

  Serial.print("kelembaban: ");
  Serial.print(kelembaban);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(suhu);
  
  String dataKirim = String(suhu) + "#" + String(kelembaban);
  Serial.println(dataKirim);
}