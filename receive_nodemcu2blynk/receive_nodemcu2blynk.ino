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
  // cek koneksi wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Berhasil terhubung ke WiFi");
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(2500L, sendSensor);
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
    //  Serial.print("\n");

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
    
    // kirim data hasil parsing
    Serial.print("Ketinggian Air: ");
    Serial.print(dt[0].toInt());
    Serial.print("\n");
    Serial.print("Suhu: ");
    Serial.print(dt[1].toFloat());
    Serial.print("\n");
    Serial.print("Kelembaban: ");
    Serial.print(dt[2].toFloat());
    Serial.print("\n");
    Serial.print("Hari: ");
    Serial.print(dt[3]);
    Serial.print("\n");
    Serial.print("Tanggal: ");
    Serial.print(dt[4]);
    Serial.print("\n");
    Serial.print("Bulan: ");
    Serial.print(dt[5]);
    Serial.print("\n");
    Serial.print("Tahun: ");
    Serial.print(dt[6]);
    Serial.print("\n");
    Serial.print("Jam: ");
    Serial.print(dt[7]);
    Serial.print("\n");
    Serial.print("Menit: ");
    Serial.print(dt[8]);
    Serial.print("\n");
    Serial.print("Detik: ");
    Serial.print(dt[9]);
    Serial.print("\n");
    delay(5000);
}

void sendSensor(){
  Blynk.virtualWrite(V0, dt[0]);
  Blynk.virtualWrite(V1, dt[1]);
  Blynk.virtualWrite(V2, dt[2]);
  Blynk.virtualWrite(V3, dt[3]);
  Blynk.virtualWrite(V4, dt[4]);
  Blynk.virtualWrite(V5, dt[5]);
  Blynk.virtualWrite(V6, dt[6]);
  Blynk.virtualWrite(V7, dt[7]);
  Blynk.virtualWrite(V8, dt[8]);
  Blynk.virtualWrite(V9, dt[9]);
  Blynk.virtualWrite(V10, dt[10]);
}
