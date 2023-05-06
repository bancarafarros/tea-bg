//penampung nilai ketinggian air
int analogPin = A1;
int sensorVal;

//ds3231
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;

//dht11
#include <DHT.h>
DHT dht(7, DHT11); //Pin, Jenis DHT

void setup() {
  Serial.begin(9600);

//  dht11
  dht.begin();

//  ds3231
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
  }

  //Atur Waktu
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
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
//  water level
  sensorVal = analogRead(analogPin);
  Serial.print("Ketinggian Air = ");
  Serial.println(sensorVal);
  delay(1000);

//  dht11
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();

  Serial.print("kelembaban: ");
  Serial.print(kelembaban);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(suhu);
  
//  ds3231
  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;

  Serial.println(String() + hari + ", " + tanggal + "-" + bulan + "-" + tahun);
  Serial.println(String() + jam + ":" + menit + ":" + detik);
  Serial.println();
  delay(1000);

  String dataKirim = String(sensorVal) + "#" + String(suhu) + "#" + String(kelembaban) + "#" + String(hari) + "#" + String(tanggal) + "#" + String(bulan) + "#" + String(tahun) + "#" + String(jam) + "#" + String(menit) + "#" + String(detik);
  Serial.println(dataKirim);
}
