//rtc
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;

//servo
#include <Servo.h>
Servo servoku;

void setup() {
    Serial.begin(9600);

    servoku.attach(3);

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
    DateTime now = rtc.now();
    hari    = dataHari[now.dayOfTheWeek()];
    tanggal = now.day(), DEC;
    bulan   = now.month(), DEC;
    tahun   = now.year(), DEC;
    jam     = now.hour(), DEC;
    menit   = now.minute(), DEC;
    detik   = now.second(), DEC;

    //  Serial.println(String() + hari + ", " + tanggal + "-" + bulan + "-" + tahun);
    //  Serial.println(String() + jam + ":" + menit + ":" + detik);
    //  Serial.println();

    //  modulPakan();

    if(jam == 13 && menit == 49 && detik == 10) {
        modulPakan(); 
    }

    if(jam == 13 && menit == 49 && detik == 30) {
        modulPakan(); 
    }

    if(jam == 13 && menit == 49 && detik == 50) {
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