#include <SoftwareSerial.h>
#include <ThingerESP8266.h>

//buat variabel untuk software serial (Rx, Tx)
SoftwareSerial DataSerial(12,13);

//millis sebagai pengganti delay
unsigned long previousMillis = 0;
const long interval = 3000;

//variabel array untuk data parsing
String arrData[3];

//konfigurasi thinger.io
#define USERNAME "koper"   //sesuaikan punya anda
#define DEVICE_ID "Serial_ThingerIO"  //sesuaikan punya anda
#define DEVICE_CREDENTIAL "f#n_BMas-9Rv"  //sesuaikan punya anda

//variabel PIN_LED
#define LED_PIN 4   // pin D2

//variabel untuk thinger.io
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

//konfigurasi WiFi
const char* ssid = "bringthaton";  //sesuaikan punya anda
const char* password = "12345666";  //sesuaikan punya anda

//sediakan variabel untuk menampung nilai LDR, Temp, Hum yang siap dikirim ke thingerio
int ldr;
float temperature, humidity ;


void setup() {
  Serial.begin(9600);
  DataSerial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  //koneksi ke wifi
  WiFi.begin(ssid, password);
  //cek koneksi
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    digitalWrite(LED_PIN, LOW);
  }

  //apabila terkoneksi
  digitalWrite(LED_PIN, HIGH);
  //hubungkan nodemcu ke thingerIO
  thing.add_wifi(ssid, password);

  //data yang akan dikirim
  thing["Dataku"] >> [](pson & out)
  {
    out["ldr"] = ldr ;
    out["temperature"] = temperature ;
    out["humidity"] = humidity ;
  };
}

void loop() {
  //konfigurasi millis
  unsigned long currentMillis = millis(); //baca waktu millis saat ini
  if(currentMillis - previousMillis >= interval)
  {
    //update previousMillis
    previousMillis = currentMillis;

    //prioritaskan pembacaan data dari arduino (hasil kiriman data)
    //baca data serial
    String data="";
    while(DataSerial.available()>0)
    {
      data += char(DataSerial.read());
    }

    //buang spasi datanya
    data.trim();

    //uji data
    if(data != "")
    {
      //format data "10#29.45#89.50"
      //parsing data (pecah data)
      int index = 0;
      for(int i=0; i<=data.length(); i++)
      {
        char delimiter = '#';
        if(data[i] != delimiter)
          arrData[index] += data[i];
        else
          index++;   //variabel index bertambah 1
      }

      //pastikan data yang dikirim lengkap (LDR, Temp, Hum
      //urutannya 0=LDR, 1=Temp, 2=Hum
      if(index == 2)
      {
        //tampilkan nilai sensor ke serial monitor
        Serial.println("LDR         : " + arrData[0]);  //LDR
        Serial.println("Temperature : " + arrData[1]);  //Temp
        Serial.println("Humidity    : " + arrData[2]);  //Hum
        Serial.println();
      }

      //isikan variabel yang akan dikirim
      ldr         = arrData[0].toInt();
      temperature = arrData[1].toFloat();
      humidity    = arrData[2].toFloat();

      //picu pengiriman data ke thinger.io
      //apabila tidak terkoneksi ke thinger.io, maka pindahkan baris ini dibawah void loop
      thing.handle();
      
      arrData[0]="";
      arrData[1]="";
      arrData[2]="";
    }

    //minta data ke arduino
    DataSerial.println("YA");
  }
}
