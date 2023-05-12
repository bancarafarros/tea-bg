//#define BLYNK_TEMPLATE_ID "TMPL69iGXFtzB"
//#define BLYNK_TEMPLATE_NAME "kandang ayam"
//#define BLYNK_AUTH_TOKEN "7RyZrouJIw0UjHCwF0YN1iWY-qcmfkdn"

#define BLYNK_AUTH_TOKEN "7RyZrouJIw0UjHCwF0YN1iWY-qcmfkdn"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

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
    // Serial.print("Hari: ");
    // Serial.println(dt[3]);
    // Serial.print("Tanggal: ");
    // Serial.println(dt[4]);
    // Serial.print("Bulan: ");
    // Serial.println(dt[5]);
    // Serial.print("Tahun: ");
    // Serial.println(dt[6]);
    // Serial.print("Jam: ");
    // Serial.println(dt[7]);
    // Serial.print("Menit: ");
    // Serial.println(dt[8]);
    // Serial.print("Detik: ");
    // Serial.println(dt[9]);
    // delay(5000);
}

void sendSensor(){
  Blynk.virtualWrite(V0, dt[0].toInt()); // ketinggian air
  Blynk.virtualWrite(V1, dt[1].toFloat()); // suhu
  Blynk.virtualWrite(V2, dt[2].toFloat()); // kelembaban
  Blynk.virtualWrite(V3, dt[3]); // statusPakan
  Blynk.virtualWrite(V4, dt[4].toInt()); // statusPompa

//  Blynk.virtualWrite(V0, dt[0]); // ketinggian air
//  Blynk.virtualWrite(V1, dt[1]); // suhu
//  Blynk.virtualWrite(V2, dt[2]); // kelembaban
//  Blynk.virtualWrite(V3, dt[3]); // hari
//  Blynk.virtualWrite(V4, dt[4]); // tanggal
//  Blynk.virtualWrite(V5, dt[5]); // bulan
//  Blynk.virtualWrite(V6, dt[6]); // tahun
//  Blynk.virtualWrite(V7, dt[7]); // jam
//  Blynk.virtualWrite(V8, dt[8]); // menit
//  Blynk.virtualWrite(V9, dt[9]); // detik
//  Blynk.virtualWrite(V10, dt[10]); // statusPompa
}