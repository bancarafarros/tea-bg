//variabe array untuk data parsing
String arrData[3];

void setup() {
  Serial.begin(9600);
}

void loop() {
    String data = "";
    
    while(Serial.available() > 0) {
      char datachar = Serial.read();
      data = datachar;
    }

//    data += char(Serial.read());
//    data = datachar;
    
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
    }
}
