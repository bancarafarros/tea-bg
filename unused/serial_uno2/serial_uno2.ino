String datasend;

void setup() {
  Serial.begin(9600);
}

void loop() {
  datasend = "10";

  if(Serial.available() > 0) {
    Serial.println(datasend);
  }
}
