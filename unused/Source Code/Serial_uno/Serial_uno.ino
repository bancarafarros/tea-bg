#include <DHT.h>
#include <SoftwareSerial.h>
SoftwareSerial link(2, 3); // Rx, Tx

//konfigurasi untuk sensor DHT
#define DHT_PIN 8
#define DHTTYPE DHT11

//buat variabel untuk sensor DHT
DHT dht(DHT_PIN, DHTTYPE);

//variabel untuk menampung nilai sensor
int ldr;
float humidity, temperature;

void setup() {
  Serial.begin(9600);
  //aktifkan sensor DHT
  dht.begin();
}

void loop() {
  //baca peramintaan dari NodeMCU
  String minta = "";
  while(link.available()>0)
  {
    minta += char(Serial.read());
  }

  //buang spasi data yang diterima
  minta.trim();
  //uji variabel minta
  if(minta=="YA")
  {
    //kirim datanya
    kirimdata();
  }

  //kosongkan variabel minta
  minta="";
  delay(1000);
}

void kirimdata()
{
  //baca nilai sensor LDR
  ldr = analogRead(0);
  //baca temperature dan humidity
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  //sediakan variabel penampung data yang akan dikirim
  String datakirim = String(ldr) + "#" + String(temperature) + "#" + String(humidity);
  //kirim data
  Serial.println(datakirim);
}
