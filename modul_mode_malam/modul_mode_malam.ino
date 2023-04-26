//rtc
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;

//dht11
#include <DHT.h>
DHT dht(7, DHT11); //Pin, Jenis DHT

//relay
const int kipas1 = 10; //relay1 suhu
const int kipas2 = 11; //relay2 kelembaban
const int pompa = 12; //relay3
const int lampu = 13; //relay4

int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati

void setup() {
    Serial.begin(9600);

    // rtc
    if (! rtc.begin()) {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
    }

    //Atur Waktu
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    // end of rtc

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
    // rtc
    DateTime now = rtc.now();
    hari    = dataHari[now.dayOfTheWeek()];
    tanggal = now.day(), DEC;
    bulan   = now.month(), DEC;
    tahun   = now.year(), DEC;
    jam     = now.hour(), DEC;
    menit   = now.minute(), DEC;
    detik   = now.second(), DEC;

    if (jam == 17 && menit == 0 && detik == 0) {
        modulModeMalam();
    
    } else if (jam == 7 && menit == 0 && detik == 0) {
        matikanModulModeMalam();
    }
}

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