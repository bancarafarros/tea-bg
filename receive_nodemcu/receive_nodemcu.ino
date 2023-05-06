String dataIn;
String dt[10];
int i;
boolean parsing = false;

void setup() {
  Serial.begin(9600);
  dataIn = "";
}

void loop() {
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
    //SEPARATOR (,)
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
  Serial.print("data 1: ");
  Serial.print(dt[0].toInt());
  Serial.print("\n");
  Serial.print("data 2: ");
  Serial.print(dt[1].toFloat());
  Serial.print("\n");
  Serial.print("data 3: ");
  Serial.print(dt[2].toFloat());
  Serial.print("\n");
  Serial.print("\n");
  delay(5000);

//  //kosongin data
//  dataIn = "";
//  dataIn[i] = "";
//  dt[10] = "";
//  dt[j] = "";
}
