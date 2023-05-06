#include <SoftwareSerial.h>

//buat variabel untuk software serial
SoftwareSerial DataSerial(12, 13);

// millis
unsigned long previousMillis = 0;
const long interval = 3000;

//variabe array untuk data parsing
String arrData[3];

void setup() {
  Serial.begin(9600);
  DataSerial.begin(9600);
}

void loop() {
//  konfigurasi millis
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {
    // update previousMillis
    previousMillis = currentMillis;

    // prioritas pembacaan data dari uno
    // baca data serial
    String data = "";
    
    while(DataSerial.available() > 0) {
      data += char(DataSerial.read());
    }
    
    // buang spasi   
    data.trim();

    // uji data
    if(data != "") {
       // format data "10#29.45#89.50"
      // parsing data
      int index = 0;
      for(int i = 0; i <= data.length(); i++) {
        char delimiter = '#';
        if(data[i] != delimiter) {
          arrData[index] += data[i];
        } else {
          index++;
        }
        
        // pastikan data yang dikirim lengkap
        if(index == 2) {
          // tampilakan nilai sensor ke serial monitor
          Serial.println("LDR        = " + arrData[0]); // LDR
          Serial.println("Temperatur = " + arrData[1]); // Temperature
          Serial.println("Humidity   = " + arrData[2]); // Humidity
          Serial.println();
        }

        arrData[0] = "";
        arrData[1] = "";
        arrData[2] = "";
      }
      // minta data ke uno
      DataSerial.println("YA");
    }
  }
}
