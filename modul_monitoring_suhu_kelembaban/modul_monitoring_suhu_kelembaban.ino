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

  //relay
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, relayOFF);
  digitalWrite(relay2, relayOFF);
  digitalWrite(relay3, relayOFF);
  digitalWrite(relay4, relayOFF);
}

void loop() {
  //  dht11
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();
  
  Serial.print("kelembaban: ");
  Serial.print(kelembaban);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(suhu);

  if (suhu == 29 && suhu == 30 && suhu == 31) {
    
  
  } else if (suhu < 29 && suhu < 30 && suhu < 31) {
    modulPeningkatanSuhu();
  
  } else if (suhu > 29 && suhu > 30 && suhu > 31) {
    modulPenurunanSuhu();
    
  } else if () {
    
  } else if () {
  
  }
}

void modulPeningkatanSuhu() {
  //relay1
  digitalWrite(kipas1, relayON);
}

void modulPenurunanSuhu() {
  //relay1
  digitalWrite(kipas1, relayOFF);

  //relay4
  digitalWrite(lampu, relayON);
}

void peningkatanKelembaban() {
  //relay2
  digitalWrite(kipas2, relayON);
}

void penurunanKelembaban() {
  //relay2
  digitalWrite(kipas2, relayOFF);
}
