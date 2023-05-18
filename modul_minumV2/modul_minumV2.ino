//sensor ketinggian air
//penampung nilai ketinggian air
int analogPin = A1;
int ketinggianAir;
int ketinggianAirMm;

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
    ketinggianAirMm = map(ketinggianAir, 0, 1023, 0, 255);

    // // kondisi real
    //  if (ketinggianAir < 30) {
    //    modulIsiBakMinum();

    //  } else if (ketinggianAir > 60) {
    //    matikanModulIsiBakMinum();
    //  }

    // kondisi coba2
    if (ketinggianAirMm < 30) {
        modulIsiBakMinum();

    } else if (ketinggianAirMm > 60) {
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