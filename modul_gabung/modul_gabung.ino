//rtc
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;
//rtc

//servo
#include <Servo.h>
Servo servoku;
//servo

//sensor ketinggian air
int analogPin = A1;
int ketinggianAir;
//sensor ketinggian air

// relay
const int kipas1 = 10; //relay1 suhu
const int kipas2 = 11; //relay2 kelembaban
const int pompa = 12; //relay3
const int lampu = 13; //relay4

//on off relay
int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati
// relay

void setup() {
    Serial.begin(9600);

    // servo
    servoku.attach(3);

    // rtc ds3231
    if (! rtc.begin()) {
        Serial.println("RTC Tidak Ditemukan");
        Serial.flush();
        abort();
    }

    //Atur Waktu
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    // rtc ds3231

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

void loop() {
    // BACA SUHU DAN KELEMBABAN
    
    // BACA SUHU DAN KELEMBABAN

    // BACA KETINGGIAN AIR
    ketinggianAir = analogRead(analogPin);

    // KONDISI MODUL MINUM
    // kondisi coba2
    if (ketinggianAir < 100) {
        modulIsiBakMinum();

    } else if (ketinggianAir > 300) {
        matikanModulIsiBakMinum();
    }
    // KONDISI MODUL MINUM

    // BACA WAKTU
    DateTime now = rtc.now();
    hari    = dataHari[now.dayOfTheWeek()];
    tanggal = now.day(), DEC;
    bulan   = now.month(), DEC;
    tahun   = now.year(), DEC;
    jam     = now.hour(), DEC;
    menit   = now.minute(), DEC;
    detik   = now.second(), DEC;
    // BACA WAKTU

    // KONDISI MODUL PAKAN
    // kondisi coba2
    if(jam == 13 && menit == 49 && detik == 10) {
        modulPakan(); 
    }

    if(jam == 13 && menit == 49 && detik == 30) {
        modulPakan(); 
    }

    if(jam == 13 && menit == 49 && detik == 50) {
        modulPakan(); 
    }
    // KONDISI MODUL PAKAN

    // KONDISI MODUL MODE MALAM
    // kondisi coba2
    if (jam == 13 && menit == 0 && detik == 0) {
        matikanModulModeMalam();
    
    } else if (jam == 13 && menit == 2 && detik == 0) {
        modulModeMalam();
    }
    // KONDISI MODUL MODE MALAM
}

// MODUL MINUM
void modulIsiBakMinum() {
    // mengisi bak minum dengan menyala pompa air ketika bak minum hampir kosong
    //relay3
    digitalWrite(pompa, relayON);
    }

void matikanModulIsiBakMinum() {
    // mematikan pompa air ketika bak minum sudah hampir penuh
    //relay3
    digitalWrite(pompa, relayOFF);
}
// MODUL MINUM

// MODUL MONITORING SUHU DAN KELEMBABAN

// MODUL MONITORING SUHU DAN KELEMBABAN

// MODUL PAKAN
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
// MODUL PAKAN

// MODUL MODE MALAM
void modulModeMalam() {
    // menyalakan lampu kandang ketika waktu sudah memasuki malam hari
    //relay4
    digitalWrite(lampu, relayON);
}

void matikanModulModeMalam() {
    // mematikan lampu kandang ketika waktu sudah memasuki pagi hari
    //relay4
    digitalWrite(lampu, relayOFF);
}
// MODUL MODE MALAM

// MODUL KIRIM DATA

// MODUL KIRIM DATA