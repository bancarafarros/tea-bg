 #include <SoftwareSerial.h>
 SoftwareSerial link(12, 13); // Rx, Tx
String dataIn;
String dt[10];
int i;
boolean parsing=false;
 
void setup() {
    Serial.begin(9600);
    link.begin(9600);
    dataIn="";
}
 
void loop() {
  ambilData();
}

void ambilData() {
  if(link.available()>0) {
           char inChar = (char)link.read();
           dataIn += inChar;
           if (inChar == '\n') {parsing = true;}
     }
     
     if(parsing) {
           parsingData();
           parsing=false;
           dataIn="";
     }
}
 
void parsingData() {
      int j=0;
      Serial.print("data masuk : ");
      Serial.print(dataIn);
      Serial.print("\n");
      //inisialisasi variabel, (reset isi variabel)
      dt[j]="";
      //proses parsing data
      for(i=1;i<dataIn.length();i++) {
             //pengecekan tiap karakter dengan karakter (#) dan (,)
             if ((dataIn[i] == '#') || (dataIn[i] == ',')) {
                   //increment variabel j, digunakan untuk merubah index array penampung
                   j++;
                  dt[j]=""; //inisialisasi variabel array dt[j]
             
             } else {
                  //proses tampung data saat pengecekan karakter selesai.
                  dt[j] = dt[j] + dataIn[i];
             }
      }
      //kirim data hasil parsing
      Serial.print("data 1 : ");
      Serial.print(dt[0].toInt());
      Serial.print("\n");
      Serial.print("data 2 : ");
      Serial.print(dt[1].toInt());
      Serial.print("\n\n");
}
