//dht11
#include <DHT.h>
DHT dht(7, DHT11); //Pin, Jenis DHT

//relay
const int kipas1 = 10; //relay1 suhu
const int kipas2 = 11; //relay2 kelembaban
const int pompa = 12; //relay3
const int lampu = 13; //relay4

int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati

void setup() {
    Serial.begin(9600);
    
    //  dht11
    dht.begin();

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
    //  dht11
    float kelembaban = dht.readHumidity();
    float suhu = dht.readTemperature();

    //  Serial.print("kelembaban: ");
    //  Serial.print(kelembaban);
    //  Serial.print(" ");
    //  Serial.print("suhu: ");
    //  Serial.println(suhu);

    //  suhu normal
    if (suhu >= 29 && suhu <= 31) {
        matikanModulPeningkatanSuhu();
        matikanModulPenurunanSuhu();

    //  suhu di bawah standar minimum
    } else if (suhu < 29) {
        modulPeningkatanSuhu();
    
    //  suhu di atas standar maksimal
    } else if (suhu > 31) {
        modulPenurunanSuhu();

    //  kelembaban normal
    } else if (kelembaban >= 50 && kelembaban <= 70) {
        matikanModulPeningkatanKelembaban();
        matikanModulPenurunanKelembaban();

    //  kelembaban di bawah standar minimum
    } else if (kelembaban < 50) {
        modulPeningkatanKelembaban();
        
    //  kelembaban di atas standar maksimal
    } else if (kelembaban > 70) {
        modulPenurunanKelembaban();
    }
}

void modulPeningkatanSuhu() {
    //meningkatkan suhu kandang ketika suhu di bawah normal dengan menyalakan lampu
    //relay4
    digitalWrite(lampu, relayON);
}

void matikanModulPeningkatanSuhu() {
    //mematikan modul peningkatan suhu ketika suhu normal tercapai dengan mematikan lampu
    //relay4
    digitalWrite(lampu, relayOFF);
}

void modulPenurunanSuhu() {
    //menurunkan suhu kandang ketika suhu di atas normal dengan menyalakan kipas1
    //relay1
    digitalWrite(kipas1, relayON);
}

void matikanModulPenurunanSuhu() {
    //mematikan modul penurunan suhu ketika suhu normal tercapai dengan mematikan kipas1
    //relay1
    digitalWrite(kipas1, relayOFF);
}

void modulPeningkatanKelembaban() {
    //meningkatkan kelembaban kandang ketika kelembaban di bawah normal dengan menyalakan kipas
    //relay2
    digitalWrite(kipas2, relayON);
}

void matikanModulPeningkatanKelembaban() {
    //mematikan modul peningkatan kelembaban ketika kelembaban normal tercapai dengan mematikan kipas
    //relay2
    digitalWrite(kipas2, relayOFF);
}

void modulPenurunanKelembaban() {
    //menurunkan kelembaban kandang ketika kelembaban di atas normal dengan menyalakan lampu
    //relay4
    digitalWrite(lampu, relayON);
}

void matikanModulPenurunanKelembaban() {
    //mematikan modul penurunan kelembaban ketika kelembaban normal tercapai dengan mematikan lampu
    //relay4
    digitalWrite(lampu, relayOFF);
}