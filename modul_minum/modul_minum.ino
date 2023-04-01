//sensor ketinggian air
//penampung nilai ketinggian air
int analogPin = A1;
int sensorVal;

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
  sensorVal = analogRead(analogPin);

  if (sensorVal <= 480) {
    Serial.println("Ketinggian air: 0mm");
  
  } else if (sensorVal > 480 && sensorVal <= 530) {
    Serial.println("Ketinggian air: 0mm - 5mm");
  
  } else if (sensorVal > 530 && sensorVal <= 615) {
    Serial.println("Ketinggian air: 5mm - 10mm");
  
  } else if (sensorVal > 615 && sensorVal <= 660) {
    Serial.println("Ketinggian air: 10mm - 15mm");
  
  } else if (sensorVal > 660 && sensorVal <= 680) {
    Serial.println("Ketinggian air: 15mm - 20mm");
  
  } else if (sensorVal > 680 && sensorVal <= 690) {
    Serial.println("Ketinggian air: 20mm - 25mm");
  
  } else if (sensorVal > 690 && sensorVal <= 700) {
    Serial.println("Ketinggian air: 25mm - 30mm");
  
  } else if (sensorVal > 700 && sensorVal <= 705) {
    Serial.println("Ketinggian air: 30mm - 35mm");
  
  } else if (sensorVal > 705) {
    Serial.println("Ketinggian air: 35mm - 40mm");
  }

//  if (sensorVal < 530) {
//    modulIsiBakMinum();
//  
//  } else if (sensorVal > 705) {
//    matikanModulIsiBakMinum();
//  }

  if (sensorVal < 100) {
    modulIsiBakMinum();
  
  } else if (sensorVal > 300) {
    matikanModulIsiBakMinum();
  }
}

void modulIsiBakMinum() {
  //relay3
  digitalWrite(pompa, relayON);
}

void matikanModulIsiBakMinum() {
  //relay3
  digitalWrite(pompa, relayOFF);
}
