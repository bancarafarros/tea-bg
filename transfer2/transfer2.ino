//rtc
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;

// define library dht dan pin
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
    
    // baca nilai sensor
    aer = analogRead(A1);
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    //  Serial.print("Aer = ");
    //  Serial.println(aer);
    //  Serial.print("Suhu = ");
    //  Serial.println(temperature);
    //  Serial.print("Kelembababan = ");
    //  Serial.println(humidity);
    //  delay(1000);

    String dataKirim = "#" + String(aer) + "#" + String(temperature) + "#" + String(humidity) + "#" + String(hari) + "#" + String(tanggal) + "#" + String(bulan) + "#" + String(tahun) + "#" + String(jam) + "#" + String(menit) + "#" + String(detik);
    Serial.println(dataKirim);
    delay(5000);
    //  Serial.println("");
}
