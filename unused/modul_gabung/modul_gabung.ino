//KOMPONEN MODUL PAKAN
//rtc
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;

//servo
#include <Servo.h>
Servo servoku;
//KOMPONEN MODUL PAKAN

//KOMPONEN MODUL MINUM
//sensor ketinggian air
//penampung nilai ketinggian air
int analogPin = A1;
int sensorVal;
//KOMPONEN MODUL MINUM

//KOMPONEN MODUL MINUM
//relay
const int kipas1 = 10; //relay1 suhu KOMPONEN MODUL SUHU
const int kipas2 = 11; //relay2 kelembaban KOMPONEN MODUL KELEMBABAN
const int pompa = 12; //relay3 KOMPONEN MODUL MINUM
const int lampu = 13; //relay4 KOMPONEN MODUL SUHU

//on off relay
int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati

void setup () {
  Serial.begin(9600);

  // SETUP MODUL PAKAN
  servoku.attach(3);

  if (! rtc.begin()) {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
  }

  //Atur Waktu
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  // SETUP MODUL PAKAN

  //  setup relay
  pinMode(kipas1, OUTPUT);
  pinMode(kipas2, OUTPUT);
  pinMode(pompa, OUTPUT);
  pinMode(lampu, OUTPUT);
  digitalWrite(kipas1, relayOFF);
  digitalWrite(kipas2, relayOFF);
  digitalWrite(pompa, relayOFF);
  digitalWrite(lampu, relayOFF);
}

void loop () {
  // LOOP MODUL PAKAN
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

   if(jam == 14 && menit == 28 && detik == 10) {
    modulPakan(); 
  }

  if(jam == 14 && menit == 28 && detik == 30) {
    modulPakan(); 
  }

  if(jam == 14 && menit == 28 && detik == 50) {
    modulPakan(); 
  }

//  if(jam == 7 && menit == 0 && detik == 0) {
//    modulPakan(); 
//  }
//
//  if(jam == 12 && menit == 0 && detik == 0) {
//    modulPakan(); 
//  }
//
//  if(jam == 17 && menit == 0 && detik == 0) {
//    modulPakan(); 
//  }
  // LOOP MODUL PAKAN

  // LOOP MODUL MINUM
  sensorVal = analogRead(analogPin);

  if (sensorVal <= 480) {
    Serial.println("Ketinggian air: 0mm");
  
  } else if (sensorVal > 480 && sensorVal <= 530) {
    Serial.println("Ketinggian air: 0mm - 5mm");
  
  } else if (sensorVal > 530 && sensorVal <= 615) {
    Serial.println("Ketinggian air: 5mm - 10mm");
  
  } else if (sensorVal > 615 && sensorVal <= 660) {
    Serial.println("Ketinggian air: 10mm - 15mm");
  
  } else if (sensorVal > 660 && sensorVal <= 680) {
    Serial.println("Ketinggian air: 15mm - 20mm");
  
  } else if (sensorVal > 680 && sensorVal <= 690) {
    Serial.println("Ketinggian air: 20mm - 25mm");
  
  } else if (sensorVal > 690 && sensorVal <= 700) {
    Serial.println("Ketinggian air: 25mm - 30mm");
  
  } else if (sensorVal > 700 && sensorVal <= 705) {
    Serial.println("Ketinggian air: 30mm - 35mm");
  
  } else if (sensorVal > 705) {
    Serial.println("Ketinggian air: 35mm - 40mm");
  }

//  if (sensorVal < 530) {
//    modulIsiBakMinum();
//  
//  } else if (sensorVal > 705) {
//    matikanModulIsiBakMinum();
//  }

  if (sensorVal < 100) {
    modulIsiBakMinum();
  
  } else if (sensorVal > 300) {
    matikanModulIsiBakMinum();
  }
  // LOOP MODUL MINUM
}

void modulPakan() {
  // proses perputaran pakan secara halus
  for (int posisi = 0; posisi <= 180; posisi++) {
    // set posisi servo berdasarkan variabel posisi
    servoku.write(posisi);
    delay(10);
  }

  // proses perputaran tempat pakan kembali ke posisi awal
  for (int posisi = 180; posisi >= 0; posisi--) {
    servoku.write(posisi);
    delay(10);
  }
}

void modulIsiBakMinum() {
  //relay3
  digitalWrite(pompa, relayON);
}

void matikanModulIsiBakMinum() {
  //relay3
  digitalWrite(pompa, relayOFF);
}
