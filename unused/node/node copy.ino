// millis
unsigned long previousMillis = 0;
const long interval = 3000;

//variabe array untuk data parsing
String arrData[10];

void setup() {
  Serial.begin(9600);
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
    
    while(Serial.available() > 0) {
      data += char(Serial.read());
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
        if(index == 9) {
          // tampilakan nilai sensor ke serial monitor
          Serial.println("Ketinggian air = " + arrData[0]); // Ketinggian air
          Serial.println("Temperatur     = " + arrData[1]); // Temperatur
          Serial.println("Kelembaban     = " + arrData[2]); // Kelembaban
          Serial.println("Tanggal        = " + arrData[3] + arrData[4] + arrData[5] + arrData[6]); // Tanggal
          Serial.println("Waktu          = " + arrData[7] + arrData[8] + arrData[9]); // Waktu
          Serial.println();
        }

        arrData[0] = "";
        arrData[1] = "";
        arrData[2] = "";
        arrData[3] = "";
        arrData[4] = "";
        arrData[5] = "";
        arrData[6] = "";
        arrData[7] = "";
        arrData[8] = "";
        arrData[9] = "";
      }
      // minta data ke uno
      Serial.println("YA");
    }
  }
}
