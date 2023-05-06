////penampung nilai ketinggian air
int analogPin = A1;
int sensorVal;

//ds3231
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;
//float suhu;

//servo
#include <Servo.h>
Servo servoku;

//dht11
#include <DHT.h>
DHT dht(7, DHT11); //Pin, Jenis DHT

//relay
const int relay1 = 10; //pin2
const int relay2 = 11; //pin3
const int relay3 = 12; //pin2
const int relay4 = 13; //pin3

int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati

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

//  servo
servoku.attach(3);

//relay
pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, relayOFF);
  digitalWrite(relay2, relayOFF);
  digitalWrite(relay3, relayOFF);
  digitalWrite(relay4, relayOFF);
}

void loop() {
//  water level
  sensorVal = analogRead(analogPin);
  Serial.print("Ketinggian Air = ");
  Serial.println(sensorVal);
  delay(1000);

//  ds3231
DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;
//  suhu    = rtc.getTemperature();

  Serial.println(String() + hari + ", " + tanggal + "-" + bulan + "-" + tahun);
  Serial.println(String() + jam + ":" + menit + ":" + detik);
//  Serial.println(String() + "Suhu: " + suhu + " C");
  Serial.println();

  delay(1000);

//  servo
servoku.write(10);
  delay(1000);
  servoku.write(100);
  delay(1000);

//  dht11
float kelembaban = dht.readHumidity();
 float suhu = dht.readTemperature();

 Serial.print("kelembaban: ");
 Serial.print(kelembaban);
 Serial.print(" ");
 Serial.print("suhu: ");
 Serial.println(suhu);

//relay1
  digitalWrite(relay1, relayON);
  delay(1000);
  digitalWrite(relay1, relayOFF);
  delay(1000);
  
  //relay2
  digitalWrite(relay2, relayON);
  delay(1000);
  digitalWrite(relay2, relayOFF);
  delay(1000);

  //relay3
  digitalWrite(relay3, relayON);
  delay(1000);
  digitalWrite(relay3, relayOFF);
  delay(1000);
  
  //relay4
  digitalWrite(relay4, relayON);
  delay(1000);
  digitalWrite(relay4, relayOFF);
  delay(1000);
}
