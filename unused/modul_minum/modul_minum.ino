//sensor ketinggian air
//penampung nilai ketinggian air
int analogPin = A1;
int ketinggianAir;

//relay
const int kipas1 = 10; //relay1 suhu
const int kipas2 = 11; //relay2 kelembaban
const int pompa = 12; //relay3
const int lampu = 13; //relay4

//on off relay
int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati

void setup() {
    Serial.begin(9600);

    //  setup relay
    pinMode(kipas1, OUTPUT);
    pinMode(kipas2, OUTPUT);
    pinMode(pompa, OUTPUT);
    pinMode(lampu, OUTPUT);
    digitalWrite(kipas1, relayOFF);
    digitalWrite(kipas2, relayOFF);
    digitalWrite(pompa, relayOFF);
    digitalWrite(lampu, relayOFF);
}

void loop() {
    ketinggianAir = analogRead(analogPin);

    //  if (ketinggianAir <= 480) {
    //    Serial.println("Ketinggian air: 0mm");
    //  
    //  } else if (ketinggianAir > 480 && ketinggianAir <= 530) {
    //    Serial.println("Ketinggian air: 0mm - 5mm");
    //  
    //  } else if (ketinggianAir > 530 && ketinggianAir <= 615) {
    //    Serial.println("Ketinggian air: 5mm - 10mm");
    //  
    //  } else if (ketinggianAir > 615 && ketinggianAir <= 660) {
    //    Serial.println("Ketinggian air: 10mm - 15mm");
    //  
    //  } else if (ketinggianAir > 660 && ketinggianAir <= 680) {
    //    Serial.println("Ketinggian air: 15mm - 20mm");
    //  
    //  } else if (ketinggianAir > 680 && ketinggianAir <= 690) {
    //    Serial.println("Ketinggian air: 20mm - 25mm");
    //  
    //  } else if (ketinggianAir > 690 && ketinggianAir <= 700) {
    //    Serial.println("Ketinggian air: 25mm - 30mm");
    //  
    //  } else if (ketinggianAir > 700 && ketinggianAir <= 705) {
    //    Serial.println("Ketinggian air: 30mm - 35mm");
    //  
    //  } else if (ketinggianAir > 705) {
    //    Serial.println("Ketinggian air: 35mm - 40mm");
    //  }

    // // kondisi real
    //  if (ketinggianAir < 530) {
    //    modulIsiBakMinum();

    //  } else if (ketinggianAir > 705) {
    //    matikanModulIsiBakMinum();
    //  }

    // kondisi coba2
    if (ketinggianAir < 100) {
        modulIsiBakMinum();

    } else if (ketinggianAir > 300) {
        matikanModulIsiBakMinum();
    }
}

void modulIsiBakMinum() {
    // mengisi bak minum dengan menyala pompa air ketika bak minum hampir kosong
    //relay3
    digitalWrite(pompa, relayON);
    }

void matikanModulIsiBakMinum() {
    // mematikan pompa air ketika bak minum sudah hampir penuh
    //relay3
    digitalWrite(pompa, relayOFF);
}

