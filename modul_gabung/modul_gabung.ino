//dht11
#include <DHT.h>
DHT dht(7, DHT11); //Pin, Jenis DHT

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

bool statusPompa;

void setup() {
    Serial.begin(9600);

    //  dht11
    dht.begin();

    // servo
    servoku.attach(6);

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
    float kelembaban = dht.readHumidity();
    float suhu = dht.readTemperature();
    // BACA SUHU DAN KELEMBABAN

    // BACA KETINGGIAN AIR
    ketinggianAir = analogRead(analogPin);

    // KONDISI MODUL MONITORING SUSHU DAN KELEMBABAN
    //  suhu normal
    if (suhu >= 29 && suhu <= 31) {
        matikanModulPeningkatanSuhu();
        matikanModulPenurunanSuhu();

    //  suhu di bawah standar minimum
    } else if (suhu < 29) {
        modulPeningkatanSuhu();
    
    //  suhu di atas standar maksimal
    } else if (suhu > 31) {
        modulPenurunanSuhu();

    //  kelembaban normal
    } else if (kelembaban >= 50 && kelembaban <= 70) {
        matikanModulPeningkatanKelembaban();
        matikanModulPenurunanKelembaban();

    //  kelembaban di bawah standar minimum
    } else if (kelembaban < 50) {
        modulPeningkatanKelembaban();
        
    //  kelembaban di atas standar maksimal
    } else if (kelembaban > 70) {
        modulPenurunanKelembaban();
    }
    // KONDISI MODUL MONITORING SUSHU DAN KELEMBABAN
    
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

    // KIRIM DATA KE NODEMCU
    modulKirimData();
    // KIRIM DATA KE NODEMCU
}

// MODUL MINUM
void modulIsiBakMinum() {
    // mengisi bak minum dengan menyala pompa air ketika bak minum hampir kosong
    //relay3
    digitalWrite(pompa, relayON);
    statusPompa = HIGH;
    }

void matikanModulIsiBakMinum() {
    // mematikan pompa air ketika bak minum sudah hampir penuh
    //relay3
    digitalWrite(pompa, relayOFF);
    statusPompa = LOW;
}
// MODUL MINUM

// MODUL MONITORING SUHU DAN KELEMBABAN
void modulPeningkatanSuhu() {
    //meningkatkan suhu kandang ketika suhu di bawah normal dengan menyalakan lampu
    //relay4
    digitalWrite(lampu, relayON);
}

void matikanModulPeningkatanSuhu() {
    //mematikan modul peningkatan suhu ketika suhu normal tercapai dengan mematikan lampu
    //relay4
    digitalWrite(lampu, relayOFF);
}

void modulPenurunanSuhu() {
    //menurunkan suhu kandang ketika suhu di atas normal dengan menyalakan kipas1
    //relay1
    digitalWrite(kipas1, relayON);
}

void matikanModulPenurunanSuhu() {
    //mematikan modul penurunan suhu ketika suhu normal tercapai dengan mematikan kipas1
    //relay1
    digitalWrite(kipas1, relayOFF);
}

void modulPeningkatanKelembaban() {
    //meningkatkan kelembaban kandang ketika kelembaban di bawah normal dengan menyalakan kipas
    //relay2
    digitalWrite(kipas2, relayON);
}

void matikanModulPeningkatanKelembaban() {
    //mematikan modul peningkatan kelembaban ketika kelembaban normal tercapai dengan mematikan kipas
    //relay2
    digitalWrite(kipas2, relayOFF);
}

void modulPenurunanKelembaban() {
    //menurunkan kelembaban kandang ketika kelembaban di atas normal dengan menyalakan lampu
    //relay4
    digitalWrite(lampu, relayON);
}

void matikanModulPenurunanKelembaban() {
    //mematikan modul penurunan kelembaban ketika kelembaban normal tercapai dengan mematikan lampu
    //relay4
    digitalWrite(lampu, relayOFF);
}
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
void modulKirimData() {
    // BACA SUHU DAN KELEMBABAN
    float kelembaban = dht.readHumidity();
    float suhu = dht.readTemperature();
    // BACA SUHU DAN KELEMBABAN
    
    // String dataKirim = "#" + String(ketinggianAir) + "#" + String(suhu) + "#" + String(kelembaban) + "#" + String(hari) + "#" + String(tanggal) + "#" + String(bulan) + "#" + String(tahun) + "#" + String(jam) + "#" + String(menit) + "#" + String(detik) + "#" + String(statusPompa);
    String dataKirim = "#" + String(ketinggianAir) + "#" + String(suhu) + "#" + String(kelembaban) + "#" + String(hari) + "#" + String(statusPompa);
    Serial.println(dataKirim);
    delay(5000);
}
// MODUL KIRIM DATA
