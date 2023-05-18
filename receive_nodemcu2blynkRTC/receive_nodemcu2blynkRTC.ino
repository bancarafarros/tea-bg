//#define BLYNK_TEMPLATE_ID "TMPL69iGXFtzB"
//#define BLYNK_TEMPLATE_NAME "kandang ayam"
//#define BLYNK_AUTH_TOKEN "7RyZrouJIw0UjHCwF0YN1iWY-qcmfkdn"

#define BLYNK_AUTH_TOKEN "7RyZrouJIw0UjHCwF0YN1iWY-qcmfkdn"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "RINJANI01";
char pass[] = "12345678";
//char ssid[] = "bringthaton";
//char pass[] = "12345666";
//char ssid[] = "Hotspot Area";
//char pass[] = "sekolahvokasimadiun";

BlynkTimer timer;

String dataIn;
String dt[11];
int i;
boolean parsing = false;

void setup(){
  Serial.begin(9600);

  Wire.begin(5, 4);   //Setting wire (5 untuk SDA dan 4 untuk SCL)

  if (! rtc.begin()) {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
  }

  //Atur Waktu
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  
  dataIn = "";

  // koneksi ke wifi
  WiFi.begin("RINJANI01", "12345678");
  // WiFi.begin("bringthaton", "12345666");
  // WiFi.begin("Hotspot Area", "sekolahvokasimadiun");
  
  // cek koneksi wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Berhasil terhubung ke WiFi");
  // koneksi ke wifi

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(5000L, sendSensor);
}

void loop(){
  if(Serial.available() > 0) {
        char inChar = (char)Serial.read();
        dataIn += inChar;
        
        if (inChar == '\n') {
            parsing = true;
        }
    }

    if(parsing) {
        parsingData();
        parsing = false;
        dataIn = "";
    }
  
  Blynk.run();
  timer.run();
}

void parsingData() {
    int j = 0;

    //  kirim data yang telah diterima sebelumnya
    Serial.print("data masuk: ");
    Serial.print(dataIn);

    //inisialisasi variabel, (reset isi variabel)
    dt[j] = "";

    //proses parsing data
    for(i=1; i<dataIn.length(); i++) {
        //SEPARATOR (#)
        if((dataIn[i] == '#')) {
            //increment variabel j, digunakan untuk merubah index array penampung
            j++;
            dt[j] = ""; //inisialisasi variabel array dt[j]
            
        } else {
            //proses menampung data saat pengecekan karakter sudah selesai
            dt[j] = dt[j] + dataIn[i];
        }
    }
    
    // // print data hasil parsing
    // Serial.print("Ketinggian Air: ");
    // Serial.println(dt[0].toInt());
    // Serial.print("Suhu: ");
    // Serial.println(dt[1].toFloat());
    // Serial.print("Kelembaban: ");
    // Serial.println(dt[2].toFloat());
    // Serial.print("Status Pakan: ");
    // Serial.println(dt[3]);
    // Serial.print("statusKipasSuhu: ");
    // Serial.println(dt[4]);
    // Serial.print("statusKipasKelembaban: ");
    // Serial.println(dt[5]);
    // Serial.print("Status Pompa;: ");
    // Serial.println(dt[6]);
    // Serial.print("statusLampu: ");
    // Serial.println(dt[7]);
    // delay(5000);
}

void sendSensor(){
  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;

  String statusPakan = String() + jam + ":" + menit + ":" + detik;
  Serial.println(statusPakan);
  
  Blynk.virtualWrite(V0, dt[0].toInt()); // ketinggian air
  Blynk.virtualWrite(V1, dt[1].toFloat()); // suhu
  Blynk.virtualWrite(V2, dt[2].toFloat()); // kelembaban
  Blynk.virtualWrite(V3, dt[3]); // statusPakan
  Blynk.virtualWrite(V4, dt[4].toInt()); // statusKipasSuhu
  Blynk.virtualWrite(V5, dt[5].toInt()); // statusKipasKelembaban
  Blynk.virtualWrite(V6, dt[6].toInt()); // statusPompa
  Blynk.virtualWrite(V7, dt[7].toInt()); // statusLampu

  if(statusPakan == "15:30:0"){
    Blynk.logEvent("status_pakan","Pakan sudah diberikan pada jam 7");
  
  } else if(statusPakan == "15:32:0"){
    Blynk.logEvent("status_pakan","Pakan sudah diberikan pada jam 12");
  
  } else if(statusPakan == "15:33:0"){
    Blynk.logEvent("status_pakan","Pakan sudah diberikan pada jam 17");
  }
}